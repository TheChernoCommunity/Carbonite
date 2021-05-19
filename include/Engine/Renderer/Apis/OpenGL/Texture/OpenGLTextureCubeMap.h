//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture.h"
#include "Engine/Renderer/Texture/TextureCubeMap.h"

#include <cstdint>

namespace gp1::renderer::opengl
{
	struct OpenGLTextureCubeMap : public TextureCubeMap, public OpenGLTexture
	{
	public:
		friend struct OpenGLUniformTextureCubeMap;

	public:
		virtual ~OpenGLTextureCubeMap();

		void Update();
		void CleanUp();

	private:
		uint32_t m_TextureId = 0;
	};
} // namespace gp1::renderer::opengl
#endif