#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "Engine/Rendering/SwapChain.h"
#include "Engine/Rendering/RenderPass.h"
#include "Engine/Rendering/FramebufferManager.h"

#include "Utility/DebugMessenger.h"

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

	SwapChain swapChain{};
	RenderPass renderPass{};
	FramebufferManager framebufferManager{};
	DebugMessenger debugMessenger{};

	SwapChainSupportDetails swapChainSupportDetails;

	GLFWwindow* window = nullptr;
	VkInstance vkInstance = VK_NULL_HANDLE;
	VkSurfaceKHR surface = VK_NULL_HANDLE;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	VkDevice device = VK_NULL_HANDLE;
	VkQueue graphicsQueue = VK_NULL_HANDLE;
	VkQueue presentQueue = VK_NULL_HANDLE;

	QueueFamilyIndices queueFamilyIndices;

	void windowInit();
	void vulkanInit();

	void cleanupGlfw();
	void cleanupVulkan();
	void cleanupSurface();
	void cleanupDevice();

	void createInstance();
	void createSurface();
	void selectPhysicalDevice();
	void createLogicalDevice();
	void drawFrame();

	bool checkValidationLayerSupport();
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

public:

	VulkanEngine() = default;
	~VulkanEngine();

	VulkanEngine(VulkanEngine&) = delete;
	VulkanEngine& operator=(const VulkanEngine&) = delete;

	VulkanEngine(VulkanEngine&&) = delete;
	VulkanEngine& operator=(VulkanEngine&&) = delete;

	void init();
	void run();
};