#pragma once

#include "Class.h"

namespace CSharp
{
	class Namespace
	{
	public:
		friend class Assembly;

	public:
		Namespace(std::uint64_t hash, class Assembly* assembly);

		auto getAssembly() { return m_Assembly; }
		auto getAssembly() const { return m_Assembly; }

		auto& getClasses() const { return m_Classes; }

		Class*       getClass(std::string_view name);
		const Class* getClass(std::string_view name) const;
		Class*       getClass(std::uint64_t hash);
		const Class* getClass(std::uint64_t hash) const;

	private:
		std::uint64_t   m_Hash;
		class Assembly* m_Assembly;

		std::unordered_map<std::uint64_t, Class> m_Classes;
	};
} // namespace CSharp