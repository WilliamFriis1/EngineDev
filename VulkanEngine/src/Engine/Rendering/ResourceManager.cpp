#include "ResourceManager.h"

//TEMPORARY, MESHES WILL CONTAIN VERTEX DATA LATER ON
std::vector<Vertex> vertices =
{
    {{ 0.0f, -0.5f }, {1.0f, 0.0f, 0.0f}},
    {{ 0.5f,  0.5f }, {0.0f, 1.0f, 0.0f}},
    {{-0.5f,  0.5f }, {0.0f, 0.0f, 1.0f}}
};

void ResourceManager::create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager)
{
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
