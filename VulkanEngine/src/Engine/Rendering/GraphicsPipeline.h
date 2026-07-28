#pragma once

#include "Utility/assetLoader.h"
#include "Engine/Rendering/Graphics/VertexTypes/vertex.h"
#include "Engine/Rendering/Graphics/RenderingTypes/pushconstantData.h"

#include <vulkan/vulkan.h>

class GraphicsPipeline
{
private:

	AssetLoader assetLoader{};

	VkPipeline graphicsPipeline = VK_NULL_HANDLE;
	VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;

public:
	//Getters
	VkPipeline get() const;
	VkPipelineLayout getLayout() const;

	GraphicsPipeline() = default;
	~GraphicsPipeline() = default;

	void create(VkDevice device, VkExtent2D extent, VkRenderPass renderPass, VkDescriptorSetLayout descriptorLayout);
	void cleanup(VkDevice device);
};
