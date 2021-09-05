//
//	Created by Brandon Burton (Izodn) on 30. Aug. 2021
//

#include "Game/World/Generator.h"

using namespace world;

Generator::Generator(int seed, uint8_t minGenHeight, uint8_t maxGenHeight)
    : m_Logger("Generator"), m_MinGenHeight(minGenHeight), m_MaxGenHeight(maxGenHeight)
{
	SetSeed(seed);

	m_Noise.SetNoiseType(FastNoiseLite::NoiseType::Perlin); // Better for Rolling hills

	//m_Noise.SetNoiseType(FastNoiseLite::NoiseType::OpenSimplex2S); // Better for mountains
	//m_Noise.SetNoiseType(FastNoiseLite::NoiseType::ValueCubic); // Actually pretty good for plains and ocean floor
};

ChunkHeightMap Generator::GenerateHeightMap(vec2 position, WorldType worldType, uint8_t diameter, uint8_t oceanLevel)
{
	m_Logger.LogDebug("Generator::GenerateHeightMapAt: Called with {x: %i, y: %i}, %u", position.x, position.y, m_Seed);

	switch (worldType)
	{
	default:
	case WorldType::Standard:
		return GenerateHeightMapFromNoise(position, diameter);

	case WorldType::SuperFlat:
		return GenerateFlatHeightMap(diameter, oceanLevel);
		break;
	}
}

void Generator::FillUnderHeightMap(Chunk* chunk, ChunkHeightMap heightMap)
{
	m_Logger.LogDebug("Generator::FillUnderHeightMap: Filling in blocks under heightmap");
	uint8_t diameter = chunk->GetDiameter();
	uint8_t height   = chunk->GetHeight();
	vec2    pos      = chunk->GetPosition();
	for (size_t x = 0; x < diameter; x++)
	{
		for (size_t y = 0; y < height; y++)
		{
			for (size_t z = 0; z < diameter; z++)
			{
				if (y <= heightMap[x * diameter + z])
				{
					chunk->SetBlock(vec3(x, y, z), blocks::BlockType::MoonRock);
				}
				else
				{
					chunk->SetBlock(vec3(x, y, z), blocks::BlockType::Air);
				}
			}
		}
	}
}

Chunk* Generator::GenerateChunkAt(vec2 position, WorldType worldType, uint8_t chunkDiameter, uint8_t chunkHeight, uint8_t oceanLevel)
{
	m_Logger.LogDebug("Generator::GenerateChunkAt: Generating chunk at {x: %i, y: %i} with seed %u", position.x, position.y, m_Seed);

	Chunk*         chunk     = new Chunk(position, chunkDiameter, chunkHeight);
	ChunkHeightMap heightMap = GenerateHeightMap(chunk->GetPosition(), worldType, chunkDiameter, oceanLevel);

	FillUnderHeightMap(chunk, heightMap);
	delete heightMap;
	return chunk;
}

void Generator::SetSeed(int seed)
{
	m_Seed = seed;
	m_Noise.SetSeed(seed);
}

int Generator::GetSeed() const
{
	return m_Seed;
}

ChunkHeightMap Generator::GenerateFlatHeightMap(uint8_t diameter, uint8_t oceanLevel)
{
	m_Logger.LogDebug("Generator::GenerateFlatHeightMap: Generating flat height map");
	size_t         heightMapSize = (size_t) diameter * (size_t) diameter;
	ChunkHeightMap heightMap     = new uint8_t[heightMapSize];
	for (size_t i = 0; i < heightMapSize; i++)
	{
		heightMap[i] = oceanLevel;
	}
	return heightMap;
}

ChunkHeightMap Generator::GenerateHeightMapFromNoise(vec2 position, uint8_t diameter)
{
	m_Logger.LogDebug("Generator::GenerateFlatHeightMap: Generating flat height map");
	size_t         heightMapSize = static_cast<size_t>(diameter) * static_cast<size_t>(diameter);
	ChunkHeightMap noiseData     = new uint8_t[heightMapSize];
	size_t         index         = 0;

	for (int x = 0; x < diameter; x++)
	{
		for (int y = 0; y < diameter; y++)
		{
			// (C6386) Compiler isn't smart enough to see that index won't get greater than diameter * diameter.
			if (index >= heightMapSize)
			{
				m_Logger.LogError("Hit a situation where index was larger than the heightMapSize. Should never happen.");
				break;
			}
			float   noise       = m_Noise.GetNoise((float) position.x * diameter + x, (float) position.y * diameter + y);
			uint8_t scaledNoise = static_cast<uint8_t>((m_MaxGenHeight - m_MinGenHeight) / 2 * (noise + 1) + m_MinGenHeight);

			// This likes to throw VS2019 C6386 warning. See reference to C6386 above
			noiseData[index] = scaledNoise;

			index++;
		}
	}

	return noiseData;
}
