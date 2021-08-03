#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

namespace gp1::assets
{
	enum class AssetType
	{
		NormalFile,
		ShaderVS,
		ShaderFS,
		ShaderGS,
		ShaderPS
	};

	class Asset
	{
	public:
		AssetType   a_type;
		const char* a_pathToAsset;

		std::string ReadAssetFile();

		void WriteToAssetFile(const char* wstr);

		Asset(AssetType type, const char* path);
	};

	class AssetManager
	{		
	public:
		static std::vector<Asset> loadedAssets;
		static Asset loadAsset(AssetType type, const char* path);
		static void removeAsset(Asset asset);
	};

} // namespace gp1::assets