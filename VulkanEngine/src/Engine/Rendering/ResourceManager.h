#pragma once

#include "TransferManager.h"
#include "Engine\Resources\VertexBuffer.h"
#include "Engine\Resources\StagingBuffer.h"

class ResourceManager
{
	VertexBuffer vertBuff{};

public:
	void create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager);

	void cleanup();
};