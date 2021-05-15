//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#pragma once

#include "Engine/Renderer/Apis/OpenGL/OpenGLRendererData.h"
#include "Engine/Renderer/Texture/Texture2D.h"

#include <stdint.h>

namespace gp1::renderer::apis::opengl::texture
{
	struct OpenGLTexture2DData : public OpenGLRendererData
	{
	public:
		OpenGLTexture2DData(renderer::texture::Texture2D* texture);

		virtual void CleanUp() override;

		// Get the texture id.
		uint32_t GetTextureID();

		// Initialize the opengl data.
		void InitGLData();

		friend OpenGLRenderer;

	private:
		uint32_t m_TextureID = 0; // The texture id.
	};

} // namespace gp1::renderer::apis::opengl::texture
