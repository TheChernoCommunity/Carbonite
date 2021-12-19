#pragma once

#include "Chunk.h"

#include <vector>

class Dimension
{
public:
	Dimension();
	~Dimension();

private:
	std::vector<Chunk> m_LoadedChunks;
};
