#pragma once

#include <cstdint>

class Identifiable
{
	uint64_t id;

public:
	Identifiable();
	uint64_t getID();
	~Identifiable();
};