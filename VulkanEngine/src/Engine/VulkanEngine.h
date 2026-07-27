#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "Engine/Rendering/swapChain.h"
#include "Engine/Rendering/commandPool.h"
#include "Engine/Rendering/transferManager.h"
#include "Engine/Rendering/resourceManager.h"
#include "Engine/Rendering/renderer.h"
#include "Engine/Rendering/renderQueue.h"
#include "Engine/Rendering/Graphics/RenderingTypes/objectData.h"

#include "Utility/debugMessenger.h"
#include "Utility/assetManager.h"

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

	ResourceManager resourceManager{};
	TransferManager transferManager{};
	CommandPool commandPool{};
	Swapchain swapchain{};
	Renderer renderer{};

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

	RenderQueue renderQueue{};
	std::vector<ObjectData> sceneObjs{};

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