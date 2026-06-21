#include "SyncManager.h"

void SyncManager::create(VkDevice device, uint32_t swapChainImageCount)
{
	imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	framesInFlight.resize(MAX_FRAMES_IN_FLIGHT);

	renderFinishedSemaphores.resize(swapChainImageCount);
	imageInFlight.resize(swapChainImageCount);

	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS)
			throw std::runtime_error("Failed to create image available semaphore");

		if (vkCreateFence(device, &fenceInfo, nullptr, &framesInFlight[i]) != VK_SUCCESS)
			throw std::runtime_error("Failed to create frame fence");
	}

	for (auto& sem : renderFinishedSemaphores)
	{
		if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &sem) != VK_SUCCESS)
			throw std::runtime_error("Failed to create render finished semaphore");
	}
}

void SyncManager::cleanup(VkDevice device)
{
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
		vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
		vkDestroyFence(device, framesInFlight[i], nullptr);
	}
}

VkSemaphore SyncManager::getImageAvailable(uint32_t frame) const
{
	return imageAvailableSemaphores[frame];
}

VkSemaphore SyncManager::getRenderFinished(uint32_t frame) const
{
	return renderFinishedSemaphores[frame];
}

VkFence SyncManager::getFramesInFlight(uint32_t frame) const
{
	return framesInFlight[frame];
}

VkFence& SyncManager::getImageInFlight(uint32_t frame)
{
	return imageInFlight[frame];
}



