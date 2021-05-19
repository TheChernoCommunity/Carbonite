//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#pragma once

#include "Engine/Renderer/Texture/Texture2D.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace gp1::renderer
{
	struct Texture2DArray : public Texture
	{
	public:
		static std::shared_ptr<Texture2DArray> Create();

	public:
		virtual ~Texture2DArray() = default;

	protected:
		Texture2DArray() = default;

	public:
		std::vector<std::vector<uint8_t>> m_Textures;

		uint32_t          m_Width = 0, m_Height = 0;
		Texture2DWrapping m_Wrapping;
	};
} // namespace gp1::renderer