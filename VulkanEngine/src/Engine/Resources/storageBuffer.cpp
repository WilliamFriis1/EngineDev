#include "storageBuffer.h"

VkBuffer StorageBuffer::get() const
{
	return buffer.get();
}

VkDeviceSize StorageBuffer::getSize() const
{
	return buffer.getSize();
}

void* StorageBuffer::getMappedData()
{
	return mappedMemory;
}

void StorageBuffer::create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size)
{
	buffer.create(physicalDevice, device, size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

	mappedMemory = buffer.map();
}

void StorageBuffer::cleanup()
{
	buffer.cleanup();
}

void StorageBuffer::upload(const void* data)
{
	memcpy(mappedMemory, data, buffer.getSize());
}