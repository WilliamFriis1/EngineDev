#pragma once

#include "transferManager.h"

#include "Engine/Resources/mesh.h"
#include "Engine/Resources/uniformBuffer.h"
#include "Engine/Resources/storageBuffer.h"
#include "Engine/Resources/vertexBuffer.h"
#include "Engine/Resources/indexBuffer.h"


#include <vulkan/vulkan.h>
#include <vector>


class ResourceManager
{
private:
	std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
	std::vector<std::shared_ptr<IndexBuffer>> indexBuffers;
	std::vector<std::shared_ptr<Mesh>> meshes;

public:
	void create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager);
	std::weak_ptr<VertexBuffer> getVertexBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size);
};