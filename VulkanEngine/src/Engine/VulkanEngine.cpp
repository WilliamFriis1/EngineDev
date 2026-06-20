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

	glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, VulkanEngine::glfwFramebufferResized);
}

void VulkanEngine::vulkanInit()
{
	createInstance();
	debugMessenger.setupDebugMessenger(vkInstance);
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

	renderPass.create(device, swapChain.getImageFormat());

	framebufferManager.createFramebuffers
	(
		device,
		renderPass.get(),
		swapChain.getImageViews(),
		swapChain.getExtents()
	);

	graphicsPipeline.create(device, swapChain.getExtents(), renderPass.get());

	commandPool.create(device, queueFamilyIndices.graphicsFamily.value());

	commandBufferManager.create(device, commandPool.get(), static_cast<uint32_t>(framebufferManager.getCount()));

	commandBufferManager.record(renderPass.get(), swapChain.getExtents(), graphicsPipeline.get(), graphicsPipeline.getLayout(), framebufferManager.get());

	createSyncObjects();
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

void VulkanEngine::cleanupSyncObjects()
{
	if (inFlightFence != VK_NULL_HANDLE)
		vkDestroyFence(device, inFlightFence, nullptr);

	if (renderFinishedSemaphore != VK_NULL_HANDLE)
		vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);

	if (imageAvailableSemaphore != VK_NULL_HANDLE)
		vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);

	inFlightFence = VK_NULL_HANDLE;
	renderFinishedSemaphore = VK_NULL_HANDLE;
	imageAvailableSemaphore = VK_NULL_HANDLE;
}

void VulkanEngine::createInstance()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	if (!glfwExtensions)
		throw std::runtime_error("Failed to get GLFW Vulkan extensions");

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

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

		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

	debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

	debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

	debugCreateInfo.pfnUserCallback = DebugMessenger::VulkanDebugCallback;

	if (enableValidationLayers)
		createInfo.pNext = &debugCreateInfo;
	else
		createInfo.pNext = nullptr;

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

void VulkanEngine::createSyncObjects()
{
	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS)
		throw std::runtime_error("Failed to create image available semaphore");

	if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS)
		throw std::runtime_error("Failed to create render finished semaphore");

	if (vkCreateFence(device, &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS)
		throw std::runtime_error("Failed to create fence");
}

void VulkanEngine::drawFrame()
{
	uint32_t imageIndex;

	vkWaitForFences(device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
	vkResetFences(device, 1, &inFlightFence);

	VkResult result = vkAcquireNextImageKHR(device, swapChain.get(), UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		recreateSwapChain();
		return;
	}

	VkCommandBuffer commandBuffer = commandBufferManager.get()[imageIndex];

	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &imageAvailableSemaphore;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &renderFinishedSemaphore;

	if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFence) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to submit draw command buffer");
	}

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &renderFinishedSemaphore;;

	VkSwapchainKHR swapChains[] = { swapChain.get() };

	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;

	result = vkQueuePresentKHR(presentQueue, &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || isFramebufferResized)
	{
		isFramebufferResized = false;
		recreateSwapChain();
	}

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

void VulkanEngine::recreateSwapChain()
{
	std::cout << "Started recreation of swapchain...\n";
	vkDeviceWaitIdle(device);

	framebufferManager.cleanupFramebuffers(device);
	swapChain.cleanup(device);

	swapChainSupportDetails = swapChain.isDeviceSuitable(physicalDevice, surface).swapChainSupport;

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

	framebufferManager.createFramebuffers
	(
		device,
		renderPass.get(),
		swapChain.getImageViews(),
		swapChain.getExtents()
	);
}

void VulkanEngine::glfwFramebufferResized(GLFWwindow* window, int width, int height)
{
	auto engine = static_cast<VulkanEngine*>(glfwGetWindowUserPointer(window));

	engine->isFramebufferResized = true;
}

// _____________Public_____________
VulkanEngine::~VulkanEngine()
{
	cleanupSyncObjects();
	commandBufferManager.cleanup();
	commandPool.cleanup(device);
	graphicsPipeline.cleanup(device);
	framebufferManager.cleanupFramebuffers(device);
	renderPass.cleanup(device);
	swapChain.cleanup(device);

	cleanupDevice();
	cleanupSurface();

	debugMessenger.cleanupDebugMessenger(vkInstance);

	cleanupVulkan();
	cleanupGlfw();
}

void VulkanEngine::init()
{
	AssetManager::init();

	windowInit();
	vulkanInit();
}

void VulkanEngine::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		drawFrame();
	}
}


