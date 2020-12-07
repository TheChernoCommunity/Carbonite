//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#pragma once

#include "Engine/Renderer/RendererData.h"
#include "Engine/Renderer/Texture/TextureCommon.h"

#include <stdint.h>
#include <vector>

namespace gp1::renderer::texture
{
	struct Texture3D : public Data
	{
	public:
		Texture3D();

		// Mark this texture dirty for recreation.
		void MarkDirty();
		// Clears this texture's dirtiness.
		void ClearDirty();
		// Is this texture dirty.
		bool IsDirty();

		// Is the texture editable.
		bool IsEditable();
		// Is the texture dynamic.
		bool IsDynamic();

	public:
		std::vector<uint8_t> m_Data;                                    // This texture's raw byte data.
		uint32_t             m_Width = 0, m_Height = 0, m_Depth = 0;    // The size of the texture.
		TextureFormat        m_Format = TextureFormat::RGBA;            // The format of the texture data.
		TextureDataType      m_Type   = TextureDataType::UNSIGNED_BYTE; // The type of texture data.

		struct
		{
			TextureWrapping s = TextureWrapping::REPEAT; // The x axis wrap method.
			TextureWrapping t = TextureWrapping::REPEAT; // The y axis wrap method.
			TextureWrapping r = TextureWrapping::REPEAT; // The z axis wrap method.
		} m_Wrapping;                                    // The wrapping of this texture.

		struct
		{
			TextureFilter minimize = TextureFilter::LINEAR_MIPMAP_LINEAR; // The minimize filter to use.
			TextureFilter magnify  = TextureFilter::LINEAR;               // THe magnify filter to use.
		} m_Filter;                                                       // The filter of this texture.

		float    m_LodBias   = 0.0f;     // The level of detail bias for the texture.
		float    m_MinLod    = -1000.0f; // The min level of detail for the texture.
		float    m_MaxLod    = 1000.0f;  // The max level of detail for the texture.
		uint32_t m_BaseLevel = 0;        // The base mapmap level for the texture.
		uint32_t m_MaxLevel  = 1000;     // The max mipmap level for the texture.

	protected:
		bool m_Dirty     = true;  // Should this texture be recreated.
		bool m_Editable  = true;  // Is this texture editable.
		bool m_IsDynamic = false; // Is this texture dynamic. (i.e. should the raw byte data be kept after initialization of the GL data)
	};

} // namespace gp1::renderer::texture
