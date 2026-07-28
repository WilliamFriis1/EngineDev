#include "mesh.h"


void Mesh::create(VkPhysicalDevice physicalDevice, VkDevice device, TransferManager& transferManager, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, uint32_t materialIndex)
{
    this->materialIndex = materialIndex;

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

void Mesh::draw(VkCommandBuffer cmd)
{
    vkCmdDrawIndexed(cmd, indexCount, 1, 0, 0, 0);
}

void Mesh::bind(VkCommandBuffer cmd)
{
    VkBuffer buffers[] = { vertexBuffer.get()};
    VkDeviceSize offsets[] = { 0 };

    vkCmdBindVertexBuffers(cmd, 0, 1, buffers, offsets);
    vkCmdBindIndexBuffer(cmd, indexBuffer.get(), 0, VK_INDEX_TYPE_UINT32);
}
