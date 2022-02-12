#include "Class.h"
#include "Namespace.h"
#include "Runtime.h"

#include <mono/metadata/class.h>

namespace CSharp
{
	Field::Field(std::uint64_t hash, class Class* clazz, MonoClassField* field)
	    : m_Hash(hash), m_Class(clazz), m_Field(field)
	{
		m_Name       = mono_field_get_name(m_Field);
		m_Visibility = getVisibilityFromMonoFieldFlags(mono_field_get_flags(m_Field));
		m_Type       = Runtime::Get().getType(mono_field_get_type(m_Field));
	}

	Class::Class(std::uint64_t hash, class Namespace* namespc, MonoClass* clazz)
	    : m_Hash(hash), m_Namespace(namespc), m_Class(clazz), m_Type(hash, this, mono_class_get_type(clazz))
	{
		m_Name       = mono_class_get_name(m_Class);
		m_Visibility = getVisibilityFromMonoClassFlags(mono_class_get_flags(m_Class));
	}

	class Assembly* Class::getAssembly()
	{
		return m_Namespace->getAssembly();
	}

	const class Assembly* Class::getAssembly() const
	{
		return m_Namespace->getAssembly();
	}

	Field* Class::getField(std::string_view name)
	{
		return getField(std::hash<std::string_view>()(name));
	}

	const Field* Class::getField(std::string_view name) const
	{
		return getField(std::hash<std::string_view>()(name));
	}

	Field* Class::getField(std::uint64_t hash)
	{
		auto itr = m_Fields.find(hash);
		return itr != m_Fields.end() ? &itr->second : nullptr;
	}

	const Field* Class::getField(std::uint64_t hash) const
	{
		auto itr = m_Fields.find(hash);
		return itr != m_Fields.end() ? &itr->second : nullptr;
	}

	void Class::parseMetadata()
	{
		MonoClassField* monoField = nullptr;
		void*           fieldPtr  = nullptr;
		while ((monoField = mono_class_get_fields(m_Class, &fieldPtr)) != nullptr)
		{
			const char* name = mono_field_get_name(monoField);

			if (std::strstr(name, "k__BackingField"))
				continue;

			Field field = Field(std::hash<std::string_view>()(name), this, monoField);
			m_Fields.insert({ field.m_Hash, std::move(field) });
		}
	}
} // namespace CSharp