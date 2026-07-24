#include "uniformBuffer.h"

VkBuffer UniformBuffer::get() const
{
	return buffer.get();
}

VkDeviceSize UniformBuffer::getSize() const
{
	return buffer.getSize();
}

void* UniformBuffer::getMappedData()
{
	return mappedMemory;
}

void UniformBuffer::create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size)
{
	buffer.create(physicalDevice, device, size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

	mappedMemory = buffer.map();
}

void UniformBuffer::cleanup()
{
	buffer.cleanup();
}

void UniformBuffer::upload(const void* data)
{
	memcpy(mappedMemory, data, buffer.getSize());
}