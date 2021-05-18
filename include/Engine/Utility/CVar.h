//
//	Created by Sausty on 18. May. 2021
//

#pragma once

#include <string>
#include <fstream>
#include <iostream>

namespace gp1
{
	template<typename T>
	class CVar
	{
	public:
		CVar(T initialiser, const std::string& name);

		void LoadFromFile(std::ifstream& stream);

		T Get() { return m_Value; }
		void Set(T value) { m_Value = value; }

		operator T() const {
			return m_Value;
		}

		std::ostream& operator<<(std::ostream& os)
		{
			return os << m_Name << " : " << m_Value;
		}

		const std::string& GetName() const { return m_Name; }
	private:
		std::string m_Name;
		T m_Value;
	};

	using CVar_Int = CVar<int>;
	using CVar_Float = CVar<float>;
	using CVar_String = CVar<std::string>;

	template<typename T>
	inline CVar<T>::CVar(T initialiser, const std::string& name)
		: m_Value(initialiser), m_Name(name)
	{
	}

	template<typename T>
	inline void CVar<T>::LoadFromFile(std::ifstream& stream)
	{
		if (stream.is_open())
		{
			std::string name;
			T value{};
			stream >> name >> value;

			if (name == m_Name)
			{
				m_Value = (T)value;
			}
		}
	}
}
