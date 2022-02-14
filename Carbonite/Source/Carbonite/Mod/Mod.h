#pragma once

#include "CSharp/Runtime.h"

#include <string>
#include <string_view>
#include <unordered_map>

struct ModInfo
{
public:
	ModInfo(const std::string& id, bool hasCSharp, const std::unordered_map<std::string, std::string>& dependencies);
	ModInfo(std::string&& id, bool hasCSharp, std::unordered_map<std::string, std::string>&& dependencies);

	auto& getId() const { return m_Id; }
	auto  hasCSharp() const { return m_HasCSharp; }
	auto& getDependencies() const { return m_Dependencies; }

private:
	std::string m_Id;
	bool        m_HasCSharp;

	std::unordered_map<std::string, std::string> m_Dependencies;
};

class Mod
{
public:
	Mod(const ModInfo& info);

	auto& getInfo() const { return m_Info; }
	auto  getAssembly() const { return m_Assembly; }

private:
	ModInfo m_Info;

	CSharp::Assembly* m_Assembly;
};