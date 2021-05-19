//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#pragma once

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Texture/Texture.h"

#include <cstdint>

namespace gp1::renderer::opengl
{
	struct OpenGLTexture
	{
	public:
		uint32_t GetGLWrapping(ETextureWrapping wrapping) const;
		uint32_t GetGLFilter(ETextureFilter filter) const;
		uint32_t GetGLFormat(ETextureFormat format) const;
		uint32_t GetGLDataType(ETextureDataType dataType) const;

	protected:
		OpenGLTexture() = default;
	};
} // namespace gp1::renderer::opengl
#endif