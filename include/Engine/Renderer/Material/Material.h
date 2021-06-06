//
//	Created by MarcasRealAccount on 14. May. 2021
//

#pragma once

#include "Engine/Renderer/Material/UniformBuffer.h"
#include "Engine/Renderer/RendererData.h"
#include "Engine/Renderer/Shader/ShaderProgram.h"

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
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

	struct Material : public RendererData
	{
	public:
		friend ShaderProgram;

		struct UniformBufferEntry
		{
		public:
			std::string                    m_Name;
			std::unique_ptr<UniformBuffer> m_UniformBuffer;
		};

	public:
		static std::unique_ptr<Material> Create();

	public:
		virtual ~Material();

		void SetShaderProgram(ShaderProgram* shaderProgram);

		ShaderProgram* GetShaderProgram() const
		{
			return m_ShaderProgram;
		}

		UniformBuffer* GetUniformBuffer(std::string_view name) const;
		Uniform*       GetUniform(std::string_view bufferName, std::string_view uniformName) const;

		template <typename T, std::enable_if_t<std::is_base_of_v<Uniform, T>, bool> = true>
		T* GetUniform(std::string_view bufferName, const std::string_view uniformName) const
		{
			return reinterpret_cast<T*>(GetUniform(bufferName, uniformName));
		}

	protected:
		Material() = default;

		void UpdateUniformBuffers(std::vector<std::pair<std::string, std::vector<std::pair<std::string, EUniformType>>>> uniformBuffers);

	public:
		bool        m_DepthTest = false;
		CullMode    m_CullMode;
		BlendFunc   m_BlendFunc;
		PolygonMode m_PolygonMode;

	protected:
		std::vector<UniformBufferEntry> m_UniformBuffers;

	private:
		ShaderProgram* m_ShaderProgram;
	};
} // namespace gp1::renderer