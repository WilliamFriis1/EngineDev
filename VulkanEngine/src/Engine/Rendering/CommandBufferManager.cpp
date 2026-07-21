#include "CommandBufferManager.h"

const std::vector<VkCommandBuffer>& CommandBufferManager::get() const
{
	return commandBuffers;
}

void CommandBufferManager::create(VkDevice device, VkCommandPool commandPool, uint32_t count)
{
	commandBuffers.resize(count);

	VkCommandBufferAllocateInfo allocInfo{};

	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;

	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

	allocInfo.commandBufferCount = count;

	if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
		throw std::runtime_error("Failed to allocate command buffers");

	std::cout << "Allocated " << count << " command buffers\n";
}

void CommandBufferManager::cleanup()
{
	commandBuffers.clear();
}

void CommandBufferManager::record(VkRenderPass renderPass, VkExtent2D extent, VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout, const std::vector<VkFramebuffer>& framebuffers, std::vector<Mesh>& meshes)
{
	VkClearValue clearColor = { {0.0f, 0.0f, 0.0f, 1.0f} };
	VkDeviceSize offsets[] = { 0 };

	for (size_t i = 0; i < commandBuffers.size(); i++)
	{
		VkCommandBufferBeginInfo beginInfo{};

		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
			throw std::runtime_error("Failed to begin command buffer");

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;

		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = framebuffers[i];

		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = extent;

		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

		VkBuffer buffer[1];

		for (auto& mesh : meshes)
		{
			buffer[0] = mesh.getVertexBuffer();

			vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, buffer, offsets);

			vkCmdBindIndexBuffer(commandBuffers[i], mesh.getIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);

			vkCmdDrawIndexed(commandBuffers[i], mesh.getIndexCount(), 1, 0, 0, 0);
		}

		vkCmdEndRenderPass(commandBuffers[i]);

		if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
			throw std::runtime_error("Failed to end command buffer");
	}
}
