#pragma once

#include "buffer.h"

#include <vulkan/vulkan.h>

class UniformBuffer
{
private:

    Buffer buffer{};
    void* mappedMemory;

public:
    VkBuffer get() const;

    void create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size);

    void cleanup();

    void upload(const void* data);
};