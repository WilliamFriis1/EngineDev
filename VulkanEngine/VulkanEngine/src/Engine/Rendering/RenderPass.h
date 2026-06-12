#pragma once
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

class RenderPass
{
private:
	VkRenderPass renderPass = VK_NULL_HANDLE;

public:

	void create(VkDevice device, VkFormat swapchainFormat);
	void cleanup(VkDevice device);
};
