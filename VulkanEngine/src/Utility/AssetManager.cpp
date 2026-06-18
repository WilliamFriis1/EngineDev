#include "AssetManager.h"

std::filesystem::path AssetManager::assetRoot;

void AssetManager::init()
{
    assetRoot = std::filesystem::path(ENGINE_ROOT) / "assets";

    if (!std::filesystem::exists(assetRoot))
    {
        throw std::runtime_error("Asset root not found: " + assetRoot.string());
    }

    std::cout << "[AssetManager] Root: " << assetRoot << "\n";
}

std::string AssetManager::getAssetPath(const std::string& relativePath)
{
	return (assetRoot / relativePath).string();
}