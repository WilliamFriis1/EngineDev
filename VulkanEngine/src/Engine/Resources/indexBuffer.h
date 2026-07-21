#pragma once
#include "buffer.h"

class IndexBuffer
{
private:

    Buffer buffer{};

public:
    VkBuffer get() const;

    void create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size);

    void cleanup();
};