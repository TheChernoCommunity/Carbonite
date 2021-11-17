#include "PCH.h"

#include "World/Chunk.h"

#include <cstring>

Chunk::Chunk(std::uint32_t chunkX, std::uint32_t chunkY, std::uint32_t chunkZ)
    : m_ChunkX(chunkX), m_ChunkY(chunkY), m_ChunkZ(chunkZ)
{
	std::memset(m_Voxels, Size * Size * Size, ~0ULL);
}
