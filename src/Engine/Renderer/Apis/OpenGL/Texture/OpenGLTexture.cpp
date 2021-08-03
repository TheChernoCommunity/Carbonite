//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture.h"

#include <glad/glad.h>

namespace gp1::renderer::opengl
{
	uint32_t OpenGLTexture::GetGLWrapping(ETextureWrapping wrapping) const
	{
		switch (wrapping)
		{
		case ETextureWrapping::Repeat: return GL_REPEAT;
		case ETextureWrapping::MirroredRepeat: return GL_MIRRORED_REPEAT;
		case ETextureWrapping::ClampToEdge: return GL_CLAMP_TO_EDGE;
		case ETextureWrapping::ClampToBorder: return GL_CLAMP_TO_BORDER;
		case ETextureWrapping::MirroredClampToEdge: return GL_MIRROR_CLAMP_TO_EDGE;
		default: return 0;
		}
	}

	uint32_t OpenGLTexture::GetGLFilter(ETextureFilter filter) const
	{
		switch (filter)
		{
		case ETextureFilter::Nearest: return GL_NEAREST;
		case ETextureFilter::Linear: return GL_LINEAR;
		case ETextureFilter::NearestMipmapNearest: return GL_NEAREST_MIPMAP_NEAREST;
		case ETextureFilter::NearestMipmapLinear: return GL_NEAREST_MIPMAP_LINEAR;
		case ETextureFilter::LinearMipmapNearest: return GL_LINEAR_MIPMAP_NEAREST;
		case ETextureFilter::LinearMipmapLinear: return GL_LINEAR_MIPMAP_LINEAR;
		default: return 0;
		}
	}

	uint32_t OpenGLTexture::GetGLFormat(ETextureFormat format) const
	{
		switch (format)
		{
		case ETextureFormat::Red: return GL_RED;
		case ETextureFormat::RG: return GL_RG;
		case ETextureFormat::RGB: return GL_RGB;
		case ETextureFormat::BGR: return GL_BGR;
		case ETextureFormat::RGBA: return GL_RGBA;
		case ETextureFormat::BGRA: return GL_BGRA;
		case ETextureFormat::RedInteger: return GL_RED_INTEGER;
		case ETextureFormat::RGInteger: return GL_RG_INTEGER;
		case ETextureFormat::RGBInteger: return GL_RGB_INTEGER;
		case ETextureFormat::BGRInteger: return GL_BGR_INTEGER;
		case ETextureFormat::RGBAInteger: return GL_RGBA_INTEGER;
		case ETextureFormat::BGRAInteger: return GL_BGRA_INTEGER;
		case ETextureFormat::StencilIndex: return GL_STENCIL_INDEX;
		case ETextureFormat::DepthComponent: return GL_DEPTH_COMPONENT;
		case ETextureFormat::DepthStencil: return GL_DEPTH_STENCIL;
		default: return 0;
		}
	}

	uint32_t OpenGLTexture::GetGLDataType(ETextureDataType dataType) const
	{
		switch (dataType)
		{
		case ETextureDataType::UByte: return GL_UNSIGNED_BYTE;
		case ETextureDataType::Byte: return GL_BYTE;
		case ETextureDataType::UShort: return GL_UNSIGNED_SHORT;
		case ETextureDataType::Short: return GL_SHORT;
		case ETextureDataType::UInt: return GL_UNSIGNED_INT;
		case ETextureDataType::Int: return GL_INT;
		case ETextureDataType::HalfFloat: return GL_HALF_FLOAT;
		case ETextureDataType::Float: return GL_FLOAT;
		case ETextureDataType::UByte_3_3_2: return GL_UNSIGNED_BYTE_3_3_2;
		case ETextureDataType::UByte_2_3_3_Rev: return GL_UNSIGNED_BYTE_2_3_3_REV;
		case ETextureDataType::UShort_5_6_5: return GL_UNSIGNED_SHORT_5_6_5;
		case ETextureDataType::UShort_5_6_5_Rev: return GL_UNSIGNED_SHORT_5_6_5_REV;
		case ETextureDataType::UShort_4_4_4_4: return GL_UNSIGNED_SHORT_4_4_4_4;
		case ETextureDataType::UShort_4_4_4_4_Rev: return GL_UNSIGNED_SHORT_4_4_4_4_REV;
		case ETextureDataType::UShort_5_5_5_1: return GL_UNSIGNED_SHORT_5_5_5_1;
		case ETextureDataType::UShort_1_5_5_5_Rev: return GL_UNSIGNED_SHORT_1_5_5_5_REV;
		case ETextureDataType::UInt_8_8_8_8: return GL_UNSIGNED_INT_8_8_8_8;
		case ETextureDataType::UInt_8_8_8_8_Rev: return GL_UNSIGNED_INT_8_8_8_8_REV;
		case ETextureDataType::UInt_10_10_10_2: return GL_UNSIGNED_INT_10_10_10_2;
		case ETextureDataType::UInt_2_10_10_10_Rev: return GL_UNSIGNED_INT_2_10_10_10_REV;
		default: return 0;
		}
	}
} // namespace gp1::renderer::opengl
#endif