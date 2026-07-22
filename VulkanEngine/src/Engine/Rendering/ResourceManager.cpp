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

    meshes.emplace_back(square);

    meshes.back().create(physicalDevice, device, transferManager, vertices, indices);

    Mesh triangle{};

    meshes.emplace_back(triangle);

    meshes.back().create(physicalDevice, device, transferManager, vertices1, indices1);

    TransformData transform{};

    transform.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0, 0));

    uniformBuffer.create(physicalDevice, device, sizeof(glm::mat4));

    uniformBuffer.upload(&transform);
}

std::vector<Mesh>& ResourceManager::getMeshes()
{
    return meshes;
}

UniformBuffer& ResourceManager::getUniformBuffer()
{
    return uniformBuffer;
}
