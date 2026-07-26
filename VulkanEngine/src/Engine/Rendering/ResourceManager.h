#pragma once

#include "transferManager.h"

#include "Engine/Resources/mesh.h"
#include "Engine/Resources/uniformBuffer.h"
#include "Engine/Resources/storageBuffer.h"
#include "Engine/Rendering/Graphics/ShaderTypes/objectData.h"
#include "Engine/Rendering/Graphics/ShaderTypes/cameraData.h"
#include "Engine/Rendering/Graphics/VertexTypes/vertex.h"
#include "Scene/camera.h"


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
	UniformBuffer uniformBuffer{};
	StorageBuffer storageBuffer{};

	std::vector<ObjectData> objectData{};
	//

public:
	void create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager);

	//TEMP
	std::vector<Mesh>& getMeshes();
	std::vector<ObjectData>& getObjects();
	UniformBuffer& getUniformBuffer();
	StorageBuffer& getStorageBuffer();
	Camera& getCamera();
	//
};