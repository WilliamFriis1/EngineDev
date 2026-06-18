#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <algorithm>

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector < VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct DeviceSuitability
{
	bool suitable;

	SwapChainSupportDetails swapChainSupport;
};

class SwapChain
{
private:

	VkSwapchainKHR swapChain = VK_NULL_HANDLE;

	std::vector<VkImage> images;
	std::vector<VkImageView> imageViews;

	VkFormat imageFormat;
	VkExtent2D extent;

	void createImageViews(VkDevice device);

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

public:
	const std::vector<const char*> deviceExtensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	//Getters
	VkFormat getImageFormat() const;
	VkExtent2D getExtents() const;
	std::vector<VkImageView> getImageViews() const;


	SwapChain() = default;
	~SwapChain() = default;

	void create(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface, GLFWwindow* window, uint32_t graphicsFamily, uint32_t presentFamily, const SwapChainSupportDetails &details);

	void cleanup(VkDevice device);

	DeviceSuitability isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

	VkSurfaceFormatKHR chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);

	VkPresentModeKHR choosePresentMode(const std::vector<VkPresentModeKHR>& presentModes);

	VkExtent2D chooseExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);
};
