#pragma once
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

class SyncManager
{
private:
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> framesInFlight;
	std::vector<VkFence> imageInFlight;

public:

	static constexpr uint32_t MAX_FRAMES_IN_FLIGHT = 2;

	SyncManager() = default;
	~SyncManager() = default;

	void create(VkDevice device, uint32_t swapChainImageCount);
	void cleanup(VkDevice device);

	VkSemaphore getImageAvailable(uint32_t frame) const;
	VkSemaphore getRenderFinished(uint32_t frame) const;
	VkFence getFramesInFlight(uint32_t frame) const;
	VkFence& getImageInFlight(uint32_t frame);

};