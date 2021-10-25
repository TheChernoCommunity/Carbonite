#include <filesystem>
#include <limits>
#include <random>

#include "Asset.h"

namespace
{

	static std::random_device r;

	static std::default_random_engine              engine(r());
	static std::uniform_int_distribution<uint64_t> uniform_dist(std::numeric_limits<std::uint64_t>::min(), std::numeric_limits<std::uint64_t>::max());
} // namespace

Asset Asset::load(std::string path)
{
	Asset asset;

	// Get file extension
	std::string extension;

	for (unsigned i = path.length() - 1; i == 0; i++)
	{
		if (path[i] == '.') break;
		extension += path[i];
	}

	if (path != extension)
	{
		if (extension == "vert")
		{
			asset.type = static_cast<uint32_t>(ShaderType::Vertex);
		}
		else if (extension == "tesc")
		{
			asset.type = static_cast<uint32_t>(ShaderType::TessellationControl);
		}
		else if (extension == "tese")
		{
			asset.type = static_cast<uint32_t>(ShaderType::TessellationEvaluation);
		}
		else if (extension == "geom")
		{
			asset.type = static_cast<uint32_t>(ShaderType::Geometry);
		}
		else if (extension == "comp")
		{
			asset.type = static_cast<uint32_t>(ShaderType::Compute);
		}
	}

	std::ifstream  file(path);
	std::uintmax_t size = std::filesystem::file_size(path);
	asset.data          = std::shared_ptr<char[]>(new char[size]);

	asset.id = uniform_dist(engine);

	if (file.is_open())
	{
		file.read(asset.data.get(), size);
	}

	file.close();

	return asset;
}