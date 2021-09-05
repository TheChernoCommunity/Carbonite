//
//	Created by Brandon Burton (Izodn) on 30. Aug. 2021
//

#pragma once

#include "Chunk.h"
#include "Generator.h"
#include "WorldType.h"
#include <Engine/Utility/Logger.h>

using namespace gp1;

namespace world
{
	class World
	{
	public:
		static const uint8_t DEFAULT_SEED                = 1;
		static const uint8_t DEFAULT_CHUNK_LOAD_DIAMETER = 9;
		static const uint8_t DEFAULT_OCEAN_LEVEL         = 63;

		World(
		    int       seed              = DEFAULT_SEED,
		    WorldType worldType         = WorldType::SuperFlat,
		    uint8_t   chunkLoadDiameter = DEFAULT_CHUNK_LOAD_DIAMETER,
		    uint8_t   chunkDiameter     = Chunk::DEFAULT_CHUNK_DIAMETER,
		    uint8_t   chunkHeight       = Chunk::DEFAULT_CHUNK_HEIGHT,
		    uint8_t   oceanLevel        = DEFAULT_OCEAN_LEVEL,
		    uint8_t   minGenHeight      = Generator::DEFAULT_MIN_GEN_HEIGHT,
		    uint8_t   maxGenHeight      = Generator::DEFAULT_MAX_GEN_HEIGHT);
		~World();
		void                SetSeed(int);
		void                SetChunkLoadDiameter(uint8_t);
		void                LoadChunks(uint8_t chunkDiameter, uint8_t chunkHeight, uint8_t oceanLevel, uint8_t minGenHeight, uint8_t maxGenHeight);
		blocks::BlockType   GetBlockAt(vec3 position);
		std::vector<Chunk*> GetChunks();

	private:
		Logger              m_Logger;
		int                 m_Seed              = DEFAULT_SEED;
		uint8_t             m_ChunkLoadDiameter = DEFAULT_CHUNK_LOAD_DIAMETER;
		WorldType           m_WorldType         = WorldType::SuperFlat;
		std::vector<Chunk*> m_Chunks;
		Generator           m_ChunkGenerator;
	};
}; // namespace world
