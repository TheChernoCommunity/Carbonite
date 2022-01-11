#pragma once

#include "Class.h"
#include "Namespace.h"

#include <mono/metadata/image.h>

#include <cstdint>

#include <string_view>
#include <unordered_map>

namespace CSharp
{
	class Assembly
	{
	public:
		friend class Runtime;

	public:
		Assembly(std::uint64_t hash, MonoAssembly* assembly, MonoImage* image);
		~Assembly();

		auto& getNamespaces() const { return m_Namespaces; }

		Namespace*       getNamespace(std::string_view space);
		const Namespace* getNamespace(std::string_view space) const;
		Namespace*       getNamespace(std::uint64_t hash);
		const Namespace* getNamespace(std::uint64_t hash) const;

		Class*       getClass(std::string_view space, std::string_view name);
		const Class* getClass(std::string_view space, std::string_view name) const;
		Class*       getClass(std::uint64_t spaceHash, std::uint64_t nameHash);
		const Class* getClass(std::uint64_t spaceHash, std::uint64_t nameHash) const;

	private:
		void parseMetadata();

	private:
		std::uint64_t m_Hash;

		MonoAssembly* m_Assembly;
		MonoImage*    m_Image;

		std::unordered_map<std::uint64_t, Namespace> m_Namespaces;
	};
} // namespace CSharp