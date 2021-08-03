//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#include "Engine/Utility/Core.h"

#ifdef RENDERER_OPENGL

#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture2D.h"

#include <glad/glad.h>

namespace gp1::renderer::opengl
{
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		CleanUp();
	}

	void OpenGLTexture2D::Update()
	{
		if (m_Dirty)
		{
			if (!m_TextureId)
				glGenTextures(1, &m_TextureId);

			if (m_Data.empty() || m_Width == 0 || m_Height == 0)
			{
				CleanUp();
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, m_TextureId);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetGLWrapping(m_Wrapping.m_S));
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetGLWrapping(m_Wrapping.m_T));
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetGLFilter(m_Filter.m_Minimize));
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetGLFilter(m_Filter.m_Magnify));
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, m_Lod.m_Bias);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, m_Lod.m_Min);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, m_Lod.m_Max);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, m_Lod.m_BaseLevel);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, m_Lod.m_MaxLevel);

				GLenum format = GetGLFormat(m_Format);
				GLenum type   = GetGLDataType(m_Type);
				switch (m_Format)
				{
				case ETextureFormat::DepthComponent:
					[[fallthrough]];
				case ETextureFormat::DepthStencil:
					glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, type, m_Data.data());
					break;
				default:
					GLenum internalFormat;
					switch (m_Type)
					{
					case ETextureDataType::Byte:
					case ETextureDataType::UByte:
					case ETextureDataType::UByte_2_3_3_Rev:
					case ETextureDataType::UByte_3_3_2:
						internalFormat = GL_RGBA8;
						break;
					case ETextureDataType::Short:
					case ETextureDataType::UShort:
					case ETextureDataType::UShort_1_5_5_5_Rev:
					case ETextureDataType::UShort_4_4_4_4:
					case ETextureDataType::UShort_4_4_4_4_Rev:
					case ETextureDataType::UShort_5_5_5_1:
					case ETextureDataType::UShort_5_6_5:
					case ETextureDataType::UShort_5_6_5_Rev:
						internalFormat = GL_RGBA16;
						break;
					case ETextureDataType::Int:
					case ETextureDataType::UInt:
					case ETextureDataType::UInt_10_10_10_2:
					case ETextureDataType::UInt_2_10_10_10_Rev:
					case ETextureDataType::UInt_8_8_8_8:
					case ETextureDataType::UInt_8_8_8_8_Rev:
						internalFormat = GL_RGBA32UI;
						break;
					case ETextureDataType::HalfFloat:
						internalFormat = GL_RGBA16F;
						break;
					case ETextureDataType::Float:
						internalFormat = GL_RGBA32F;
						break;
					default:
						internalFormat = GL_RGBA;
					}
					glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, type, m_Data.data());
					break;
				}

				switch (m_Filter.m_Minimize)
				{
				case ETextureFilter::NearestMipmapNearest:
				case ETextureFilter::NearestMipmapLinear:
				case ETextureFilter::LinearMipmapNearest:
				case ETextureFilter::LinearMipmapLinear:
					glGenerateMipmap(GL_TEXTURE_2D);
					break;
				default:
					break;
				}

				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if (!m_Editable || !m_Dynamic)
				m_Data.clear();

			m_Dirty = false;
		}
	}

	void OpenGLTexture2D::CleanUp()
	{
		glDeleteTextures(1, &m_TextureId);
		m_TextureId = 0;
	}
} // namespace gp1::renderer::opengl
#endif