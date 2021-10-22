#pragma once
#include <iostream>
#include <vector>

enum class ShaderType
{
	Fragment,
	Vertex,
	Compute, // Currently unsupported.
	Geometry, // Currently unsupported.
	Pixel // Currently unsupported.
};

enum class CarboniteAssetType
{
	Item,
	Block,
	Entity,
	Recipe
};

class Asset
{
	unsigned int AssetID;
};

class ShaderAsset : Asset
{
	std::string ShaderPath;
	ShaderType Type;
};

class CarboniteAsset : Asset
{
	std::string AssetPath;
	CarboniteAssetType typePath;
};

class AssetManager
{
protected:
	std::vector<Asset> LoadedAssets;
public:
	void Load();
	Asset LoadAsset(std::string path);
	void UnloadAsset(Asset asset);
};