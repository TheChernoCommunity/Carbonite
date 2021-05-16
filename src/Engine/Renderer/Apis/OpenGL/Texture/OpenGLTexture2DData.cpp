//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTexture2DData.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTextureCommon.h"

#include <cstring>

namespace gp1::renderer::apis::opengl::texture
{
	OpenGLTexture2DData::OpenGLTexture2DData(renderer::texture::Texture2D* texture)
	    : OpenGLRendererData(texture) {}

	void OpenGLTexture2DData::CleanUp()
	{
		if (this->m_TextureID) glDeleteTextures(1, &this->m_TextureID);
	}

	uint32_t OpenGLTexture2DData::GetTextureID()
	{
		if (GetDataUnsafe<renderer::texture::Texture2D>()->IsDirty()) InitGLData();
		return this->m_TextureID;
	}

	void OpenGLTexture2DData::InitGLData()
	{
		if (this->m_TextureID) CleanUp();

		renderer::texture::Texture2D* texture = GetDataUnsafe<renderer::texture::Texture2D>();
		if (!texture || texture->m_Data.size() == 0 || texture->m_Width == 0 || texture->m_Height == 0) return;

		glGenTextures(1, &this->m_TextureID);
		glBindTexture(GL_TEXTURE_2D, this->m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureCommon::GetTextureWrapping(texture->m_Wrapping.s));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureCommon::GetTextureWrapping(texture->m_Wrapping.t));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureCommon::GetTextureFilter(texture->m_Filter.minimize));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureCommon::GetTextureFilter(texture->m_Filter.magnify));
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, texture->m_LodBias);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, texture->m_MinLod);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, texture->m_MaxLod);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, texture->m_BaseLevel);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, texture->m_MaxLevel);

		renderer::texture::TextureFormat format = texture->m_Format;
		switch (format)
		{
		case renderer::texture::TextureFormat::DEPTH_COMPONENT:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, texture->m_Width, texture->m_Height, 0, GL_DEPTH_COMPONENT, textureCommon::GetTextureType(texture->m_Type), texture->m_Data.data());
			break;
		case renderer::texture::TextureFormat::DEPTH_STENCIL:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_STENCIL, texture->m_Width, texture->m_Height, 0, GL_DEPTH_STENCIL, textureCommon::GetTextureType(texture->m_Type), texture->m_Data.data());
			break;
		default:
			GLenum internalFormat;
			switch (texture->m_Type)
			{
			case renderer::texture::TextureDataType::BYTE:
			case renderer::texture::TextureDataType::UNSIGNED_BYTE:
			case renderer::texture::TextureDataType::UNSIGNED_BYTE_2_3_3_REV:
			case renderer::texture::TextureDataType::UNSIGNED_BYTE_3_3_2:
				internalFormat = GL_RGBA8;
				break;
			case renderer::texture::TextureDataType::SHORT:
			case renderer::texture::TextureDataType::UNSIGNED_SHORT:
			case renderer::texture::TextureDataType::UNSIGNED_SHORT_1_5_5_5_REV:
			case renderer::texture::TextureDataType::UNSIGNED_SHORT_4_4_4_4:
			case renderer::texture::TextureDataType::UNSIGNED_SHORT_4_4_4_4_REV:
			case renderer::texture::TextureDataType::UNSIGNED_SHORT_5_5_5_1:
			case renderer::texture::TextureDataType::UNSIGNED_SHORT_5_6_5:
			case renderer::texture::TextureDataType::UNSIGNED_SHORT_5_6_5_REV:
				internalFormat = GL_RGBA16;
				break;
			case renderer::texture::TextureDataType::INT:
			case renderer::texture::TextureDataType::UNSIGNED_INT:
			case renderer::texture::TextureDataType::UNSIGNED_INT_10_10_10_2:
			case renderer::texture::TextureDataType::UNSIGNED_INT_2_10_10_10_REV:
			case renderer::texture::TextureDataType::UNSIGNED_INT_8_8_8_8:
			case renderer::texture::TextureDataType::UNSIGNED_INT_8_8_8_8_REV:
				internalFormat = GL_RGBA32UI;
				break;
			case renderer::texture::TextureDataType::HALF_FLOAT:
				internalFormat = GL_RGBA16F;
				break;
			case renderer::texture::TextureDataType::FLOAT:
				internalFormat = GL_RGBA32F;
				break;
			default:
				internalFormat = GL_RGBA;
			}
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texture->m_Width, texture->m_Height, 0, textureCommon::GetTextureFormat(format), textureCommon::GetTextureType(texture->m_Type), texture->m_Data.data());
			break;
		}

		switch (texture->m_Filter.minimize)
		{
		case renderer::texture::TextureFilter::NEAREST_MIPMAP_NEAREST:
		case renderer::texture::TextureFilter::NEAREST_MIPMAP_LINEAR:
		case renderer::texture::TextureFilter::LINEAR_MIPMAP_NEAREST:
		case renderer::texture::TextureFilter::LINEAR_MIPMAP_LINEAR:
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		default:
			break;
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		if (!texture->IsEditable() || !texture->IsDynamic())
		{
			texture->m_Data.clear();
		}
		texture->ClearDirty();
	}

} // namespace gp1::renderer::apis::opengl::texture
