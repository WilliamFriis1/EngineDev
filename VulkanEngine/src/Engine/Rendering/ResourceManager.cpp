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

    meshes.back().create(physicalDevice, device, transferManager, vertices, indices, 0);

    Mesh triangle{};

    meshes.emplace_back(triangle);

    meshes.back().create(physicalDevice, device, transferManager, vertices1, indices1, 1);

    ObjectData transform1{};
    ObjectData transform2{};

    CameraData cameraData{};

    camera.getTransform().translate({ 0,0,3 });
    camera.update();

    objectData.emplace_back(transform1);
    objectData.back().model = meshes[0].getTransform().getMatrix();

    objectData.emplace_back(transform2);
    objectData.back().model = meshes[1].getTransform().getMatrix();

    uniformBuffer.create(physicalDevice, device, sizeof(CameraData));
    storageBuffer.create(physicalDevice, device, sizeof(ObjectData) * objectData.size());
}

std::vector<Mesh>& ResourceManager::getMeshes()
{
    return meshes;
}

std::vector<ObjectData>& ResourceManager::getObjects()
{
    return objectData;
}

UniformBuffer& ResourceManager::getUniformBuffer()
{
    return uniformBuffer;
}

StorageBuffer& ResourceManager::getStorageBuffer()
{
    return storageBuffer;
}

Camera& ResourceManager::getCamera()
{
    return camera;
}
