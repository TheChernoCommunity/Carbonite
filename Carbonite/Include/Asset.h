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

	static Asset load(std::string path);
};
