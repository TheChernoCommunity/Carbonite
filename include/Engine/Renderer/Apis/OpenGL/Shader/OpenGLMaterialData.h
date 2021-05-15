//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#pragma once

#include "Engine/Renderer/Apis/OpenGL/OpenGLRendererData.h"
#include "Engine/Renderer/Shader/Material.h"

#include <glad/glad.h>

namespace gp1::renderer::apis::opengl::shader
{
	class OpenGLMaterialData : public OpenGLRendererData
	{
	public:
		OpenGLMaterialData(renderer::shader::Material* material);

		virtual void CleanUp() override;

		// Get the cull face.
		GLenum GetCullFace() const;
		// Get the src blend function.
		GLenum GetSrcBlendFunc() const;
		// Get the dst blend function.
		GLenum GetDstBlendFunc() const;
		// Get the face to use the polygon mode on.
		GLenum GetPolygonModeFace() const;
		// Get the polygon mode.
		GLenum GetPolygonMode() const;

		// Set all uniforms.
		void SetAllUniforms(OpenGLRenderer* renderer);

		friend OpenGLRenderer;

	private:
		// Get the opengl cull face value.
		static GLenum GetGLCullFace(renderer::shader::TriangleFace face);
		// Get the opengl blend function value.
		static GLenum GetGLBlendFunc(renderer::shader::BlendFunc blendFunc);
		// Get the opengl polycon mode value.
		static GLenum GetGLPolygonMode(renderer::shader::PolygonMode polygonMode);
	};

} // namespace gp1::renderer::apis::opengl::shader
