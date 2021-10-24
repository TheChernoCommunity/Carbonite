#pragma once
#include <iostream>
#include <vector>

enum class ShaderType
{
	Vertex,
	TessellationControl,    // Currently unsupported.
	TessellationEvaluation, // Currently unsupported.
	Geometry,               // Currently unsupported.
	Fragment,
	Compute,        // Currently unsupported.
	RTRayGen,       // Currently unsupported.
	RTAnyHit,       // Currently unsupported.
	RTClosestHit,   // Currently unsupported.
	RTMiss,         // Currently unsupported.
	RTIntersection, // Currently unsupported.
	RTCallable      // Currently unsupported.
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
	ShaderType  Type;
};

class CarboniteAsset : Asset
{
	std::string        AssetPath;
	CarboniteAssetType typePath;
};

class AssetManager
{
protected:
	std::vector<Asset> LoadedAssets;

public:
	void  Load();
	Asset LoadAsset(std::string path);
	void  UnloadAsset(Asset asset);
};
