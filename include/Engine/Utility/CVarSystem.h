//
//	Created by Sausty on 18. May. 2021
//

#pragma once

#include <Engine/Utility/CVar.h>
#include <vector>

namespace gp1
{
	class CVarSystem
	{
	public:
		CVarSystem(const std::string& path);
		~CVarSystem();

		CVar_Int GetCVarInt(const std::string& name, int defaultValue);
		CVar_String GetCVarString(const std::string& name, const std::string& defaultValue);
		CVar_Float GetCVarFloat(const std::string& name, float defaultValue);
	private:
		std::vector<CVar_Int> m_CVarsInt;
		std::vector<CVar_String> m_CVarsString;
		std::vector<CVar_Float> m_CVarsFloat;

		std::string m_Path;
		std::ifstream m_Stream;
	};
}
