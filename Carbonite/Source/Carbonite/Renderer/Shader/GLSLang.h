#pragma once

#include "Graphics/Pipeline/ShaderModule.h"

#include <glslang/Include/ResourceLimits.h>
#include <glslang/SPIRV/GlslangToSpv.h>

#include <cstdint>

#include <string_view>
#include <vector>

class GLSLang
{
public:
	static GLSLang& Get();
	static void     Destroy();

public:
	std::vector<std::uint32_t> compileShader(std::string_view sourceString, Graphics::EShaderType shaderType);

protected:
	GLSLang();
	~GLSLang();

private:
	bool             m_Initialized = false;
	TBuiltInResource m_Resources;
};