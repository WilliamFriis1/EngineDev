#pragma once

#include "transferManager.h"

#include "Engine\Core\common.h"
#include "Engine\Resources\mesh.h"

class ResourceManager
{
private:
	std::vector<Vertex> vertices;
	std::vector<Vertex> vertices1;

	std::vector<uint32_t> indices;
	std::vector<uint32_t> indices1;

	std::vector<Mesh> meshes{};

public:
	void create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager);

	std::vector<Mesh>& getMeshes();
};