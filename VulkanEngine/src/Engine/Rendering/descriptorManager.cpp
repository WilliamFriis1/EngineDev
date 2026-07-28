#include "descriptorManager.h"

VkDescriptorSetLayout DescriptorManager::getDescriptorLayout() const
{
	return descriptorSetLayout;
}

VkDescriptorSet* DescriptorManager::getDescriptorSet()
{
	return &descriptorSet;
}

void DescriptorManager::create(VkDevice device)
{
	VkDescriptorSetLayoutBinding bindings[3]{};

	bindings[0].binding = 0;
	bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	bindings[0].descriptorCount = 1;
	bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	bindings[1].binding = 1;
	bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	bindings[1].descriptorCount = 1;
	bindings[1].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	bindings[2].binding = 2;
	bindings[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	bindings[2].descriptorCount = 1;
	bindings[2].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

	VkDescriptorSetLayoutCreateInfo descriptorLayoutInfo{};
	descriptorLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;

	descriptorLayoutInfo.bindingCount = 3;
	descriptorLayoutInfo.pBindings = bindings;

	if (vkCreateDescriptorSetLayout(device, &descriptorLayoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
		throw std::runtime_error("Failed to create descriptor set layout");

	VkDescriptorPoolSize poolSizes[2]{};

	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = 1;

	poolSizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	poolSizes[1].descriptorCount = 2;

	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;

	poolInfo.poolSizeCount = 2;
	poolInfo.pPoolSizes = poolSizes;

	poolInfo.maxSets = 1;

	if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS)
		throw std::runtime_error("Failed to create descriptor pool");

	VkDescriptorSetAllocateInfo allocInfo{};

	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;

	allocInfo.descriptorPool = descriptorPool;
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = &descriptorSetLayout;

	if (vkAllocateDescriptorSets(device, &allocInfo, &descriptorSet) != VK_SUCCESS)
		throw std::runtime_error("Failed to allocate descriptor sets");
}

void DescriptorManager::cleanup(VkDevice device)
{
	if (descriptorPool != VK_NULL_HANDLE)
	{
		vkDestroyDescriptorPool(device, descriptorPool, nullptr);

		descriptorPool = VK_NULL_HANDLE;
	}

	if (descriptorSetLayout != VK_NULL_HANDLE)
	{
		vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);

		descriptorSetLayout = VK_NULL_HANDLE;
	}
}

void DescriptorManager::update(VkDevice device, const UniformBuffer& uniformBuffer, const std::vector<StorageBuffer>& storageBuffer)
{
	if (descriptorPool == VK_NULL_HANDLE)
		return;

	VkDescriptorBufferInfo bufferInfo[3]{};

	bufferInfo[0].buffer = uniformBuffer.get();
	bufferInfo[0].offset = 0;
	bufferInfo[0].range = uniformBuffer.getSize();

	bufferInfo[1].buffer = storageBuffer[0].get();
	bufferInfo[1].offset = 0;
	bufferInfo[1].range = storageBuffer[0].getSize();

	bufferInfo[2].buffer = storageBuffer[1].get();
	bufferInfo[2].offset = 0;
	bufferInfo[2].range = storageBuffer[1].getSize();

	VkWriteDescriptorSet writeSet[3]{};
	writeSet[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

	writeSet[0].descriptorCount = 1;
	writeSet[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	writeSet[0].dstArrayElement = 0;

	writeSet[0].dstBinding = 0;
	writeSet[0].dstSet = descriptorSet;
	writeSet[0].pBufferInfo = &bufferInfo[0];

	writeSet[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

	writeSet[1].descriptorCount = 1;
	writeSet[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	writeSet[1].dstArrayElement = 0;

	writeSet[1].dstBinding = 1;
	writeSet[1].dstSet = descriptorSet;
	writeSet[1].pBufferInfo = &bufferInfo[1];

	writeSet[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

	writeSet[2].descriptorCount = 1;
	writeSet[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	writeSet[2].dstArrayElement = 0;

	writeSet[2].dstBinding = 2;
	writeSet[2].dstSet = descriptorSet;
	writeSet[2].pBufferInfo = &bufferInfo[2];

	vkUpdateDescriptorSets(device, 3, writeSet, 0, nullptr);
}
