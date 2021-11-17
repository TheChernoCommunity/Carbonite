#pragma once

#include <stdexcept>

struct Chunk
{
public:
	static constexpr std::size_t Size = 32;

	static std::size_t PositionToIndex(std::uint32_t x, std::uint32_t y, std::uint32_t z)
	{
		return x + y * Size + z * Size * Size;
	}

public:
	Chunk(std::uint32_t chunkX, std::uint32_t chunkY, std::uint32_t chunkZ);

	std::uint64_t& operator()(std::uint32_t x, std::uint32_t y, std::uint32_t z)
	{
		// TODO(MarcasRealAccount): Add asserts
		if (x >= Size || y >= Size || z >= Size)
			throw std::runtime_error("Outside chunk bounds");
		return m_Voxels[PositionToIndex(x, y, z)];
	}

public:
	std::uint32_t m_ChunkX, m_ChunkY, m_ChunkZ;
	std::uint64_t m_Voxels[Size * Size * Size];
};
