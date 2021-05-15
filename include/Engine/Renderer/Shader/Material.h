//
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#pragma once

#include "Engine/Renderer/RendererData.h"

#include <any>
#include <unordered_map>

namespace gp1::renderer::shader
{
	struct Shader;

	template <typename T>
	struct Uniform;

	enum class TriangleFace : uint32_t
	{
		BACK,
		FRONT,
		FRONT_AND_BACK
	};

	enum class BlendFunc : uint32_t
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

	enum class PolygonMode : uint32_t
	{
		POINT,
		LINE,
		FILL
	};

	struct Material : public Data
	{
	public:
		Material();

		// Set the shader this material uses.
		void SetShader(Shader* shader);
		// Get the shader this material uses.
		Shader* GetShader() const;

		// Get a pointer to a uniform.
		template <typename T>
		Uniform<T>* GetUniform(const std::string& id)
		{
			if (!this->m_Shader)
				return nullptr;

			auto itr = this->m_Uniforms.find(id);
			if (itr != this->m_Uniforms.end()) {
				return std::any_cast<Uniform<T>>(&itr->second);
			}
			return nullptr;
		}

		// Gets all the uniforms this material has.
		const std::unordered_map<std::string, std::any>& GetUniforms() const;

	public:
		struct
		{
			bool         m_Enabled = true;               // Is face culling enabled.
			TriangleFace m_Face    = TriangleFace::BACK; // The face to cull.
		} m_CullMode;                                    // This mesh's cullmode.

		bool m_DepthTest = true; // Is depth testing enabled.

		struct
		{
			bool      m_Enabled = true;                           // Is blending enabled.
			BlendFunc m_SrcFunc = BlendFunc::SRC_ALPHA;           // The blend function's source function.
			BlendFunc m_DstFunc = BlendFunc::ONE_MINUS_SRC_ALPHA; // The blend function's destination function.
		} m_BlendFunc;                                            // The mesh's blend function.

		struct
		{
			bool         m_Enabled = true;                         // Is polygon mode enabled.
			TriangleFace m_Face    = TriangleFace::FRONT_AND_BACK; // The face to render with this mode.
			PolygonMode  m_Mode    = PolygonMode::FILL;            // The polygon mode.
		} m_PolygonMode;                                           // The mesh's polygon mode.

	protected:
		std::unordered_map<std::string, std::any> m_Uniforms; // The uniforms this material has.

	private:
		Shader* m_Shader = nullptr; // The shader this material uses.
	};

} // namespace gp1::renderer::shader
