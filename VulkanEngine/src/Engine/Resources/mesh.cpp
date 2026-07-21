#include "mesh.h"

VkBuffer Mesh::getVertexBuffer() const
{
    return vertexBuffer.get();
}

VkBuffer Mesh::getIndexBuffer() const
{
    return indexBuffer.get();
}

uint32_t Mesh::getIndexCount() const
{
    return indexCount;
}

void Mesh::create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
{
    indexCount = static_cast<uint32_t>(indices.size());

    VkDeviceSize sizeVert = sizeof(vertices[0]) * vertices.size();
    VkDeviceSize sizeIndex = sizeof(indices[0]) * indices.size();
    VkDeviceSize sizeStage = std::max(sizeVert, sizeIndex);

    vertexBuffer.create(physicalDevice, device, sizeVert);
    indexBuffer.create(physicalDevice, device, sizeIndex);

    StagingBuffer stageBuff{};

    stageBuff.create(physicalDevice, device, sizeStage);

    stageBuff.upload(vertices.data());

    transferManager.copyBuffer(stageBuff.get(), vertexBuffer.get(), sizeVert);

    stageBuff.upload(indices.data());

    transferManager.copyBuffer(stageBuff.get(), indexBuffer.get(), sizeIndex);

    stageBuff.cleanup();
}

void Mesh::cleanup()
{
    vertexBuffer.cleanup();
    indexBuffer.cleanup();
}