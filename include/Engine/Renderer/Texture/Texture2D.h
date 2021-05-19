//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#pragma once

#include "Engine/Renderer/Texture/Texture.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace gp1::renderer
{
	struct Texture2DWrapping
	{
	public:
		ETextureWrapping m_S = ETextureWrapping::Repeat;
		ETextureWrapping m_T = ETextureWrapping::Repeat;
	};

	struct Texture2D : public Texture
	{
	public:
		static std::shared_ptr<Texture2D> Create();

	public:
		virtual ~Texture2D() = default;

	protected:
		Texture2D() = default;

	public:
		std::vector<uint8_t> m_Data;
		uint32_t             m_Width = 0, m_Height = 0;
		Texture2DWrapping    m_Wrapping;
	};
} // namespace gp1::renderer