#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "Engine/Rendering/SwapChain.h"
#include "Engine/Rendering/RenderPass.h"
#include "Engine/Rendering/FramebufferManager.h"
#include "Engine/Rendering/GraphicsPipeline.h"
#include "Engine/Rendering/CommandPool.h"
#include "Engine/Rendering/CommandBufferManager.h"
#include "Engine/Rendering/SyncManager.h"

#include "Utility/DebugMessenger.h"
#include "Utility/AssetManager.h"

#include <iostream>
#include <vector>
#include <optional>
#include <set>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class VulkanEngine
{
private:

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() const
		{
			return graphicsFamily.has_value() && presentFamily.has_value(); 
		}
	};

	const std::vector<const char*> validationLayers =
	{
		"VK_LAYER_KHRONOS_validation"
	};

	SyncManager syncManager{};
	CommandBufferManager commandBufferManager{};
	CommandPool commandPool{};
	GraphicsPipeline graphicsPipeline{};
	SwapChain swapChain{};
	RenderPass renderPass{};
	FramebufferManager framebufferManager{};
	DebugMessenger debugMessenger{};

	SwapChainSupportDetails swapChainSupportDetails;
	QueueFamilyIndices queueFamilyIndices;

	GLFWwindow* window = nullptr;

	VkInstance vkInstance = VK_NULL_HANDLE;
	VkSurfaceKHR surface = VK_NULL_HANDLE;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	VkDevice device = VK_NULL_HANDLE;
	VkQueue graphicsQueue = VK_NULL_HANDLE;
	VkQueue presentQueue = VK_NULL_HANDLE;

	uint32_t currentFrame = 0;

	//Initialization
	void windowInit();
	void vulkanInit();

	//Cleanup
	void cleanupGlfw();
	void cleanupVulkan();
	void cleanupSurface();
	void cleanupDevice();

	//Create
	void createInstance();
	void createSurface();
	void selectPhysicalDevice();
	void createLogicalDevice();

	//Update
	void drawFrame();

	//Utility
	bool checkValidationLayerSupport();
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	void recreateSwapChain();

	//Callback
	static void glfwFramebufferResized(GLFWwindow* window, int width, int height);

public:

	bool isFramebufferResized = false;

	VulkanEngine() = default;
	~VulkanEngine();

	VulkanEngine(VulkanEngine&) = delete;
	VulkanEngine& operator=(const VulkanEngine&) = delete;

	VulkanEngine(VulkanEngine&&) = delete;
	VulkanEngine& operator=(VulkanEngine&&) = delete;

	void init();
	void run();

};