#pragma once
#include <vulkan/vulkan.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <vector>

#include "Utility/assetManager.h"
#include "Engine/Rendering/Graphics/VertexTypes/vertex.h"
#include "Engine/Rendering/Graphics/RenderingTypes/pushconstantData.h"

class GraphicsPipeline
{
private:

	VkPipeline graphicsPipeline = VK_NULL_HANDLE;
	VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;

	static std::vector<char> readFile(const std::string& filename);

	VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);

public:
	//Getters
	VkPipeline get() const;
	VkPipelineLayout getLayout() const;

	GraphicsPipeline() = default;
	~GraphicsPipeline() = default;

	void create(VkDevice device, VkExtent2D extent, VkRenderPass renderPass, VkDescriptorSetLayout descriptorLayout);
	void cleanup(VkDevice device);
};
