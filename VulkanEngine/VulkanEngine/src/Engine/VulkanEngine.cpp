#include "VulkanEngine.h"

// _____________Private_____________
void VulkanEngine::windowInit()
{
	if (!glfwInit())
		throw std::runtime_error("Failed to initialize GLFW\n");

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window = glfwCreateWindow
	(
		2560,
		1440,
		"Vulkan Engine",
		nullptr,
		nullptr
	);

	if (!window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create window\n");
	}

	std::cout << "Window created successfully!\n";
}

void VulkanEngine::vulkanInit()
{
	createInstance();
	createSurface();
	selectPhysicalDevice();
	createLogicalDevice();

	swapChain.create
	(
		physicalDevice, 
		device, 
		surface, 
		window, 
		queueFamilyIndices.graphicsFamily.value(), 
		queueFamilyIndices.presentFamily.value(),
		swapChainSupportDetails
	);
}

void VulkanEngine::cleanupGlfw()
{
	if(window)
		glfwDestroyWindow(window);

	glfwTerminate();
}

void VulkanEngine::cleanupVulkan()
{
	if(vkInstance != VK_NULL_HANDLE)
		vkDestroyInstance(vkInstance, nullptr);
}

void VulkanEngine::cleanupSurface()
{
	if (surface != VK_NULL_HANDLE)
	{
		vkDestroySurfaceKHR(vkInstance, surface, nullptr);

		surface = VK_NULL_HANDLE;
	}
}

void VulkanEngine::cleanupDevice()
{
	if (device != VK_NULL_HANDLE)
	{
		vkDestroyDevice(device, nullptr);
		device = VK_NULL_HANDLE;
	}
}

void VulkanEngine::createInstance()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	if (!glfwExtensions)
		throw std::runtime_error("Failed to get GLFW Vulkan extensions");

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "VulkanEngine";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "MyEngine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_3;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;

	if (enableValidationLayers && !checkValidationLayerSupport())
	{
		throw std::runtime_error("Validation layers requested but not available!\n");
	}

	if (vkCreateInstance(&createInfo, nullptr, &vkInstance) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Vulkan instance!\n");
	}

	std::cout << "Vulkan instance created!\n";
}

void VulkanEngine::createSurface()
{
	if (glfwCreateWindowSurface(vkInstance, window, nullptr, &surface) != VK_SUCCESS)
		throw std::runtime_error("Failed to create window surface!\n");

	std::cout << "Surface created!\n";
}

void VulkanEngine::selectPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr);

	if (deviceCount == 0)
		throw std::runtime_error("Failed to find physical devices!\n");

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(vkInstance, &deviceCount, devices.data());

	std::cout << "Found: " << deviceCount << " physical devices.\n";

	for (const auto& device : devices)
	{
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(device, &properties);

		std::cout << properties.deviceName << "\n";
	}

	for (const auto& device : devices)
	{
		auto indices = findQueueFamilies(device);
		auto swapSupport = swapChain.isDeviceSuitable(device, surface);

		if (indices.isComplete() && swapSupport.suitable)
		{
			physicalDevice = device;
			queueFamilyIndices = indices;
			swapChainSupportDetails = swapSupport.swapChainSupport;

			return;
		}
	}

	throw std::runtime_error("Failed to find a suitable GPU!\n");
}

void VulkanEngine::createLogicalDevice()
{
	std::set<uint32_t> uniqueQueueFamilies = 
	{ 
		queueFamilyIndices.graphicsFamily.value(), 
		queueFamilyIndices.presentFamily.value() 
	};

	float queuePriority = 1.0f;
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

	for (uint32_t queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo{};

		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;

		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceCreateInfo createInfo{};

	createInfo.enabledExtensionCount = static_cast<uint32_t>(swapChain.deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = swapChain.deviceExtensions.data();

	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());

	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.pEnabledFeatures = &deviceFeatures;

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
		throw std::runtime_error("Failed to create logical device!\n");

	std::cout << "Logical device created!\n";

	vkGetDeviceQueue(device, queueFamilyIndices.graphicsFamily.value(), 0, &graphicsQueue);
	vkGetDeviceQueue(device, queueFamilyIndices.presentFamily.value(), 0, &presentQueue);

	std::cout << "Graphics Queue Family: " << queueFamilyIndices.graphicsFamily.value() << "\n";
	std::cout << "Present Queue Family: " << queueFamilyIndices.presentFamily.value() << "\n";
}

void VulkanEngine::drawFrame()
{

}

bool VulkanEngine::checkValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers)
	{
		bool found = false;

		for (const auto& layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
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

VulkanEngine::QueueFamilyIndices VulkanEngine::findQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;

	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);

	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	std::cout << "Queue Families: " << queueFamilyCount << "\n";

	for (uint32_t i = 0; i < queueFamilies.size(); i++)
	{
		std::cout << "Family: " << i << " flags: " << queueFamilies[i].queueFlags << "\n";
	}

	uint32_t i = 0;

	for (const auto& queueFamily : queueFamilies)
	{
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			indices.graphicsFamily = i;

		VkBool32 presentSupport = false;

		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

		if (presentSupport)
			indices.presentFamily = i;

		if (indices.isComplete())
			return indices;

		i++;
	}

	return indices;
}

// _____________Public_____________
VulkanEngine::~VulkanEngine()
{
	swapChain.cleanup(device);
	cleanupDevice();
	cleanupSurface();
	cleanupVulkan();
	cleanupGlfw();
}

void VulkanEngine::init()
{
	windowInit();
	vulkanInit();
}

void VulkanEngine::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}
