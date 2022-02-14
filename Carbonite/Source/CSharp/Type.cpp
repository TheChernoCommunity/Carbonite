#include "Type.h"

namespace CSharp
{
	Type::Type(std::uint64_t hash, class Class* clazz, MonoType* type)
	    : m_Hash(hash), m_Class(clazz), m_Type(type) {}
} // namespace CSharp