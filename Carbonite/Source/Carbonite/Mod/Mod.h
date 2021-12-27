#pragma once

#include <string>
#include <string_view>

struct ModInfo
{
public:
	ModInfo(std::string_view id);

	auto& getId() const
	{
		return m_Id;
	}

private:
	std::string m_Id;
};

class Mod
{
public:
	Mod(const ModInfo& info);

	auto& getInfo() const
	{
		return m_Info;
	}

private:
	ModInfo m_Info;
};