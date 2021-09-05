//
//	Created by Brandon Burton (Izodn) on 30. Aug. 2021
//

#pragma once

#include "../Blocks/Block.h"
#include <vec2.hpp>
#include <vec3.hpp>
#include <vector>

using blocks::Block;

namespace world
{
	typedef glm::ivec2 vec2;
	typedef glm::ivec3 vec3;

	class Chunk
	{
	public:
		static const uint8_t DEFAULT_CHUNK_DIAMETER = 16;
		static const uint8_t DEFAULT_CHUNK_HEIGHT   = 255;

		Chunk(vec2 position, uint8_t diameter = DEFAULT_CHUNK_DIAMETER, uint8_t height = DEFAULT_CHUNK_HEIGHT);
		void                           SetPosition(vec2 position);
		vec2                           GetPosition() const;
		uint8_t                        GetDiameter() const;
		uint8_t                        GetHeight() const;
		void                           SetBlock(vec3 position, blocks::BlockType blockType);
		blocks::BlockType              GetBlock(vec3 position) const;
		std::vector<blocks::BlockType> GetBlocks();

	private:
		vec2                           m_Position;
		uint8_t                        m_Diameter;
		uint8_t                        m_Height;
		std::vector<blocks::BlockType> m_Blocks;
	};
}; // namespace world
