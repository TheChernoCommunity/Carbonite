//
//	Created by Sausty on 18. May. 2021
//

#include <Engine/Utility/CVarSystem.h>

namespace gp1
{
	CVarSystem::CVarSystem(const std::string& path)
		: m_Path(path)
	{
		m_Stream = std::ifstream(path);
	}

	CVarSystem::~CVarSystem()
	{
		m_Stream.close();
	}

	CVar_Int CVarSystem::GetCVarInt(const std::string& name, int defaultValue)
	{
		for (auto& cvar : m_CVarsInt)
		{
			if (cvar.GetName() == name)
			{
				return cvar;
			}
		}

		// If not found, read from file
		CVar_Int res(defaultValue, name);
		res.LoadFromFile(m_Stream);
		m_CVarsInt.push_back(res);
		return res;
	}

	CVar_String CVarSystem::GetCVarString(const std::string& name, const std::string& defaultValue)
	{
		for (auto& cvar : m_CVarsString)
		{
			if (cvar.GetName() == name)
			{
				return cvar;
			}
		}

		// If not found, read from file
		CVar_String res(defaultValue, name);
		res.LoadFromFile(m_Stream);
		m_CVarsString.push_back(res);
		return res;
	}

	CVar_Float CVarSystem::GetCVarFloat(const std::string& name, float defaultValue)
	{
		for (auto& cvar : m_CVarsFloat)
		{
			if (cvar.GetName() == name)
			{
				return cvar;
			}
		}

		// If not found, read from file
		CVar_Float res(defaultValue, name);
		res.LoadFromFile(m_Stream);
		m_CVarsFloat.push_back(res);
		return res;
	}
}
