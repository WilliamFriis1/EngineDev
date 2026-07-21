#include "indexBuffer.h"

VkBuffer IndexBuffer::get() const
{
    return buffer.get();
}

void IndexBuffer::create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size)
{
    buffer.create(physicalDevice, device, size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
}

void IndexBuffer::cleanup()
{
    buffer.cleanup();
}