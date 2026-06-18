#pragma once
#include <vulkan/vulkan.h>
#include <iostream>

class DebugMessenger
{
private:
	VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

public:

	void setupDebugMessenger(VkInstance instance)
	{
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

		debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;

		debugCreateInfo.pfnUserCallback = VulkanDebugCallback;

		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

 

		if (!func || func(instance, &debugCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create debug messenger!\n");
		}

		std::cout << "Successfully created runtime messenger\n";
	}

	void cleanupDebugMessenger(VkInstance instance)
	{
		if (debugMessenger != VK_NULL_HANDLE)
		{
			auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

			if (func)
				func(instance, debugMessenger, nullptr);

			debugMessenger = VK_NULL_HANDLE;
		}
	}

	static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* data, void* userData)
	{
		std::cerr << "[VULKAN] " << data->pMessage << "\n";
		return VK_FALSE;
	}
};