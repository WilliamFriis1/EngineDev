#pragma once

#include "Utility/assetManager.h"

#include <vulkan/vulkan.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <vector>

class AssetLoader
{
private:

public:

	std::vector<char> readFile(const std::string& filename);

	VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);
};