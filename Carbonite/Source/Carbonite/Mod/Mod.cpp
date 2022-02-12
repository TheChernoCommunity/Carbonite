#include "Mod.h"

#include <utility>

ModInfo::ModInfo(const std::string& id, bool hasCSharp, const std::unordered_map<std::string, std::string>& dependencies)
    : m_Id(id), m_HasCSharp(hasCSharp), m_Dependencies(dependencies) {}

ModInfo::ModInfo(std::string&& id, bool hasCSharp, std::unordered_map<std::string, std::string>&& dependencies)
    : m_Id(std::move(id)), m_HasCSharp(hasCSharp), m_Dependencies(std::move(dependencies)) {}

Mod::Mod(const ModInfo& info)
    : m_Info(info) {}