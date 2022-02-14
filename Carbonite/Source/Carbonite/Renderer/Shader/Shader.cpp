#include "Shader.h"
#include "Graphics/Device/Device.h"

#include "GLSLang.h"
#include "Utils/FileIO.h"
#include "Utils/Utils.h"

#include <fstream>

static Graphics::EShaderType getShaderTypeFromFile(const std::filesystem::path& file)
{
	auto extension = file.extension();
	if (extension == ".vert")
		return Graphics::EShaderType::Vertex;
	else if (extension == ".frag")
		return Graphics::EShaderType::Fragment;
	return Graphics::EShaderType::Compute;
}

Shader::Shader(Graphics::Device& device)
    : m_ShaderModule(device) {}

void Shader::updateShader()
{
	bool createShaderModule = false;

	std::filesystem::path cacheFilePath = FileIO::getGameDir() / "Temp/Shaders" / m_ShaderFile;
	cacheFilePath += ".cache";
	if (std::filesystem::exists(cacheFilePath))
	{
		std::ifstream cacheFile { cacheFilePath, std::ios::ate | std::ios::binary };
		if (cacheFile)
		{
			std::size_t cacheFileLength = static_cast<std::size_t>(cacheFile.tellg());
			if (cacheFileLength >= 8)
			{
				cacheFile.seekg(0);

				std::uint64_t cachedTime;
				std::uint32_t shaderType;
				cacheFile.read(reinterpret_cast<char*>(&cachedTime), 8);
				cacheFile.read(reinterpret_cast<char*>(&shaderType), 4);

				std::uint64_t lastWriteTime = FileIO::gameFileLastWriteTime(m_ShaderFile);
				if (cachedTime == lastWriteTime)
				{
					m_ShaderModule.m_Code.resize(Utils::alignFloor(cacheFileLength - 12, 4) / 4);
					m_ShaderModule.m_Type = static_cast<Graphics::EShaderType>(shaderType);
					cacheFile.read(reinterpret_cast<char*>(m_ShaderModule.m_Code.data()), m_ShaderModule.m_Code.size() * 4);
					createShaderModule = true;
				}
			}

			cacheFile.close();
		}
	}

	if (!createShaderModule)
	{
		std::vector<std::uint8_t> shaderSourceContent;
		if (FileIO::readGameFile(m_ShaderFile, shaderSourceContent))
		{
			auto& glslang = GLSLang::Get();
			auto  type    = getShaderTypeFromFile(m_ShaderFile);
			auto  code    = glslang.compileShader(std::string_view { reinterpret_cast<char*>(shaderSourceContent.data()), shaderSourceContent.size() }, type);

			m_ShaderModule.m_Code = code;
			m_ShaderModule.m_Type = type;
			createShaderModule    = true;

			std::filesystem::create_directories(cacheFilePath.parent_path());
			std::ofstream cacheFile { cacheFilePath, std::ios::binary };
			if (cacheFile)
			{
				std::uint64_t lastWriteTime = FileIO::gameFileLastWriteTime(m_ShaderFile);
				std::uint32_t shaderType    = static_cast<std::uint32_t>(type);
				cacheFile.write(reinterpret_cast<char*>(&lastWriteTime), 8);
				cacheFile.write(reinterpret_cast<char*>(&shaderType), 4);
				cacheFile.write(reinterpret_cast<char*>(code.data()), code.size() * 4);
				cacheFile.close();
			}
		}
	}

	if (createShaderModule)
	{
		if (!m_ShaderModule.create())
			throw std::runtime_error("Failed to create vulkan shader module");
		// TODO(MarcasRealAccount): Implement better debug naming
		m_ShaderModule.getDevice().setDebugName(m_ShaderModule, "m_ShaderModule");
	}
}