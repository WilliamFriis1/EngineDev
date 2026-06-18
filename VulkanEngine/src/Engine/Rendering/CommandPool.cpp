#include "CommandPool.h"

VkCommandPool CommandPool::get() const
{
	return commandPool;
}

void CommandPool::create(VkDevice device, uint32_t graphicsFamily)
{
	VkCommandPoolCreateInfo poolInfo{};

	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;

	poolInfo.queueFamilyIndex = graphicsFamily;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
		throw std::runtime_error("Failed to create command pool");
}

void CommandPool::cleanup(VkDevice device)
{
	if (commandPool != VK_NULL_HANDLE)
	{
		vkDestroyCommandPool(device, commandPool, nullptr);

		commandPool = VK_NULL_HANDLE;
	}
}
