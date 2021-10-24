#include <filesystem>

#include "AssetManager.h"

std::vector<char>& Asset::getData()
{
	return data;
}

Asset AssetManager::LoadAsset(std::string path)
{
	Asset asset;

	std::ifstream  file(path);
	std::uintmax_t size = std::filesystem::file_size(path);
	asset.data.resize(size);

	if (file.is_open())
	{
		file.read(asset.data.data(), size);
	}

	LoadedAssets.push_back(asset);

	return asset;
}