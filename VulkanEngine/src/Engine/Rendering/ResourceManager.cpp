#include "ResourceManager.h"



void ResourceManager::create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager)
{
 
}

std::weak_ptr<VertexBuffer> ResourceManager::getVertexBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size)
{
	auto buffer = std::make_shared<VertexBuffer>();

	vertexBuffers.emplace_back(buffer);

	vertexBuffers.back().get()->create(physicalDevice, device, size);

	return vertexBuffers.back();
}
