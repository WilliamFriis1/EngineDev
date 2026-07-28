#pragma once

#include "Engine/Rendering/renderPass.h"
#include "Engine/Rendering/framebufferManager.h"
#include "Engine/Rendering/graphicsPipeline.h"
#include "Engine/Rendering/descriptorManager.h"
#include "Engine/Rendering/swapchain.h"
#include "Engine/Rendering/commandBufferManager.h"
#include "Engine/Rendering/syncManager.h"
#include "Engine/Rendering/commandPool.h"

#include "Engine/Rendering/Graphics/RenderingTypes/includes.h"
#include "Engine/Resources/uniformBuffer.h"
#include "Engine/Resources/storageBuffer.h"

#include "Scene/scene.h"

#include <vulkan/vulkan.h>
#include <iostream>

class Renderer
{
private:
	//Owned
	GraphicsPipeline graphicsPipeline{};
	RenderPass renderPass{};

	FramebufferManager framebufferManager{};
	DescriptorManager descriptorManager{};

	SyncManager syncManager{};
	CommandBufferManager commandBufferManager{};

	UniformBuffer cameraBuffer{};
	StorageBuffer objectBuffer{};
	StorageBuffer materialBuffer{};

	std::vector<StorageBuffer> storageBuffers;

	uint32_t currentFrame = 0;

	//References
	VkDevice device;
	Swapchain* swapchain;

	VkQueue graphicsQueue;
	VkQueue presentQueue;


	void record(uint32_t imageIndex, const RenderQueue& renderQueue, const std::vector<ObjectData>& objs, const std::vector<MaterialData>& materials, const Camera& camera);
public:

	enum DrawStatus
	{
		DRAW_SUCCESS,
		DRAW_FAIL
	};

	void create(VkPhysicalDevice physicalDevice, VkDevice device, Swapchain* swapChain, const CommandPool& commandPool, VkQueue graphicsQueue, VkQueue presentQueue, uint32_t maxObjects, uint32_t maxMaterials);
	void cleanup();
	void createSwapchainResources();
	void destroySwapchainResources();
	DrawStatus drawFrame(const RenderQueue& renderQueue, const std::vector<ObjectData>& objs, const std::vector<MaterialData>& materials, const Camera& camera);
};