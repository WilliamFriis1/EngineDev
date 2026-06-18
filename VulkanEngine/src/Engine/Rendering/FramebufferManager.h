#pragma once
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

class FramebufferManager
{

private:
	std::vector<VkFramebuffer> framebuffers;

public:
	const std::vector<VkFramebuffer>& get() const;
	size_t getCount() const;

	FramebufferManager() = default;
	~FramebufferManager() = default;

	void createFramebuffers(VkDevice device, VkRenderPass renderPass, const std::vector<VkImageView>& imageViews, const VkExtent2D& extent);

	void cleanupFramebuffers(VkDevice device);
};