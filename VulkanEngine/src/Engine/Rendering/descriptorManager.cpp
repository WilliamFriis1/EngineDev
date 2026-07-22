#include "descriptorManager.h"

VkDescriptorSetLayout DescriptorManager::getDescriptorLayout() const
{
	return descriptorSetLayout;
}

VkDescriptorSet DescriptorManager::getDescriptorSet() const
{
	return descriptorSet;
}

void DescriptorManager::create(VkDevice device)
{
	VkDescriptorSetLayoutBinding uboLayoutBinding{};
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	VkDescriptorSetLayoutCreateInfo descriptorLayoutInfo{};
	descriptorLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;

	descriptorLayoutInfo.bindingCount = 1;
	descriptorLayoutInfo.pBindings = &uboLayoutBinding;

	if (vkCreateDescriptorSetLayout(device, &descriptorLayoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
		throw std::runtime_error("Failed to create descriptor set layout");

	VkDescriptorPoolSize poolSize{};

	poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSize.descriptorCount = 1;

	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;

	poolInfo.poolSizeCount = 1;
	poolInfo.pPoolSizes = &poolSize;

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

void DescriptorManager::update(VkDevice device, const UniformBuffer& uniformBuffer)
{
	VkDescriptorBufferInfo bufferInfo{};

	bufferInfo.buffer = uniformBuffer.get();
	bufferInfo.offset = 0;
	bufferInfo.range = sizeof(glm::mat4); //TEMP, size

	VkWriteDescriptorSet writeSet{};
	writeSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

	writeSet.descriptorCount = 1;
	writeSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	
	writeSet.dstArrayElement = 0;
	writeSet.dstBinding = 0;
	writeSet.dstSet = descriptorSet;

	writeSet.pBufferInfo = &bufferInfo;

	vkUpdateDescriptorSets(device, 1, &writeSet, 0, nullptr);
}
