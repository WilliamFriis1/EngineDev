//TODO: Fix temp assingment to permanent
#pragma once

#include "Scene\entity.h"
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

	static std::vector<char> readFile(const std::string& filename);

	static VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);

	//TEST
	static std::vector<Vertex> readObj(const std::string& filename);
};