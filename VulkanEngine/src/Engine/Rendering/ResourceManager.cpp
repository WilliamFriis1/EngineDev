#include "ResourceManager.h"

//TEMPORARY, MESHES WILL CONTAIN VERTEX DATA LATER ON


void ResourceManager::create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager)
{
    vertices =
    {
        {{ 0.0f, -0.5f }, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f,  0.5f }, {0.0f, 1.0f, 0.0f}},
        {{-0.5f,  0.5f }, {0.0f, 0.0f, 1.0f}}
    };

    auto size = sizeof(vertices[0]) * vertices.size();
    StagingBuffer stageBuff{};

    vertBuff.create(physicalDevice, device, size);
    stageBuff.create(physicalDevice, device, size);

    stageBuff.upload(vertices.data());

    transferManager.copyBuffer(stageBuff.get(), vertBuff.get(), size);

    stageBuff.cleanup();
}

void ResourceManager::cleanup()
{
    vertBuff.cleanup();
}

VkBuffer ResourceManager::getVertexBuffer() const
{
    return vertBuff.get();
}

uint32_t ResourceManager::getVertCount() const
{
    return static_cast<uint32_t>(vertices.size());
}
