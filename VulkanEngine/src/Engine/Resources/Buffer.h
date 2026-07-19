#pragma once

#include <vulkan/vulkan.h>
#include <iostream>

class Buffer
{

private:

	VkDevice device{};

	VkBuffer buffer = VK_NULL_HANDLE;
	VkDeviceMemory memory = VK_NULL_HANDLE;

	VkDeviceSize size{};

	uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

public:
	VkBuffer get() const;
	VkDeviceSize getSize() const;

	void create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);

	void cleanup();

	void* map();
	void unmap();
};