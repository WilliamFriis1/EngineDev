#include "Buffer.h"
uint32_t Buffer::findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties memProperties;

	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

	for (size_t i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if (typeFilter & (1<< i))
		{
			if ((memProperties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				return i;
			}
		}
	}

	throw std::runtime_error("Failed to find suitable memory type");
}

VkBuffer Buffer::get() const
{
	return buffer;
}

VkDeviceSize Buffer::getSize() const
{
	return size;
}

void Buffer::create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize bufferSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
{
	this->device = device;
	this->size = size;

	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;

	bufferInfo.size = bufferSize;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
		throw std::runtime_error("Failed to create buffer");

	VkMemoryRequirements memRequirements{};
	vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties);
	
	if (vkAllocateMemory(device, &allocInfo, nullptr, &memory) != VK_SUCCESS)
		throw std::runtime_error("Failed to allocate buffer memory");

	if (vkBindBufferMemory(device, buffer, memory, 0) != VK_SUCCESS)
		throw std::runtime_error("Failed to bind buffer to memory");
}

void Buffer::cleanup()
{
	if (buffer != VK_NULL_HANDLE)
	{
		vkDestroyBuffer(device, buffer, nullptr);
		buffer = VK_NULL_HANDLE;
	}

	if (memory != VK_NULL_HANDLE)
	{
		vkFreeMemory(device, memory, nullptr);
		memory = VK_NULL_HANDLE;
	}
}

void* Buffer::map()
{
	void* data;

	if (vkMapMemory(device, memory, 0, size, 0, &data) != VK_SUCCESS)
		throw std::runtime_error("Failed to map buffer memory");

	return data;
}

void Buffer::unmap()
{
	vkUnmapMemory(device, memory);
}
