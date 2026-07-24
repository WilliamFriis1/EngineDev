#pragma once

#include "transferManager.h"

#include "Engine/Resources/mesh.h"
#include "Engine/Resources/uniformBuffer.h"
#include "Engine/Rendering/Graphics/ShaderTypes/transformData.h"
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
	//

public:
	void create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager);

	//TEMP
	std::vector<Mesh>& getMeshes();
	UniformBuffer& getUniformBuffer();
	//
};