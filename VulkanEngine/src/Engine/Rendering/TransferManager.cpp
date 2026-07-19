#include "TransferManager.h"

VkCommandBuffer TransferManager::beginSingleTimeCommands()
{
	VkCommandBuffer buffer{};

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;

	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;
	allocInfo.commandPool = commandPool;

	if (vkAllocateCommandBuffers(device, &allocInfo, &buffer) != VK_SUCCESS)
		throw std::runtime_error("Failed to allocate command buffer");

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	if (vkBeginCommandBuffer(buffer, &beginInfo) != VK_SUCCESS)
		throw std::runtime_error("Failed to begin transfer command buffer");

	return buffer;
}

void TransferManager::endSingleTimeCommands(VkCommandBuffer commandBuffer)
{
	if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
		throw std::runtime_error("Failed to end transfer command buffer");

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS)
		throw std::runtime_error("Failed to submit transfer command buffer");

	vkQueueWaitIdle(graphicsQueue);

	vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

void TransferManager::create(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue)
{
	this->device = device;
	this->commandPool = commandPool;
	this->graphicsQueue = graphicsQueue;
}

void TransferManager::copyBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize bufferSize)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands();

	VkBufferCopy copyRegion{};
	copyRegion.size = bufferSize;

	vkCmdCopyBuffer(commandBuffer, src, dst, 1, &copyRegion);

	endSingleTimeCommands(commandBuffer);
}
