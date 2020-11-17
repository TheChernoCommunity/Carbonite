#pragma once
#include <string>

namespace gp1
{
	class Item
	{
	protected:
		Item(std::string& id, bool isWearable, bool isConsumable);
	private:
		bool m_IsWearable;
		bool m_IsConsumable;
		std::string m_ID;
	};
}
