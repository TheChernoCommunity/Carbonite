//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTextureCommon.h"

namespace gp1::renderer::apis::opengl::textureCommon
{
	GLenum GetTextureWrapping(renderer::texture::TextureWrapping wrapping)
	{
		switch (wrapping)
		{
		case renderer::texture::TextureWrapping::REPEAT:
			return GL_REPEAT;
		case renderer::texture::TextureWrapping::MIRRORED_REPEAT:
			return GL_MIRRORED_REPEAT;
		case renderer::texture::TextureWrapping::CLAMP_TO_EDGE:
			return GL_CLAMP_TO_EDGE;
		case renderer::texture::TextureWrapping::CLAMP_TO_BORDER:
			return GL_CLAMP_TO_BORDER;
		case renderer::texture::TextureWrapping::MIRRORED_CLAMP_TO_EDGE:
			return GL_MIRROR_CLAMP_TO_EDGE;
		default:
			return GL_REPEAT;
		}
	}

	GLenum GetTextureFilter(renderer::texture::TextureFilter filter)
	{
		switch (filter)
		{
		case renderer::texture::TextureFilter::NEAREST:
			return GL_NEAREST;
		case renderer::texture::TextureFilter::LINEAR:
			return GL_LINEAR;
		case renderer::texture::TextureFilter::NEAREST_MIPMAP_NEAREST:
			return GL_NEAREST_MIPMAP_NEAREST;
		case renderer::texture::TextureFilter::NEAREST_MIPMAP_LINEAR:
			return GL_NEAREST_MIPMAP_LINEAR;
		case renderer::texture::TextureFilter::LINEAR_MIPMAP_NEAREST:
			return GL_LINEAR_MIPMAP_NEAREST;
		case renderer::texture::TextureFilter::LINEAR_MIPMAP_LINEAR:
			return GL_LINEAR_MIPMAP_LINEAR;
		default:
			return GL_NEAREST;
		}
	}

	GLenum GetTextureFormat(renderer::texture::TextureFormat format)
	{
		switch (format)
		{
		case renderer::texture::TextureFormat::RED:
			return GL_RED;
		case renderer::texture::TextureFormat::RG:
			return GL_RG;
		case renderer::texture::TextureFormat::RGB:
			return GL_RGB;
		case renderer::texture::TextureFormat::BGR:
			return GL_BGR;
		case renderer::texture::TextureFormat::RGBA:
			return GL_RGBA;
		case renderer::texture::TextureFormat::BGRA:
			return GL_BGRA;
		case renderer::texture::TextureFormat::RED_INTEGER:
			return GL_RED_INTEGER;
		case renderer::texture::TextureFormat::RG_INTEGER:
			return GL_RG_INTEGER;
		case renderer::texture::TextureFormat::RGB_INTEGER:
			return GL_RGB_INTEGER;
		case renderer::texture::TextureFormat::BGR_INTEGER:
			return GL_BGR_INTEGER;
		case renderer::texture::TextureFormat::RGBA_INTEGER:
			return GL_RGBA_INTEGER;
		case renderer::texture::TextureFormat::BGRA_INTEGER:
			return GL_BGRA_INTEGER;
		case renderer::texture::TextureFormat::STENCIL_INDEX:
			return GL_STENCIL_INDEX;
		case renderer::texture::TextureFormat::DEPTH_COMPONENT:
			return GL_DEPTH_COMPONENT;
		case renderer::texture::TextureFormat::DEPTH_STENCIL:
			return GL_DEPTH_STENCIL;
		default:
			return GL_RGBA;
		}
	}

	GLenum GetTextureType(renderer::texture::TextureDataType type)
	{
		switch (type)
		{
		case renderer::texture::TextureDataType::UNSIGNED_BYTE:
			return GL_UNSIGNED_BYTE;
		case renderer::texture::TextureDataType::BYTE:
			return GL_BYTE;
		case renderer::texture::TextureDataType::UNSIGNED_SHORT:
			return GL_UNSIGNED_SHORT;
		case renderer::texture::TextureDataType::SHORT:
			return GL_SHORT;
		case renderer::texture::TextureDataType::UNSIGNED_INT:
			return GL_UNSIGNED_INT;
		case renderer::texture::TextureDataType::INT:
			return GL_INT;
		case renderer::texture::TextureDataType::HALF_FLOAT:
			return GL_HALF_FLOAT;
		case renderer::texture::TextureDataType::FLOAT:
			return GL_FLOAT;
		case renderer::texture::TextureDataType::UNSIGNED_BYTE_3_3_2:
			return GL_UNSIGNED_BYTE_3_3_2;
		case renderer::texture::TextureDataType::UNSIGNED_BYTE_2_3_3_REV:
			return GL_UNSIGNED_BYTE_2_3_3_REV;
		case renderer::texture::TextureDataType::UNSIGNED_SHORT_5_6_5:
			return GL_UNSIGNED_SHORT_5_6_5;
		case renderer::texture::TextureDataType::UNSIGNED_SHORT_5_6_5_REV:
			return GL_UNSIGNED_SHORT_5_6_5_REV;
		case renderer::texture::TextureDataType::UNSIGNED_SHORT_4_4_4_4:
			return GL_UNSIGNED_SHORT_4_4_4_4;
		case renderer::texture::TextureDataType::UNSIGNED_SHORT_4_4_4_4_REV:
			return GL_UNSIGNED_SHORT_4_4_4_4_REV;
		case renderer::texture::TextureDataType::UNSIGNED_SHORT_5_5_5_1:
			return GL_UNSIGNED_SHORT_5_5_5_1;
		case renderer::texture::TextureDataType::UNSIGNED_SHORT_1_5_5_5_REV:
			return GL_UNSIGNED_SHORT_1_5_5_5_REV;
		case renderer::texture::TextureDataType::UNSIGNED_INT_8_8_8_8:
			return GL_UNSIGNED_INT_8_8_8_8;
		case renderer::texture::TextureDataType::UNSIGNED_INT_8_8_8_8_REV:
			return GL_UNSIGNED_INT_8_8_8_8_REV;
		case renderer::texture::TextureDataType::UNSIGNED_INT_10_10_10_2:
			return GL_UNSIGNED_INT_10_10_10_2;
		case renderer::texture::TextureDataType::UNSIGNED_INT_2_10_10_10_REV:
			return GL_UNSIGNED_INT_2_10_10_10_REV;
		default:
			return GL_UNSIGNED_BYTE;
		}
	}

} // namespace gp1::renderer::apis::opengl::textureCommon
