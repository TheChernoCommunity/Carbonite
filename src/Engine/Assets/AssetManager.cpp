#include "AssetManager.h"

namespace gp1::assets
{
	//Asset Class
	Asset::Asset(AssetType type, const char* path) {
		a_type        = type;
		a_pathToAsset = path;
	}
	void Asset::WriteToAssetFile(const char* wstr)
	{
		std::ofstream ofstm(a_pathToAsset);
		ofstm.write(wstr, strlen(wstr));
		ofstm.close();
	}
	const char* Asset::ReadAssetFile() {
		std::string   content;
		std::ifstream strm(a_pathToAsset);
		content.assign((std::istreambuf_iterator<char>(strm)),
		               (std::istreambuf_iterator<char>()));
		strm.close();
		return content.c_str();
	}

	//AssetManager Class
	Asset AssetManager::loadAsset(AssetType type, const char* path) {
		Asset asset = Asset(type, path);
		loadedAssets.push_back(asset);
	}
	void AssetManager::removeAsset(Asset asset) {
		loadedAssets.erase(std::find(loadedAssets.begin(), loadedAssets.end(), asset));
	}
}