//
//	Created by Brandon Burton (Izodn) on 30. Aug. 2021
//

#include "Game/World/World.h"

#include <cmath>
#include <ctime>

using namespace world;

World::World(int seed, WorldType worldType, uint8_t chunkLoadDiameter, uint8_t chunkDiameter, uint8_t chunkHeight, uint8_t oceanLevel)
    : m_Logger("World"), m_WorldType(worldType)
{
	m_Logger.LogDebug("World::World: Instantiating world");
	SetSeed(seed);
	SetChunkLoadDiameter(chunkLoadDiameter);
	LoadChunks(chunkDiameter, chunkHeight, oceanLevel);
}

World::~World()
{
	m_Logger.LogDebug("World::~World: Deleting world");
	for (Chunk* chunk : m_Chunks)
	{
		vec2 position = chunk->GetPosition();
		m_Logger.LogDebug("World::~World: Deleting chunk at {x: %i, y: %i}", position.x, position.y);
		delete chunk;
	}
	m_Chunks.clear();
}

void World::SetSeed(int seed)
{
	//m_Logger.LogDebug("World::SetSeed: Updating old seed %i to %i", m_Seed, seed);
	m_Seed = seed;
	m_ChunkGenerator.SetSeed(seed);
}

void World::SetChunkLoadDiameter(uint8_t chunkLoadDiameter)
{
	//m_Logger.LogDebug("World::SetChunkLoadDiameter: Updating old seed %i to %i", m_ChunkLoadDiameter, chunkLoadDiameter);
	m_ChunkLoadDiameter = chunkLoadDiameter;
}

void World::LoadChunks(uint8_t chunkDiameter, uint8_t chunkHeight, uint8_t oceanLevel)
{
	//m_Logger.LogDebug("World::LoadChunks: Loading loading chunks using seed %i and chunk radius %i", m_Seed, m_ChunkLoadDiameter);
	m_ChunkGenerator = Generator(m_Seed);

	// Create chunks in a diameter around world center.
	for (auto x = -(m_ChunkLoadDiameter / 2); x <= m_ChunkLoadDiameter / 2; x++)
	{
		for (auto y = -(m_ChunkLoadDiameter / 2); y <= m_ChunkLoadDiameter / 2; y++)
		{
			//m_Logger.LogDebug("World::LoadChunks: Generating chunk at (%i, %i) with seed %i", x, y, m_Seed);
			m_Chunks.push_back(m_ChunkGenerator.GenerateChunkAt(vec2(x, y), m_WorldType, chunkDiameter, chunkHeight, oceanLevel));
		}
	}
}

/**
* Note the following:
* References to XYZ below depend on context.
* Since chunk positions are relative to the world center chunk as a top-down view,
* Chunk->GetPosition().x is the same axis as Block->GetPosition().x but
* Chunk->GetPosition().y is the same axis as Block->GetPosition().z.
*/
blocks::BlockType World::GetBlockAt(vec3 position)
{
	Chunk* target   = nullptr;
	vec2   chunkPos = vec2(0, 0);
	for (Chunk* chunk : m_Chunks)
	{
		chunkPos = chunk->GetPosition();

		// Getting diameter repeatedly is inefficient as they're likely all the same.
		bool betweenX = position.x >= chunkPos.x * chunk->GetDiameter() && position.x < chunkPos.x * chunk->GetDiameter() + chunk->GetDiameter();
		bool betweenZ = position.z >= chunkPos.y * chunk->GetDiameter() && position.z < chunkPos.y * chunk->GetDiameter() + chunk->GetDiameter();
		if (betweenX && betweenZ)
		{
			target = chunk;
			break;
		}
	}

	if (target == nullptr)
	{
		return blocks::BlockType::Void;
	}
	//m_Logger.LogDebug("Chunk position: %i, %i", chunkPos.x, chunkPos.y);

	int ox = abs(position.x) % target->GetDiameter();
	int oy = position.y;
	int oz = abs(position.z) % target->GetDiameter();

	//m_Logger.LogDebug("Block position: %i, %i, %i", ox, oy, oz);

	return target->GetBlock(vec3(ox, oy, oz));
}

std::vector<Chunk*> World::GetChunks()
{
	return m_Chunks;
}
