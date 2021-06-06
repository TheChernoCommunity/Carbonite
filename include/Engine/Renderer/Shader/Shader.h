//
//	Created by MarcasRealAccount on 14. May. 2021
//

#pragma once

#include <cstdint>
#include <vector>

namespace gp1::renderer
{
	enum class EShaderType
	{
		VertexShader,
		TessControlShader,
		TessEvaluationShader,
		GeometryShader,
		FragmentShader,
		ComputeShader
	};

	struct Shader
	{
	public:
		friend struct ShaderProgram;

	protected:
		Shader(EShaderType type);

	public:
		EShaderType          m_Type;
		std::vector<uint8_t> m_Data;
	};
} // namespace gp1::renderer