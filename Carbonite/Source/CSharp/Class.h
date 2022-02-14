#pragma once

#include "Type.h"
#include "Visibility.h"

#include <mono/metadata/class.h>

#include <cstdint>

#include <string_view>
#include <unordered_map>

namespace CSharp
{
	class Field
	{
	public:
		friend class Class;

	public:
		Field(std::uint64_t hash, class Class* clazz, MonoClassField* field);

		auto getClass() { return m_Class; }
		auto getClass() const { return m_Class; }

		auto getName() const { return m_Name; }
		auto getVisibility() const { return m_Visibility; }
		auto getType() const { return m_Type; }

	private:
		std::uint64_t m_Hash;
		class Class*  m_Class;

		MonoClassField*  m_Field;
		std::string_view m_Name;
		EVisibility      m_Visibility;
		Type*            m_Type;
	};

	class Class
	{
	public:
		friend class Assembly;

	public:
		Class(std::uint64_t hash, class Namespace* namespc, MonoClass* clazz);

		auto getNamespace() { return m_Namespace; }
		auto getNamespace() const { return m_Namespace; }

		class Assembly*       getAssembly();
		const class Assembly* getAssembly() const;

		auto  getName() const { return m_Name; }
		auto  getVisibility() const { return m_Visibility; }
		auto* getType() { return &m_Type; }
		auto* getType() const { return &m_Type; }

		auto& getFields() const { return m_Fields; }

		Field*       getField(std::string_view name);
		const Field* getField(std::string_view name) const;
		Field*       getField(std::uint64_t hash);
		const Field* getField(std::uint64_t hash) const;

	private:
		void parseMetadata();

	private:
		std::uint64_t    m_Hash;
		class Namespace* m_Namespace;

		MonoClass*       m_Class;
		std::string_view m_Name;
		EVisibility      m_Visibility;
		Type             m_Type;

		std::unordered_map<std::uint64_t, Field> m_Fields;
	};
} // namespace CSharp