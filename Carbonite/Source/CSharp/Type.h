#pragma once

#include <mono/metadata/metadata.h>

#include <cstdint>

namespace CSharp
{
	class Type
	{
	public:
		friend class Assembly;

	public:
		Type(std::uint64_t hash, class Class* clazz, MonoType* type);

		auto getClass() { return m_Class; }
		auto getClass() const { return m_Class; }

	private:
		std::uint64_t m_Hash;
		class Class*  m_Class;

		MonoType* m_Type;
	};
} // namespace CSharp