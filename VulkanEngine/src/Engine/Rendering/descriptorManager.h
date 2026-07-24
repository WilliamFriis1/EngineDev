#pragma once

#include <vulkan/vulkan.h>
#include "Engine/Resources/uniformBuffer.h"

#include <iostream>

class DescriptorManager
{
private:
	VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
	VkDescriptorSet descriptorSet = VK_NULL_HANDLE;
	VkDescriptorSetLayout descriptorSetLayout = VK_NULL_HANDLE;

public:
	VkDescriptorSetLayout getDescriptorLayout() const;
	VkDescriptorSet getDescriptorSet() const;

	void create(VkDevice device);
	void cleanup(VkDevice device);

	void update(VkDevice device, const UniformBuffer& uniformBuffer);

};