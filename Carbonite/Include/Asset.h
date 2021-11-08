#pragma once

#include <cstdint>
#include <fstream>
#include <memory>
#include <string>

#include <Utils/Identifiable.h>

enum class ShaderType
{
	Vertex = 4,
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

struct Asset : public Identifiable
{
	std::uint32_t           type;
	std::uint32_t           size;
	std::shared_ptr<char[]> data;

	Asset(std::string path);
};
