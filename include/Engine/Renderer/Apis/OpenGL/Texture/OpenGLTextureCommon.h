//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#pragma once

#include "Engine/Renderer/Texture/TextureCommon.h"

#include <glad/glad.h>

namespace gp1::renderer::apis::opengl::textureCommon
{
	// Get the opengl texture wrap value.
	GLenum GetTextureWrapping(renderer::texture::TextureWrapping wrapping);
	// Get the opengl texture filter value.
	GLenum GetTextureFilter(renderer::texture::TextureFilter filter);
	// Get the opengl texture format value.
	GLenum GetTextureFormat(renderer::texture::TextureFormat format);
	// Get the opengl texture type value.
	GLenum GetTextureType(renderer::texture::TextureDataType type);

} // namespace gp1::renderer::apis::opengl::textureCommon
