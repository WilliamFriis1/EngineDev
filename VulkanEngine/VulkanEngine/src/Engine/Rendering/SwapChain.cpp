#include "SwapChain.h"

// _____________Private_____________

void SwapChain::createImageViews(VkDevice device)
{
	imageViews.resize(images.size());


	for (size_t i = 0; i < images.size(); i++)
	{
		VkImageViewCreateInfo createInfo{};

		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = images[i];

		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = imageFormat;

		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;

		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(device, &createInfo, nullptr, &imageViews[i]) != VK_SUCCESS)
			throw std::runtime_error("Failed to create image view");

	}
}

SwapChainSupportDetails SwapChain::querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
{
	SwapChainSupportDetails details{};

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);


	uint32_t formatCount;

	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

	if (formatCount == 0)
	{
		throw std::runtime_error("No surface formats found!\n");
	}
	else
	{
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;

	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

	if (presentModeCount == 0)
	{
		throw std::runtime_error("No present modes found!\n");
	}
	else
	{
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
	}

	return details;
}

bool SwapChain::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	for (auto& extensionName : deviceExtensions)
	{
		bool found = false;

		for (auto& extentionProperty : availableExtensions)
		{
			if (strcmp(extensionName, extentionProperty.extensionName) == 0)
			{
				found = true;
				break;
			}
		}

		if (!found)
			return false;
	}

	return true;

}

// _____________Public_____________
void SwapChain::create(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface, GLFWwindow* window, uint32_t graphicsFamily, uint32_t presentFamily, const SwapChainSupportDetails &details)
{
	auto surfaceFormat = chooseSurfaceFormat(details.formats);
	auto presentMode = choosePresentMode(details.presentModes);
	auto imageCount = details.capabilities.minImageCount + 1;

	imageFormat = surfaceFormat.format;
	extent = chooseExtent(window, details.capabilities);

	if (details.capabilities.maxImageCount > 0 && imageCount > details.capabilities.maxImageCount)
		imageCount = details.capabilities.maxImageCount;

	VkSwapchainCreateInfoKHR createInfo{};

	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;

	createInfo.surface = surface;
	createInfo.minImageCount = imageCount;
	
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;

	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;

	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	if (graphicsFamily != presentFamily)
	{
		uint32_t queueFamilyIndices[] = { graphicsFamily, presentFamily };

		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;

		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;
	}

	createInfo.preTransform = details.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;

	createInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS)
		throw std::runtime_error("Unable to create swapchain!\n");

	std::cout << "Swapchain successfully created!\n";


	uint32_t imageCounter;

	vkGetSwapchainImagesKHR(device, swapChain, &imageCounter, nullptr);

	images.resize(imageCount);

	vkGetSwapchainImagesKHR(device, swapChain, &imageCounter, images.data());

	std::cout << "Retrieved " << imageCount << " swapchain images\n";

	createImageViews(device);
}

void SwapChain::cleanup(VkDevice device)
{
	for (auto imageView : imageViews)
	{
		vkDestroyImageView(device, imageView, nullptr);
	}

	vkDestroySwapchainKHR(device, swapChain, nullptr);
}




DeviceSuitability SwapChain::isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface)
{
	auto details = querySwapChainSupport(device, surface);
	bool suitable = checkDeviceExtensionSupport(device) && !details.formats.empty() && !details.presentModes.empty();

	return DeviceSuitability{ suitable, details };
}

VkSurfaceFormatKHR SwapChain::chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats)
{
	if (formats.empty())
		throw std::runtime_error("Format vector is empty!\n");

	for (const auto& format : formats)
	{
		if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			return format;
	}

	return formats[0];
}

VkPresentModeKHR SwapChain::choosePresentMode(const std::vector<VkPresentModeKHR>& presentModes)
{
	if (presentModes.empty())
		throw std::runtime_error("Present modes vector is empty!\n");

	for (const auto& mode : presentModes)
	{
		if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
			return mode;
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D SwapChain::chooseExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities)
{
	if (capabilities.currentExtent.width != UINT32_MAX)
		return capabilities.currentExtent;

	int width, height;

	glfwGetFramebufferSize(window, &width, &height);

	VkExtent2D extent =
	{
		static_cast<uint32_t>(width),
		static_cast<uint32_t>(height)
	};

	extent.width = std::clamp(extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
	extent.height = std::clamp(extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

	return extent;
}
