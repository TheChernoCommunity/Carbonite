#pragma once

#include <cstdint>

#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

template <class T>
struct RegistryValue
{
public:
	std::string m_Name;
	T           m_Value;
};

template <class T>
class Registry
{
public:
	void clear()
	{
		m_Entries.clear();
		m_NameToId.clear();
	}

	bool addEntry(std::string_view name, std::uint64_t id, T&& value)
	{
		if (m_Entries.find(id) != m_Entries.end() || m_NameToId.find(std::string { name }) != m_NameToId.end())
			return false;

		m_Entries.insert({ id, { name, std::move(value) } });
		m_NameToId.insert({ std::string { name }, id });
		return true;
	}

	T* get(std::uint64_t id) const
	{
		auto itr = m_Entries.find(id);
		return itr != m_Entries.end() ? static_cast<T*>(&itr->second.m_Value) : nullptr;
	}

	T* get(const std::string& name) const
	{
		auto itr = m_NameToId.find(name);
		return itr != m_NameToId.end() ? get(itr->second) : nullptr;
	}

	std::uint64_t getId(const std::string& name) const
	{
		auto itr = m_NameToId.find(name);
		return itr != m_NameToId.end() ? itr->second : ~0ULL;
	}

	std::string getName(std::uint64_t id) const
	{
		auto itr = m_Entries.find(id);
		return itr != m_Entries.end() ? itr->second.m_Name : ~0ULL;
	}

	auto& getEntries() const { return m_Entries; }
	auto& getNameToIds() const { return m_NameToId; }

private:
	std::unordered_map<std::uint64_t, RegistryValue<T>> m_Entries;
	std::unordered_map<std::string, std::uint64_t>      m_NameToId;
};
