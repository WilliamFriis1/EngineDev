#pragma once

#include "Engine/Rendering/transferManager.h"
#include "Utility/assetLoader.h"
#include "scene.h"

#include <vulkan/vulkan.h>
class SceneManager
{

private:
	std::vector<Vertex> vertices;
	std::vector<Vertex> vertices1;

	std::vector<uint32_t> indices;
	std::vector<uint32_t> indices1;

	std::vector<Mesh> meshes{};

	Camera camera{};
	Scene scene{};

public:

	void create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager);

	Scene& getScene();
};