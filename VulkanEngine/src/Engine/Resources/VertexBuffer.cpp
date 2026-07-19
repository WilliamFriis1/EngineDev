#include "VertexBuffer.h"

VkBuffer VertexBuffer::get() const
{
	return buffer.get();
}

void VertexBuffer::create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size)
{
    buffer.create(physicalDevice, device, size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
}

void VertexBuffer::cleanup()
{
    buffer.cleanup();
}
