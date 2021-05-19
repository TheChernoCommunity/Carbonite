//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#pragma once

#include "Engine/Renderer/Texture/Texture2D.h"
#include "Engine/Renderer/Texture/Texture3D.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace gp1::renderer
{
	namespace TextureCubeMapFaceIndex
	{
		static constexpr const uint32_t PositiveX = 0;
		static constexpr const uint32_t NegativeX = 1;
		static constexpr const uint32_t PositiveY = 2;
		static constexpr const uint32_t NegativeY = 3;
		static constexpr const uint32_t PositiveZ = 4;
		static constexpr const uint32_t NegativeZ = 5;
	} // namespace TextureCubeMapFaceIndex

	struct TextureCubeMap : public Texture
	{
	public:
		static std::shared_ptr<TextureCubeMap> Create();

	public:
		virtual ~TextureCubeMap() = default;

	public:
		std::vector<uint8_t> m_Textures[6];

		uint32_t          m_Width = 0, m_Height = 0;
		Texture3DWrapping m_Wrapping;
	};
} // namespace gp1::renderer