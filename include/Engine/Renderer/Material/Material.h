//
//	Created by MarcasRealAccount on 14. May. 2021
//

#pragma once

#include "Engine/Renderer/Material/Uniform.h"

#include <cstdint>
#include <string>
#include <vector>

namespace gp1::renderer
{
	enum class ETriangleFace : uint32_t
	{
		Front,
		Back,
		FrontAndBack
	};

	enum class EBlendFunc : uint32_t
	{
		Zero,
		One,
		SrcColor,
		OneMinusSrcColor,
		DstColor,
		OneMinusDstColor,
		SrcAlpha,
		OneMinusSrcAlpha,
		DstAlpha,
		OneMinusDstAlpha,
		ConstantColor,
		OneMinusConstantColor,
		ConstantAlpha,
		OneMinusConstantAlpha,
		SrcAlphaSaturate,
		Src1Color,
		OneMinusSrc1Color,
		Src1Alpha,
		OneMinusSrc1Alpha
	};

	enum class EPolygonMode : uint32_t
	{
		Point,
		Line,
		Fill
	};

	struct CullMode
	{
	public:
		bool          m_Enabled = true;
		ETriangleFace m_Face    = ETriangleFace::Back;
	};

	struct BlendFunc
	{
	public:
		bool       m_Enabled = true;
		EBlendFunc m_SrcFunc = EBlendFunc::SrcAlpha;
		EBlendFunc m_DstFunc = EBlendFunc::OneMinusSrcAlpha;
	};

	struct PolygonMode
	{
	public:
		bool          m_Enabled = true;
		ETriangleFace m_Face    = ETriangleFace::FrontAndBack;
		EPolygonMode  m_Mode    = EPolygonMode::Fill;
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