#pragma once

#include "transferManager.h"

#include "Engine/Resources/mesh.h"
#include "Engine/Resources/uniformBuffer.h"
#include "Engine/Resources/storageBuffer.h"
#include "Engine/Rendering/Graphics/RenderingTypes/objectData.h"
#include "Engine/Rendering/Graphics/RenderingTypes/cameraData.h"
#include "Engine/Rendering/Graphics/VertexTypes/vertex.h"
#include "Scene/camera.h"
#include "Scene/scene.h"


class ResourceManager
{
private:
	//TEMP
	std::vector<Vertex> vertices;
	std::vector<Vertex> vertices1;

	std::vector<uint32_t> indices;
	std::vector<uint32_t> indices1;

	std::vector<Mesh> meshes{};

	Camera camera{};
	Scene scene{};
	//

public:
	void create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager);

	Scene& getScene();
};