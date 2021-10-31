#include "PCH.h"

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

Asset::Asset(std::string path)
{
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
			type = static_cast<uint32_t>(ShaderType::Vertex);
		}
		else if (extension == "tesc")
		{
			type = static_cast<uint32_t>(ShaderType::TessellationControl);
		}
		else if (extension == "tese")
		{
			type = static_cast<uint32_t>(ShaderType::TessellationEvaluation);
		}
		else if (extension == "geom")
		{
			type = static_cast<uint32_t>(ShaderType::Geometry);
		}
		else if (extension == "comp")
		{
			type = static_cast<uint32_t>(ShaderType::Compute);
		}
	}

	std::ifstream file(path);

	size = std::filesystem::file_size(path);
	data = std::shared_ptr<char[]>(new char[size]);
	id   = uniform_dist(engine);

	if (file.is_open())
	{
		file.read(data.get(), size);
	}

	file.close();
}