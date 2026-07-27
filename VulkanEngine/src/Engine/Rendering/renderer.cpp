#include "renderer.h"

void Renderer::record(uint32_t imageIndex, const RenderQueue& renderQueue, const std::vector<ObjectData>& objs, const Camera& camera)
{
	VkClearValue clearColor = { {0.0f, 0.0f, 0.0f, 1.0f} };
	VkDeviceSize offsets[] = { 0 };

	const VkCommandBuffer& cmdBuff = commandBufferManager.get()[imageIndex];
	const VkFramebuffer& framebuffer = framebufferManager.get()[imageIndex];

	VkCommandBufferBeginInfo beginInfo{};

	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	if (vkBeginCommandBuffer(cmdBuff, &beginInfo) != VK_SUCCESS)
		throw std::runtime_error("Failed to begin command buffer");

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;

	renderPassInfo.renderPass = renderPass.get();
	renderPassInfo.framebuffer = framebuffer;

	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = swapchain->getExtents();

	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;

	vkCmdBeginRenderPass(cmdBuff, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(cmdBuff, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline.get());

	vkCmdBindDescriptorSets(cmdBuff, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline.getLayout(), 0, 1, descriptorManager.getDescriptorSet(), 0, nullptr);

	CameraData cameraData{};

	cameraData.projection = camera.getProjectionMatrix();
	cameraData.view = camera.getViewMatrix();

	uniformBuffer.upload(&cameraData);
	storageBuffer.upload(objs.data());

	for (auto& cmd : renderQueue.get())
	{
		vkCmdPushConstants(cmdBuff, graphicsPipeline.getLayout(), VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(uint32_t), &cmd.objectIndex);

		cmd.mesh->bind(cmdBuff);
		cmd.mesh->draw(cmdBuff);
	}

	vkCmdEndRenderPass(cmdBuff);

	if (vkEndCommandBuffer(cmdBuff) != VK_SUCCESS)
		throw std::runtime_error("Failed to end command buffer");

}

void Renderer::create(VkPhysicalDevice physicalDevice, VkDevice device, Swapchain* swapchain, const CommandPool& commandPool, VkQueue graphicsQueue, VkQueue presentQueue, uint32_t maxObjects)
{
	this->swapchain = swapchain;
	this->device = device;
	this->graphicsQueue = graphicsQueue;
	this->presentQueue = presentQueue;

	renderPass.create(device, swapchain->getImageFormat());

	framebufferManager.createFramebuffers
	(
		device,
		renderPass.get(),
		swapchain->getImageViews(),
		swapchain->getExtents()
	);

	descriptorManager.create(device);

	graphicsPipeline.create(device, swapchain->getExtents(), renderPass.get(), descriptorManager.getDescriptorLayout());

	commandBufferManager.create(device, commandPool.get(), static_cast<uint32_t>(framebufferManager.getCount()));

	syncManager.create(device, static_cast<uint32_t>(swapchain->getImageCount()));

	uniformBuffer.create(physicalDevice, device, sizeof(CameraData));
	storageBuffer.create(physicalDevice, device, sizeof(ObjectData) * maxObjects);

	descriptorManager.update(device, uniformBuffer, storageBuffer);
}

void Renderer::cleanup()
{
	syncManager.cleanup(device);
	commandBufferManager.cleanup();
	descriptorManager.cleanup(device);
	graphicsPipeline.cleanup(device);
	framebufferManager.cleanupFramebuffers(device);
	renderPass.cleanup(device);
}
void Renderer::createSwapchainResources()
{
	framebufferManager.createFramebuffers
	(
		device,
		renderPass.get(),
		swapchain->getImageViews(),
		swapchain->getExtents()
	);
}
void Renderer::destroySwapchainResources()
{
	framebufferManager.cleanupFramebuffers(device);
}
Renderer::DrawStatus Renderer::drawFrame( const RenderQueue& renderQueue, const std::vector<ObjectData>& objs, const Camera& camera)
{
	uint32_t imageIndex;

	VkFence fence = syncManager.getFramesInFlight(currentFrame);
	VkSemaphore imageAvailSem = syncManager.getImageAvailable(currentFrame);

	vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);
	vkResetFences(device, 1, &fence);

	VkResult result = vkAcquireNextImageKHR(device, swapchain->get(), UINT64_MAX, imageAvailSem, VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		return DRAW_FAIL;
	}

	record(imageIndex, renderQueue, objs, camera);

	VkSemaphore renderFinSem = syncManager.getRenderFinished(imageIndex);

	VkFence& imageInFlight = syncManager.getImageInFlight(imageIndex);

	if (imageInFlight != VK_NULL_HANDLE)
	{
		vkWaitForFences(device, 1, &imageInFlight, VK_TRUE, UINT64_MAX);
	}

	imageInFlight = fence;

	VkCommandBuffer commandBuffer = commandBufferManager.get()[imageIndex];

	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &imageAvailSem;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &renderFinSem;

	if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, fence) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to submit draw command buffer");
	}

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &renderFinSem;

	VkSwapchainKHR swapChains[] = { swapchain->get() };

	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;

	result = vkQueuePresentKHR(presentQueue, &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
	{
		currentFrame = (currentFrame + 1) % SyncManager::MAX_FRAMES_IN_FLIGHT;

		return DRAW_FAIL;
	}

	return DRAW_SUCCESS;

}

