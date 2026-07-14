#pragma once

#include <vulkan/vulkan.h>
#include <iostream>

class TransferManager
{
private:

	VkDevice device;
	VkQueue graphicsQueue;
	VkCommandPool commandPool;

	VkCommandBuffer beginSingleTimeCommands();

	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

public:

	void create(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue);

	void cleanup(VkDevice device);

	void copyBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize bufferSize);
};