//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture.h"
#include "Engine/Renderer/Texture/Texture3D.h"

#include <cstdint>

namespace gp1::renderer::opengl
{
	struct OpenGLTexture3D : public Texture3D, public OpenGLTexture
	{
	public:
		friend struct OpenGLUniformTexture3D;

	public:
		virtual ~OpenGLTexture3D();

		void Update();
		void CleanUp();

	private:
		uint32_t m_TextureId = 0;
	};
} // namespace gp1::renderer::opengl
#endif