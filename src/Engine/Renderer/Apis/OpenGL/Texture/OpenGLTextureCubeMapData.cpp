//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTextureCubeMapData.h"
#include "Engine/Renderer/Apis/OpenGL/Texture/OpenGLTextureCommon.h"

namespace gp1::renderer::apis::opengl::texture
{
	OpenGLTextureCubeMapData::OpenGLTextureCubeMapData(renderer::texture::TextureCubeMap* texture)
	    : OpenGLRendererData(texture) {}

	void OpenGLTextureCubeMapData::CleanUp()
	{
		if (this->m_TextureID) glDeleteTextures(1, &this->m_TextureID);
	}

	uint32_t OpenGLTextureCubeMapData::GetTextureID()
	{
		if (GetDataUnsafe<renderer::texture::TextureCubeMap>()->IsDirty()) InitGLData();
		return this->m_TextureID;
	}

	void OpenGLTextureCubeMapData::InitGLData()
	{
		if (this->m_TextureID) CleanUp();

		renderer::texture::TextureCubeMap* texture = GetDataUnsafe<renderer::texture::TextureCubeMap>();
		if (!texture || texture->m_Width == 0 || texture->m_Height == 0) return;

		for (renderer::texture::Texture2D& tex : texture->m_Textures)
			if (tex.m_Data.size() == 0) return;

		glGenTextures(1, &this->m_TextureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_TextureID);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, textureCommon::GetTextureWrapping(texture->m_Wrapping.s));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, textureCommon::GetTextureWrapping(texture->m_Wrapping.t));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, textureCommon::GetTextureWrapping(texture->m_Wrapping.r));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, textureCommon::GetTextureFilter(texture->m_Filter.minimize));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, textureCommon::GetTextureFilter(texture->m_Filter.magnify));
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_LOD_BIAS, texture->m_LodBias);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_LOD, texture->m_MinLod);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LOD, texture->m_MaxLod);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, texture->m_BaseLevel);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, texture->m_MaxLevel);

		uint8_t dataSize;
		uint8_t components;
		switch (texture->m_Type)
		{
		case renderer::texture::TextureDataType::BYTE:
		case renderer::texture::TextureDataType::UNSIGNED_BYTE:
		case renderer::texture::TextureDataType::UNSIGNED_BYTE_2_3_3_REV:
		case renderer::texture::TextureDataType::UNSIGNED_BYTE_3_3_2:
			dataSize = 1;
			break;
		case renderer::texture::TextureDataType::SHORT:
		case renderer::texture::TextureDataType::UNSIGNED_SHORT:
		case renderer::texture::TextureDataType::UNSIGNED_SHORT_1_5_5_5_REV:
		case renderer::texture::TextureDataType::UNSIGNED_SHORT_4_4_4_4:
		case renderer::texture::TextureDataType::UNSIGNED_SHORT_4_4_4_4_REV:
		case renderer::texture::TextureDataType::UNSIGNED_SHORT_5_5_5_1:
		case renderer::texture::TextureDataType::UNSIGNED_SHORT_5_6_5:
		case renderer::texture::TextureDataType::UNSIGNED_SHORT_5_6_5_REV:
			dataSize = 2;
			break;
		case renderer::texture::TextureDataType::INT:
		case renderer::texture::TextureDataType::UNSIGNED_INT:
		case renderer::texture::TextureDataType::UNSIGNED_INT_10_10_10_2:
		case renderer::texture::TextureDataType::UNSIGNED_INT_2_10_10_10_REV:
		case renderer::texture::TextureDataType::UNSIGNED_INT_8_8_8_8:
		case renderer::texture::TextureDataType::UNSIGNED_INT_8_8_8_8_REV:
			dataSize = 4;
			break;
		case renderer::texture::TextureDataType::HALF_FLOAT:
			dataSize = 2;
			break;
		case renderer::texture::TextureDataType::FLOAT:
			dataSize = 4;
			break;
		default:
			dataSize = 1;
		}
		switch (texture->m_Format)
		{
		case renderer::texture::TextureFormat::RED:
		case renderer::texture::TextureFormat::RED_INTEGER:
			components = 1;
			break;
		case renderer::texture::TextureFormat::RG:
		case renderer::texture::TextureFormat::RG_INTEGER:
			components = 2;
			break;
		case renderer::texture::TextureFormat::RGB:
		case renderer::texture::TextureFormat::RGB_INTEGER:
		case renderer::texture::TextureFormat::BGR:
		case renderer::texture::TextureFormat::BGR_INTEGER:
			components = 3;
			break;
		case renderer::texture::TextureFormat::RGBA:
		case renderer::texture::TextureFormat::RGBA_INTEGER:
		case renderer::texture::TextureFormat::BGRA:
		case renderer::texture::TextureFormat::BGRA_INTEGER:
			components = 4;
			break;
		case renderer::texture::TextureFormat::STENCIL_INDEX:
		case renderer::texture::TextureFormat::DEPTH_COMPONENT:
			components = 1;
			break;
		case renderer::texture::TextureFormat::DEPTH_STENCIL:
			components = 2;
			break;
		default:
			components = 4;
		}

		uint64_t skip     = static_cast<uint64_t>(texture->m_Width) * static_cast<uint64_t>(texture->m_Height) * static_cast<uint64_t>(components) * static_cast<uint64_t>(dataSize);
		uint64_t numBytes = skip * 6;
		uint8_t* data     = new uint8_t[numBytes];

		uint64_t i = 0;
		for (renderer::texture::Texture2D& tex : texture->m_Textures)
		{
			memcpy(data + skip * i, tex.m_Data.data(), skip);
			i++;
		}

		renderer::texture::TextureFormat format = texture->m_Format;
		switch (format)
		{
		case renderer::texture::TextureFormat::DEPTH_COMPONENT:
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_DEPTH_COMPONENT, texture->m_Width, texture->m_Height, 0, GL_DEPTH_COMPONENT, textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::POSITIVE_X].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_DEPTH_COMPONENT, texture->m_Width, texture->m_Height, 0, GL_DEPTH_COMPONENT, textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::POSITIVE_Y].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_DEPTH_COMPONENT, texture->m_Width, texture->m_Height, 0, GL_DEPTH_COMPONENT, textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::POSITIVE_Z].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_DEPTH_COMPONENT, texture->m_Width, texture->m_Height, 0, GL_DEPTH_COMPONENT, textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::NEGATIVE_X].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_DEPTH_COMPONENT, texture->m_Width, texture->m_Height, 0, GL_DEPTH_COMPONENT, textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::NEGATIVE_Y].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_DEPTH_COMPONENT, texture->m_Width, texture->m_Height, 0, GL_DEPTH_COMPONENT, textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::NEGATIVE_Z].m_Data.data());
			break;
		case renderer::texture::TextureFormat::DEPTH_STENCIL:
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_DEPTH_STENCIL, texture->m_Width, texture->m_Height, 0, GL_DEPTH_STENCIL, textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::POSITIVE_X].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_DEPTH_STENCIL, texture->m_Width, texture->m_Height, 0, GL_DEPTH_STENCIL, textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::POSITIVE_Y].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_DEPTH_STENCIL, texture->m_Width, texture->m_Height, 0, GL_DEPTH_STENCIL, textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::POSITIVE_Z].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_DEPTH_STENCIL, texture->m_Width, texture->m_Height, 0, GL_DEPTH_STENCIL, textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::NEGATIVE_X].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_DEPTH_STENCIL, texture->m_Width, texture->m_Height, 0, GL_DEPTH_STENCIL, textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::NEGATIVE_Y].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_DEPTH_STENCIL, texture->m_Width, texture->m_Height, 0, GL_DEPTH_STENCIL, textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::NEGATIVE_Z].m_Data.data());
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
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, internalFormat, texture->m_Width, texture->m_Height, 0, textureCommon::GetTextureFormat(format), textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::POSITIVE_X].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, internalFormat, texture->m_Width, texture->m_Height, 0, textureCommon::GetTextureFormat(format), textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::POSITIVE_Y].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, internalFormat, texture->m_Width, texture->m_Height, 0, textureCommon::GetTextureFormat(format), textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::POSITIVE_Z].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, internalFormat, texture->m_Width, texture->m_Height, 0, textureCommon::GetTextureFormat(format), textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::NEGATIVE_X].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, internalFormat, texture->m_Width, texture->m_Height, 0, textureCommon::GetTextureFormat(format), textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::NEGATIVE_Y].m_Data.data());
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, internalFormat, texture->m_Width, texture->m_Height, 0, textureCommon::GetTextureFormat(format), textureCommon::GetTextureType(texture->m_Type), texture->m_Textures[renderer::texture::TextureCubeMapFaceIndex::NEGATIVE_Z].m_Data.data());
			break;
		}

		switch (texture->m_Filter.minimize)
		{
		case renderer::texture::TextureFilter::NEAREST_MIPMAP_NEAREST:
		case renderer::texture::TextureFilter::NEAREST_MIPMAP_LINEAR:
		case renderer::texture::TextureFilter::LINEAR_MIPMAP_NEAREST:
		case renderer::texture::TextureFilter::LINEAR_MIPMAP_LINEAR:
			glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
			break;
		}

		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

		if (!texture->IsEditable() || !texture->IsDynamic())
		{
			texture->m_Textures[0].m_Data.clear();
			texture->m_Textures[1].m_Data.clear();
			texture->m_Textures[2].m_Data.clear();
			texture->m_Textures[3].m_Data.clear();
			texture->m_Textures[4].m_Data.clear();
			texture->m_Textures[5].m_Data.clear();
		}
		texture->ClearDirty();
		delete[] data;
	}

} // namespace gp1::renderer::apis::opengl::texture
