#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <queue>

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

	using AssetLoadCallback = std::function<void(AssetLoadResult)>;

	AssetLoadResult LoadAsset(AssetId assetId);
	void LoadAssetAsync(AssetId assetId, AssetLoadCallback callback);

private:
	AssetLoader();
	~AssetLoader(); // Maybe?

	AssetLoadResult LoadAssetFromFile(AssetId assetId);


	class Cache
	{
	public:
		AssetLoadResult LoadAsset(AssetId assetId);
		AssetLoadResult StoreAsset(AssetId assetId, const std::string& contents);
	private:
		std::mutex m_mutex;
		std::unordered_map<AssetId, std::string> m_cache;
	};

	Cache m_cache;

	std::thread m_loaderThread;
	void LoadAssetThreadFunc();

	struct AssetLoadRequest
	{
		AssetId id;
		AssetLoadCallback callback;
	};
	std::mutex m_loadQueueMutex;
	std::condition_variable m_loadQueueCv;
	std::queue<AssetLoadRequest> m_loadQueue;
};
};
