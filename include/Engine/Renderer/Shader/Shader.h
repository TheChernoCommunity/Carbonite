#pragma once

#include <cstdint>
#include <vector>

namespace gp1::renderer
{
	enum class EShaderType
	{
		VERTEX_SHADER,
		TESS_CONTROL_SHADER,
		TESS_EVALUATION_SHADER,
		GEOMETRY_SHADER,
		FRAGMENT_SHADER,
		COMPUTE_SHADER
	};

	struct Shader
	{
	public:
		Shader(EShaderType type);

	public:
		EShaderType          m_Type;
		std::vector<uint8_t> m_Data;
	};
} // namespace gp1::renderer