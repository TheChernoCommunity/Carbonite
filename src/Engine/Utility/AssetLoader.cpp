#include "Engine/Utility/AssetLoader.h"

#include <filesystem>
#include <iostream>
#include <fstream>

namespace gp1
{
AssetLoader& AssetLoader::Get()
{
	static AssetLoader assetLoader;
	return assetLoader;
}

AssetLoadResult AssetLoader::LoadAsset(AssetId assetId)
{
	AssetLoadResult cacheResult = LoadAssetFromCache(assetId);
	if (cacheResult.success)
	{
		return cacheResult;
	}
	return LoadAssetFromFile(assetId);
}

AssetLoadResult AssetLoader::LoadAssetFromFile(AssetId assetId)
{
	AssetLoadResult result;
	result.id = assetId;
	result.success = false;

	std::filesystem::path path{ assetId };
	if (!std::filesystem::exists(path))
	{
		return result;
	}

	std::ifstream file(path, std::ios::in | std::ios::binary);
	if (!file)
	{
		return result;
	}

	file.seekg(0, file.end);
	size_t length = file.tellg();
	file.seekg(0, file.beg);

	std::string data;
	data.reserve(length);
	data.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	file.close();

	m_assetCache[assetId] = data;
	// Can't use `result.data = data` here as `data` will get destroyed, invalidating the view
	// We want to use the long lasting string in the cache
	result.data = m_assetCache[assetId];
	result.success = true;
	return result;
}

AssetLoadResult AssetLoader::LoadAssetFromCache(AssetId assetId)
{
	AssetLoadResult result;
	result.id = assetId;

	const auto& it = m_assetCache.find(assetId);
	if (it != m_assetCache.end())
	{
		result.success = true;
		result.data = it->second;
	}

	return result;
}
};
