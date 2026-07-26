#pragma once

#include <vulkan\vulkan.h>

#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "stagingBuffer.h"
#include "Engine/Rendering/transferManager.h"
#include "Engine/Rendering/Graphics/VertexTypes/vertex.h"
#include "Scene/transform.h"


class Mesh
{

private:
	VertexBuffer vertexBuffer{};
	IndexBuffer indexBuffer{};
	Transform transform{};

	uint32_t indexCount;
	uint32_t objectIndex;

public:
	Transform& getTransform();
	const uint32_t& getObjectIndex() const;

	void create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, uint32_t objectIndex);

	void cleanup();

	void draw(VkCommandBuffer cmd);
	void bind(VkCommandBuffer cmd);
};