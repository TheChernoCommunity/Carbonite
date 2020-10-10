#pragma once

#include <string>
#include <unordered_map>

namespace gp1
{
using AssetId = std::string;

struct AssetLoadResult
{
	AssetId id = "";
	bool success = false;
	std::string_view data;
};

class AssetLoader
{
public:
	static AssetLoader& Get();

	AssetLoadResult LoadAsset(AssetId assetId);

private:
	AssetLoader();
	~AssetLoader();

	AssetLoadResult LoadAssetFromFile(AssetId assetId);

	class Cache
	{
	public:
		AssetLoadResult LoadAsset(AssetId assetId);
		AssetLoadResult StoreAsset(AssetId assetId, const std::string& contents);
	private:
		std::unordered_map<AssetId, std::string> m_cache;
	};
	Cache m_cache;
};
}
