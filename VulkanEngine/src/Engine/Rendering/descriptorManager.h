#pragma once

#include <vulkan/vulkan.h>
#include "Engine/Resources/uniformBuffer.h"
#include "Engine/Resources/storageBuffer.h"

#include <iostream>
#include <vector>

class DescriptorManager
{
private:
	VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
	VkDescriptorSet descriptorSet = VK_NULL_HANDLE;
	VkDescriptorSetLayout descriptorSetLayout = VK_NULL_HANDLE;

public:
	VkDescriptorSetLayout getDescriptorLayout() const;
	VkDescriptorSet* getDescriptorSet();

	void create(VkDevice device);

	void cleanup(VkDevice device);

	void update(VkDevice device, const UniformBuffer& uniformBuffer, const std::vector<StorageBuffer>& storageBuffer);

};