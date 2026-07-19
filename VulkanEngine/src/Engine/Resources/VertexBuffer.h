#pragma once
#include "Buffer.h"

#include <vector>

class VertexBuffer
{
private:
    
    Buffer buffer{};

public:
    VkBuffer get() const;

    void create(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size);

    void cleanup();
};