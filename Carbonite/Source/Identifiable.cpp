#include <limits>
#include <random>
#include <unordered_set>

#include "Utils/Identifiable.h"

namespace
{
	static std::random_device                      s_randomDevice;
	static std::default_random_engine              s_engine(s_randomDevice());
	static std::uniform_int_distribution<uint64_t> s_uniformDist(std::numeric_limits<std::uint64_t>::min(), std::numeric_limits<std::uint64_t>::max());
	static std::unordered_set<uint64_t>            s_usedIDs;
} // namespace


Identifiable::Identifiable()
{
	id = s_uniformDist(s_engine);

	while (s_usedIDs.find(id) != s_usedIDs.end())
	{
		id = s_uniformDist(s_engine);
	}

	s_usedIDs.insert(id);
}

uint64_t Identifiable::getID()
{
	return id;
}

Identifiable::~Identifiable()
{
	s_usedIDs.erase(id);
}
