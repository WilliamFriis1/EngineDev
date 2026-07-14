#pragma once

#include <vulkan/vulkan.h>
#include <iostream>

class Buffer
{

private:

	VkBuffer buffer = VK_NULL_HANDLE;
	VkDeviceMemory memory = VK_NULL_HANDLE;

	uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

protected:
	VkDeviceMemory getMemory() const;
public:
	VkBuffer get() const;

	void create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);

	void cleanup(VkDevice device);
};