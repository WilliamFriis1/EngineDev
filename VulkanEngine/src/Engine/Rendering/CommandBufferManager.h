#pragma once
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

class CommandBufferManager
{
private:
	std::vector<VkCommandBuffer> commandBuffers;

public:
	const std::vector<VkCommandBuffer>& get() const;

	void create(VkDevice device, VkCommandPool commandPool, uint32_t count);

	void cleanup();

	void record(VkRenderPass renderPass, VkExtent2D extent, VkPipeline graphicsPipeline, VkPipelineLayout pipelineLayout, const std::vector<VkFramebuffer>& framebuffers);
};