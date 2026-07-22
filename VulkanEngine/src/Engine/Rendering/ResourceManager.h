#pragma once

#include "transferManager.h"

#include "Engine\Core\common.h"
#include "Engine\Resources\mesh.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Engine/Resources/uniformBuffer.h"

//TEMP
struct TransformData
{
	glm::mat4 model;
};

class ResourceManager
{
private:
	std::vector<Vertex> vertices;
	std::vector<Vertex> vertices1;

	std::vector<uint32_t> indices;
	std::vector<uint32_t> indices1;

	std::vector<Mesh> meshes{};

	//TEMP
	UniformBuffer uniformBuffer{};

public:
	void create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager);

	std::vector<Mesh>& getMeshes();

	//TEMP
	UniformBuffer& getUniformBuffer();
};