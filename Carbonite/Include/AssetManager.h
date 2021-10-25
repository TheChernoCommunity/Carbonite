#pragma once

#include <cstdint>
#include <fstream>
#include <memory>
#include <string>

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
	Item = 12,
	Block,
	Entity,
	Recipe
};

struct Asset
{
	std::uint64_t           id;
	std::uint32_t           type;
	std::shared_ptr<char[]> data;
<<<<<<< HEAD:Carbonite/Include/Asset.h

	static Asset load(std::string path);
};
=======
};

namespace AssetManager
{
	Asset LoadAsset(std::string path);
	void  UnloadAsset(Asset asset);
} // namespace AssetManager
>>>>>>> ea9dfc7b3f47c22d7a0d73892c7fe7bfeef7162e:Carbonite/Include/AssetManager.h
