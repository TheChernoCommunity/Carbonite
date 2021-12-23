#include "PCH.h"

#include <filesystem>
#include <limits>
#include <random>

#include "Asset.h"

Asset::Asset(std::string path)
{
	// Get file extension
	std::string extension;

	for (int i = static_cast<int>(path.length()) - 1; i >= 0; i--)
	{
		if (path[i] == '.') break;
		extension = path[i] + extension;
	}

	if (path != extension)
	{
		if (extension == "vert")
		{
			type = static_cast<uint32_t>(ShaderType::Vertex);
		}
		else if (extension == "frag")
		{
			type = static_cast<uint32_t>(ShaderType::Fragment);
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

	std::ifstream file(path, std::ios::in | std::ios::binary);

	size = static_cast<std::uint32_t>(std::filesystem::file_size(path));
	data = std::shared_ptr<char[]>(new char[++size]);

	if (file.is_open())
	{
		file.read(data.get(), size);
	}

	data[size - 1] = '\0';

	file.close();
}