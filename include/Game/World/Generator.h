//
//	Created by Brandon Burton (Izodn) on 30. Aug. 2021
//

#pragma once

#include "../Blocks/Block.h"
#include "Chunk.h"
#include "WorldType.h"
#include <Engine/Utility/Logger.h>
#include <FastNoiseLite.h>

/// FastNoiseLite
/// https://github.com/Auburn/FastNoiseLite
/// MIT License
///
/// Copyright(c) 2020 Jordan Peck (jordan.me2@gmail.com)
/// Copyright(c) 2020 Contributors
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.

using namespace gp1;

namespace world
{
	typedef uint8_t* ChunkHeightMap;

	class Generator
	{
	public:
		static const std::uint8_t DEFAULT_MIN_GEN_HEIGHT = 23;
		static const std::uint8_t DEFAULT_MAX_GEN_HEIGHT = 127;
		Generator(int seed = 0, uint8_t minGenHeight = DEFAULT_MIN_GEN_HEIGHT, uint8_t maxGenHeight = DEFAULT_MAX_GEN_HEIGHT);
		ChunkHeightMap GenerateHeightMap(vec2 position, WorldType worldType, uint8_t diameter, uint8_t oceanLevel);
		void           FillUnderHeightMap(Chunk* chunk, ChunkHeightMap heightMap);
		Chunk*         GenerateChunkAt(vec2 position, WorldType worldType, uint8_t chunkDiameter, uint8_t chunkHeight, uint8_t oceanLevel);
		void           SetSeed(int seed);
		int            GetSeed() const;

	protected:
		ChunkHeightMap GenerateFlatHeightMap(uint8_t diameter, uint8_t oceanLevel);
		ChunkHeightMap GenerateHeightMapFromNoise(vec2 position, uint8_t diameter);

	private:
		Logger        m_Logger;
		int           m_Seed;
		uint8_t       m_MinGenHeight;
		uint8_t       m_MaxGenHeight;
		FastNoiseLite m_Noise;
	};
}; // namespace world
