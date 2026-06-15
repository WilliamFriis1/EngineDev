#pragma once
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

class FramebufferManager
{

private:
	std::vector<VkFramebuffer> framebuffers;

public:
	FramebufferManager() = default;
	~FramebufferManager() = default;

	void createFramebuffers(VkDevice device, VkRenderPass renderPass, const std::vector<VkImageView>& imageViews, const VkExtent2D& extent);

	void cleanupFramebuffers(VkDevice device);
};