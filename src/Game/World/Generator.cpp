//
//	Created by Brandon Burton (Izodn) on 30. Aug. 2021
//

#include "Game/World/Generator.h"

using namespace world;

Generator::Generator(int seed)
    : m_Logger("Generator")
{
	SetSeed(seed);

	// Uncomment when ready for noisy terrain
	//m_Noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
};

ChunkHeightMap Generator::GenerateHeightMap(vec2 position, WorldType worldType, uint8_t diameter, uint8_t oceanLevel)
{
	m_Logger.LogDebug("Generator::GenerateHeightMapAt: Called with {x: %i, y: %i}, %u", position.x, position.y, m_Seed);

	switch (worldType)
	{
	default:
		//todo(Izodn): Uncomment when ready for noisy terrain
		//case WorldType::Standard:
		//	return GenerateHeightMapFromNoise(position, diameter); // Uncomment when ready for noisy terrain

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

	//todo(Izodn): Uncomment when ready for noisy terrain
	//m_Noise.SetSeed(seed);
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

//todo(Izodn): Uncomment when ready for noisy terrain
//ChunkHeightMap Generator::GenerateHeightMapFromNoise(vec2 position, uint8_t diameter)
//{
//	// Gather noise data
//	ChunkHeightMap noiseData = new float[(size_t) diameter * (size_t) diameter];
//	int            index     = 0;
//
//	for (int x = 0; x < diameter; x++)
//	{
//		for (int y = 0; y < diameter; y++)
//		{
//			noiseData[index++] = m_Noise.GetNoise((float) position.x * diameter + x, (float) position.x * diameter + y);
//		}
//	}
//
//	std::string str = "[";
//	for (int x = 0; x < diameter * diameter; x++)
//	{
//		if (x > 0)
//		{
//			str.append(",");
//		}
//		str.append(std::to_string((double) noiseData[x]));
//		str.append(" ");
//	}
//	str.append("]");
//	m_Logger.LogDebug(str.c_str());
//
//	return noiseData;
//}
