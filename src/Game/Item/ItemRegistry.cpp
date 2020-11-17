#include "Game/Item/ItemRegistry.h"

namespace gp1
{
	ItemRegistry::ItemRegistry()
	{
		
	}

	void ItemRegistry::PushItem(Item* item)
	{
		m_Items.push_back(item);
	}


	void ItemRegistry::PopItem(Item* item)
	{
		auto it = std::find(m_Items.begin(), m_Items.end(), item);
		m_Items.erase(it);
	}
}
