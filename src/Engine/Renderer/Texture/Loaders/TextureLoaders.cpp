//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#include "Engine/Renderer/Texture/Loaders/TextureLoaders.h"

#include "Engine/Renderer/Texture/Texture2D.h"

#include <stb/stb_image.h>
#include <unordered_map>

namespace gp1::renderer::textureLoaders
{
	std::unordered_map<std::string, texture::Texture2D*> s_Texture2Ds;

	texture::Texture2D* LoadTexture2D(std::string file, TextureLoadMode mode)
	{
		auto itr = s_Texture2Ds.find(file);
		if (itr != s_Texture2Ds.end()) return itr->second;

		texture::Texture2D* tex = new texture::Texture2D();

		int32_t width, height, nrChannels;
		switch (mode)
		{
		case TextureLoadMode::NORMAL:
		{
			uint8_t* data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				uint64_t size = static_cast<uint64_t>(width) * static_cast<uint64_t>(height) * static_cast<uint64_t>(nrChannels);
				tex->m_Data.resize(size);
				for (uint64_t i = 0; i < size; i++)
					tex->m_Data[i] = data[i];
				tex->m_Width  = static_cast<uint32_t>(width);
				tex->m_Height = static_cast<uint32_t>(height);
				switch (nrChannels)
				{
				case 1:
					tex->m_Format = texture::TextureFormat::RED;
					break;
				case 2:
					tex->m_Format = texture::TextureFormat::RG;
					break;
				case 3:
					tex->m_Format = texture::TextureFormat::RGB;
					break;
				case 4:
					tex->m_Format = texture::TextureFormat::RGBA;
					break;
				}
				s_Texture2Ds.insert({ file, tex });
				return tex;
			}
			break;
		}
		case TextureLoadMode::HDR:
		{
			float* data = stbi_loadf(file.c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				uint64_t size = static_cast<uint64_t>(width) * static_cast<uint64_t>(height) * static_cast<uint64_t>(nrChannels) * 4ULL;
				tex->m_Data.resize(size);
				uint8_t* bytes = reinterpret_cast<uint8_t*>(data);
				for (uint64_t i = 0; i < size; i++)
					tex->m_Data[i] = bytes[i];
				tex->m_Width  = static_cast<uint32_t>(width);
				tex->m_Height = static_cast<uint32_t>(height);
				tex->m_Type   = texture::TextureDataType::FLOAT;
				switch (nrChannels)
				{
				case 1:
					tex->m_Format = texture::TextureFormat::RED;
					break;
				case 2:
					tex->m_Format = texture::TextureFormat::RG;
					break;
				case 3:
					tex->m_Format = texture::TextureFormat::RGB;
					break;
				case 4:
					tex->m_Format = texture::TextureFormat::RGBA;
					break;
				}
				s_Texture2Ds.insert({ file, tex });
				return tex;
			}
			break;
		}
		case TextureLoadMode::BPC16:
		{
			uint16_t* data = stbi_load_16(file.c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				uint64_t size = static_cast<uint64_t>(width) * static_cast<uint64_t>(height) * static_cast<uint64_t>(nrChannels) * 2ULL;
				tex->m_Data.resize(size);
				uint8_t* bytes = reinterpret_cast<uint8_t*>(data);
				for (uint64_t i = 0; i < size; i++)
					tex->m_Data[i] = bytes[i];
				tex->m_Width  = static_cast<uint32_t>(width);
				tex->m_Height = static_cast<uint32_t>(height);
				tex->m_Type   = texture::TextureDataType::UNSIGNED_SHORT;
				switch (nrChannels)
				{
				case 1:
					tex->m_Format = texture::TextureFormat::RED;
					break;
				case 2:
					tex->m_Format = texture::TextureFormat::RG;
					break;
				case 3:
					tex->m_Format = texture::TextureFormat::RGB;
					break;
				case 4:
					tex->m_Format = texture::TextureFormat::RGBA;
					break;
				}
				s_Texture2Ds.insert({ file, tex });
				return tex;
			}
			break;
		}
		}
		delete tex;
		return nullptr;
	}

} // namespace gp1::renderer::textureLoaders
