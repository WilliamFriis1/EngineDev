#pragma once

#include "TransferManager.h"

#include "Engine\Resources\VertexBuffer.h"
#include "Engine\Resources\StagingBuffer.h"
#include "Engine\Core\Common.h"

class ResourceManager
{
private:
	VertexBuffer vertBuff{};
	std::vector<Vertex> vertices;

public:
	void create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager);

	void cleanup();

	//TEMP
	VkBuffer getVertexBuffer() const;
	uint32_t getVertCount() const;
};