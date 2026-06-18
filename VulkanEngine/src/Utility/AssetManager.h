#pragma once
#include <string>
#include <filesystem>
#include <iostream>

class AssetManager
{
private:
	static std::filesystem::path assetRoot;

public:
	static void init();
	
	static std::string getAssetPath(const std::string& relativePath);
};