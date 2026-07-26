#pragma once

#include "buffer.h"

#include <vulkan/vulkan.h>

class StorageBuffer
{
private:

    Buffer buffer{};
    void* mappedMemory{};

public:
    VkBuffer get() const;

    VkDeviceSize getSize() const;

    void* getMappedData();

    void create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size);

    void cleanup();

    void upload(const void* data);
};