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
	struct Texture3DWrapping
	{
	public:
		ETextureWrapping m_S = ETextureWrapping::Repeat;
		ETextureWrapping m_T = ETextureWrapping::Repeat;
		ETextureWrapping m_R = ETextureWrapping::Repeat;
	};

	struct Texture3D : public Texture
	{
	public:
		static std::shared_ptr<Texture3D> Create();

	public:
		virtual ~Texture3D() = default;

	protected:
		Texture3D() = default;

	public:
		std::vector<uint8_t> m_Data;
		uint32_t             m_Width = 0, m_Height = 0, m_Depth = 0;
		Texture3DWrapping    m_Wrapping;
	};
} // namespace gp1::renderer