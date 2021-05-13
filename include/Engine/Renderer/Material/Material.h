#pragma once

#include "Engine/Renderer/Material/Uniform.h"

#include <cstdint>
#include <string>
#include <vector>

namespace gp1::renderer
{
	enum class ETriangleFace : uint32_t
	{
		FRONT,
		BACK,
		FRONT_AND_BACK
	};

	enum class EBlendFunc : uint32_t
	{
		ZERO,
		ONE,
		SRC_COLOR,
		ONE_MINUS_SRC_COLOR,
		DST_COLOR,
		ONE_MINUS_DST_COLOR,
		SRC_ALPHA,
		ONE_MINUS_SRC_ALPHA,
		DST_ALPHA,
		ONE_MINUS_DST_ALPHA,
		CONSTANT_COLOR,
		ONE_MINUS_CONSTANT_COLOR,
		CONSTANT_ALPHA,
		ONE_MINUS_CONSTANT_ALPHA,
		SRC_ALPHA_SATURATE,
		SRC1_COLOR,
		ONE_MINUS_SRC1_COLOR,
		SRC1_ALPHA,
		ONE_MINUS_SRC1_ALPHA
	};

	enum class EPolygonMode : uint32_t
	{
		POINT,
		LINE,
		FILL
	};

	struct CullMode
	{
	public:
		bool          m_Enabled = true;
		ETriangleFace m_Face    = ETriangleFace::BACK;
	};

	struct BlendFunc
	{
	public:
		bool       m_Enabled = true;
		EBlendFunc m_SrcFunc = EBlendFunc::SRC_ALPHA;
		EBlendFunc m_DstFunc = EBlendFunc::ONE_MINUS_SRC_ALPHA;
	};

	struct PolygonMode
	{
	public:
		bool          m_Enabled = true;
		ETriangleFace m_Face    = ETriangleFace::FRONT_AND_BACK;
		EPolygonMode  m_Mode    = EPolygonMode::FILL;
	};

	struct ShaderProgram;

	struct Material
	{
	public:
		virtual ~Material() = default;

		void SetShaderProgram(ShaderProgram* shaderProgram);
		void UpdateShaderProgram();

		inline ShaderProgram* GetShaderProgram() const
		{
			return m_ShaderProgram;
		}

		UniformBuffer*           GetUniformBuffer(const std::string& name);
		const UniformBuffer*     GetUniformBuffer(const std::string& name) const;
		std::shared_ptr<Uniform> GetUniform(const std::string& bufferName, const std::string& uniformName) const;

	public:
		CullMode    m_CullMode;
		bool        m_DepthTest = false;
		BlendFunc   m_BlendFunc;
		PolygonMode m_PolygonMode;

	protected:
		std::vector<UniformBuffer> m_UniformBuffers;

	private:
		ShaderProgram* m_ShaderProgram = nullptr;
	};
} // namespace gp1::renderer