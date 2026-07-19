#include "StagingBuffer.h"

VkBuffer StagingBuffer::get() const
{
	return buffer.get();
}

void StagingBuffer::create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size)
{
	buffer.create(physicalDevice, device, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
}

void StagingBuffer::cleanup()
{
	buffer.cleanup();
}

void StagingBuffer::upload(const void* data)
{
	void* mapped = buffer.map();

	memcpy(mapped, data, buffer.getSize());

	buffer.unmap();
}
