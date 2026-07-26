#include "CommandBufferManager.h"

const std::vector<VkCommandBuffer>& CommandBufferManager::get() const
{
	return commandBuffers;
}

void CommandBufferManager::create(VkDevice device, VkCommandPool commandPool, uint32_t count)
{
	commandBuffers.resize(count);

	VkCommandBufferAllocateInfo allocInfo{};

	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;

	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

	allocInfo.commandBufferCount = count;

	if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
		throw std::runtime_error("Failed to allocate command buffers");

	std::cout << "Allocated " << count << " command buffers\n";
}

void CommandBufferManager::cleanup()
{
	commandBuffers.clear();
}
