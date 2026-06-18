#pragma once
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

class CommandPool
{
private:
	VkCommandPool commandPool = VK_NULL_HANDLE;

public:

	VkCommandPool get() const;

	CommandPool() = default;
	~CommandPool() = default;

	void create(VkDevice device, uint32_t graphicsFamily);
	void cleanup(VkDevice device);

};