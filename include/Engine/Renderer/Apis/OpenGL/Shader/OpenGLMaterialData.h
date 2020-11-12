//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Shader/Material.h"

#include <glad/glad.h>

namespace gp1 {

	class OpenGLRenderer;

	class OpenGLMaterialData : public MaterialData {
	public:
		OpenGLMaterialData(Material* material);

		virtual void CleanUp() override;

		virtual RendererType GetRendererType() const override;

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
		void SetAllUniforms();

		friend OpenGLRenderer;

	private:
		static GLenum GetGLCullFace(TriangleFace face);
		static GLenum GetGLBlendFunc(BlendFunc blendFunc);
		static GLenum GetGLPolygonMode(PolygonMode polygonMode);
	};

} // namespace gp1
