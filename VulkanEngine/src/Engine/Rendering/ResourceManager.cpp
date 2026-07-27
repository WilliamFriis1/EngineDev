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

    camera.getTransform().translate({ 0,0,3 });

    Entity square{};

    meshes.emplace_back();
    meshes.back().create(physicalDevice, device, transferManager, vertices, indices, 0);

    Entity triangle{};

    meshes.emplace_back();
    meshes.back().create(physicalDevice, device, transferManager, vertices1, indices1, 1);

    square.mesh = &meshes[0];
    triangle.mesh = &meshes[1];

    scene.entities.emplace_back(square);
    scene.entities.emplace_back(triangle);

    scene.activeCamera = &camera;
}

Scene& ResourceManager::getScene()
{
    return scene;
}
