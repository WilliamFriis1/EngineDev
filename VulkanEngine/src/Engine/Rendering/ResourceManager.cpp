#include "ResourceManager.h"



void ResourceManager::create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager)
{
    //TEMPORARY
    vertices =
    {
        {{ -0.5f, -0.5f }, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f, -0.5f }, {0.0f, 1.0f, 0.0f}},
        {{ 0.5f, 0.5f }, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f }, {1, 1, 0}}
    };

    indices = { 0, 1, 2, 2, 3, 0 };

    vertices1 =
    {
        {{ -0.5f, -0.5f }, {1.0f, 1.0f, 1.0f}},
        {{ -0.3f, -0.5f }, {1.0f, 1.0f, 1.0f}},
        {{ -0.4f, -0.3f }, {1.0f, 1.0f, 1.0f}},
    };

    indices1 = { 0, 1, 2, };


    Mesh square{};

    square.create(physicalDevice, device, transferManager, vertices, indices);

    Mesh triangle{};

    triangle.create(physicalDevice, device, transferManager, vertices1, indices1);

    meshes.push_back(square);
    meshes.push_back(triangle);
}

std::vector<Mesh>& ResourceManager::getMeshes()
{
    return meshes;
}
