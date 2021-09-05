//
//	Created by Brandon Burton (Izodn) on 30. Aug. 2021
//

#include "Game/World/Chunk.h"

using namespace world;

#define BLOCK_IDX_FORMULA (size_t) m_Height*(size_t) m_Diameter*(size_t) position.x + (size_t) m_Diameter*(size_t) position.y + position.z

Chunk::Chunk(vec2 position, uint8_t diameter, uint8_t height)
    : m_Position(position), m_Diameter(diameter), m_Height(height)
{
	//m_Logger.LogDebug("Chunk::Chunk: Initializing chunk");
	m_Blocks.resize((size_t) diameter * (size_t) diameter * (size_t) height);
}

void Chunk::SetPosition(vec2 position)
{
	m_Position = position;
}

vec2 Chunk::GetPosition() const
{
	return m_Position;
}

uint8_t Chunk::GetDiameter() const
{
	return m_Diameter;
}

uint8_t Chunk::GetHeight() const
{
	return m_Height;
}

void Chunk::SetBlock(vec3 position, blocks::BlockType block)
{
	/*
	* Example: diameter= 2 height = 3
	* Formula (BLOCK_IDX_FORMULA) = height * diameter * X + diameter * Y + Z
	*
	* 0,0,0 = 0 ( 0) [_,0,0,0,0,0,0,0,0,0,0,0] = 3*2*0 + 2*0 + 0 = 0
	* 0,0,1 = 0 ( 1) [0,_,0,0,0,0,0,0,0,0,0,0] = 3*2*0 + 2*0 + 1 = 1
	* 0,1,0 = 0 ( 2) [0,0,_,0,0,0,0,0,0,0,0,0] = 3*2*0 + 2*1 + 0 = 2
	* 0,1,1 = 0 ( 3) [0,0,0,_,0,0,0,0,0,0,0,0] = 3*2*0 + 2*1 + 1 = 3
	* 0,2,0 = 0 ( 4) [0,0,0,0,_,0,0,0,0,0,0,0] = 3*2*0 + 2*2 + 0 = 4
	* 0,2,1 = 0 ( 5) [0,0,0,0,0,_,0,0,0,0,0,0] = 3*2*0 + 2*2 + 1 = 5
	* 1,0,0 = 0 ( 6) [0,0,0,0,0,0,_,0,0,0,0,0] = 3*2*1 + 2*0 + 0 = 6
	* 1,0,1 = 0 ( 7) [0,0,0,0,0,0,0,_,0,0,0,0] = 3*2*1 + 2*0 + 1 = 7
	* 1,1,0 = 0 ( 8) [0,0,0,0,0,0,0,0,_,0,0,0] = 3*2*1 + 2*1 + 0 = 8
	* 1,1,1 = 0 ( 9) [0,0,0,0,0,0,0,0,0,_,0,0] = 3*2*1 + 2*1 + 1 = 9
	* 1,2,0 = 0 (10) [0,0,0,0,0,0,0,0,0,0,_,0] = 3*2*1 + 2*2 + 0 = 10
	* 1,2,1 = 0 (11) [0,0,0,0,0,0,0,0,0,0,0,_] = 3*2*1 + 2*2 + 1 = 11
	*/
	m_Blocks[BLOCK_IDX_FORMULA] = block;
}

blocks::BlockType Chunk::GetBlock(vec3 position) const
{
	return m_Blocks[BLOCK_IDX_FORMULA];
}

std::vector<blocks::BlockType> Chunk::GetBlocks()
{
	return m_Blocks;
}
