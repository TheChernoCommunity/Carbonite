#include "PCH.h"

#include "Mod/Mod.h"

ModInfo::ModInfo(std::string_view id)
    : m_Id(id) {}

Mod::Mod(const ModInfo& info)
    : m_Info(info) {}