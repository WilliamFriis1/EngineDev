#pragma once

#include "Buffer.h"

#include <vulkan/vulkan.h>
#include <cstring>

class StagingBuffer
{
private:

    Buffer buffer{};

public:
    VkBuffer get() const;

    void create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size);

    void cleanup();

    void upload(const void* data);
};