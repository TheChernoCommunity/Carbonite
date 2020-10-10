#include "Engine/Utility/AssetLoader.h"

#include <filesystem>
#include <iostream>
#include <fstream>

#include "Engine/Utility/Log.h"

namespace gp1
{
AssetLoader& AssetLoader::Get()
{
	static AssetLoader assetLoader;
	return assetLoader;
}

AssetLoader::AssetLoader()
{
}

AssetLoader::~AssetLoader()
{
}

AssetLoadResult AssetLoader::LoadAsset(AssetId assetId)
{
	AssetLoadResult cacheResult = m_cache.LoadAsset(assetId);
	if (cacheResult.success)
	{
		return cacheResult;
	}
	return LoadAssetFromFile(assetId);
}

AssetLoadResult AssetLoader::LoadAssetFromFile(AssetId assetId)
{
	std::filesystem::path path{ assetId };
	if (!std::filesystem::exists(path))
	{
		return AssetLoadResult{ assetId };
	}

	std::ifstream file(path, std::ios::in | std::ios::binary);
	if (!file)
	{
		return AssetLoadResult{ assetId };
	}

	file.seekg(0, file.end);
	size_t length = file.tellg();
	file.seekg(0, file.beg);

	std::string data;
	data.reserve(length);
	data.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	file.close();

	AssetLoadResult result = m_cache.StoreAsset(assetId, data);
	return result;
}

AssetLoadResult AssetLoader::Cache::LoadAsset(AssetId assetId)
{
	AssetLoadResult result;
	result.id = assetId;

	const auto& it = m_cache.find(assetId);
	if (it != m_cache.end())
	{
		result.success = true;
		result.data = it->second;
	}

	return result;
}

AssetLoadResult AssetLoader::Cache::StoreAsset(AssetId assetId, const std::string& contents)
{
	AssetLoadResult result;
	result.success = true;

	// Putting contents into the cache copies it
	// That copy will be around indefinitely
	// So it's safe to use for the AssetLoadResult string_view
	m_cache[assetId] = contents;
	result.data = m_cache[assetId];

	return result;
}
}
