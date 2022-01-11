#include "PCH.h"

#include "Assembly.h"

#include <mono/metadata/assembly.h>
#include <mono/metadata/image.h>
#include <mono/metadata/tokentype.h>

#include <stdexcept>
#include <xhash>

namespace CSharp
{
	Assembly::Assembly(std::uint64_t hash, MonoAssembly* assembly, MonoImage* image)
	    : m_Hash(hash), m_Assembly(assembly), m_Image(image)
	{
		parseMetadata();
	}

	Assembly::~Assembly()
	{
		if (m_Assembly)
		{
			mono_assembly_close(m_Assembly);

			m_Assembly = nullptr;
			m_Image    = nullptr;
		}
	}

	Namespace* Assembly::getNamespace(std::string_view space)
	{
		return getNamespace(std::hash<std::string_view>()(space));
	}

	const Namespace* Assembly::getNamespace(std::string_view space) const
	{
		return getNamespace(std::hash<std::string_view>()(space));
	}

	Namespace* Assembly::getNamespace(std::uint64_t hash)
	{
		auto itr = m_Namespaces.find(hash);
		return itr != m_Namespaces.end() ? &itr->second : nullptr;
	}

	const Namespace* Assembly::getNamespace(std::uint64_t hash) const
	{
		auto itr = m_Namespaces.find(hash);
		return itr != m_Namespaces.end() ? &itr->second : nullptr;
	}

	Class* Assembly::getClass(std::string_view space, std::string_view name)
	{
		Namespace* namespc = getNamespace(space);
		return namespc ? namespc->getClass(name) : nullptr;
	}

	const Class* Assembly::getClass(std::string_view space, std::string_view name) const
	{
		const Namespace* namespc = getNamespace(space);
		return namespc ? namespc->getClass(name) : nullptr;
	}

	Class* Assembly::getClass(std::uint64_t spaceHash, std::uint64_t nameHash)
	{
		Namespace* namespc = getNamespace(spaceHash);
		return namespc ? namespc->getClass(nameHash) : nullptr;
	}

	const Class* Assembly::getClass(std::uint64_t spaceHash, std::uint64_t nameHash) const
	{
		const Namespace* namespc = getNamespace(spaceHash);
		return namespc ? namespc->getClass(nameHash) : nullptr;
	}

	void Assembly::parseMetadata()
	{
		const MonoTableInfo* typedefTableInfo = mono_image_get_table_info(m_Image, MONO_TABLE_TYPEDEF);
		std::int32_t         typedefRows      = mono_table_info_get_rows(typedefTableInfo);

		for (std::int32_t i = 1; i < typedefRows; ++i)
		{
			MonoClass* monoClass = mono_class_get(m_Image, (i + 1) | MONO_TOKEN_TYPE_DEF);

			const char* monoNamespace = mono_class_get_namespace(monoClass);
			const char* monoClassName = mono_class_get_name(monoClass);

			Namespace* namespc = nullptr;

			{
				std::uint64_t monoNamespaceHash = std::hash<std::string_view>()(monoNamespace);

				auto itr = m_Namespaces.find(monoNamespaceHash);
				if (itr == m_Namespaces.end())
					itr = m_Namespaces.insert({ monoNamespaceHash, { monoNamespaceHash, this } }).first;
				namespc = &itr->second;
			}

			Class clazz = { std::hash<std::string_view>()(monoClassName), namespc, monoClass };
			clazz.parseMetadata();
			namespc->m_Classes.insert({ clazz.m_Hash, std::move(clazz) });
		}
	}
} // namespace CSharp