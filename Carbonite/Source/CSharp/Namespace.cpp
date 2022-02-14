#include "Namespace.h"

namespace CSharp
{
	Namespace::Namespace(std::uint64_t hash, class Assembly* assembly)
	    : m_Hash(hash), m_Assembly(assembly) {}

	Class* Namespace::getClass(std::string_view name)
	{
		return getClass(std::hash<std::string_view>()(name));
	}

	const Class* Namespace::getClass(std::string_view name) const
	{
		return getClass(std::hash<std::string_view>()(name));
	}

	Class* Namespace::getClass(std::uint64_t hash)
	{
		auto itr = m_Classes.find(hash);
		return itr != m_Classes.end() ? &itr->second : nullptr;
	}

	const Class* Namespace::getClass(std::uint64_t hash) const
	{
		auto itr = m_Classes.find(hash);
		return itr != m_Classes.end() ? &itr->second : nullptr;
	}
} // namespace CSharp