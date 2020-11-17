#pragma once

#include <vector>

#include "Item.h"

namespace gp1
{
	class ItemRegistry
	{
	public:
		ItemRegistry();

		void PushItem(Item* item);
		void PopItem(Item* item);
		
		std::vector<Item*>::iterator begin() { return m_Items.begin(); }
		std::vector<Item*>::iterator end() { return m_Items.end(); }
		std::vector<Item*>::reverse_iterator rbegin() { return m_Items.rbegin(); }
		std::vector<Item*>::reverse_iterator rend() { return m_Items.rend(); }

		std::vector<Item*>::const_iterator begin() const { return m_Items.begin(); }
		std::vector<Item*>::const_iterator end()	const { return m_Items.end(); }
		std::vector<Item*>::const_reverse_iterator rbegin() const { return m_Items.rbegin(); }
		std::vector<Item*>::const_reverse_iterator rend() const { return m_Items.rend(); }
	private:
		std::vector<Item*> m_Items;
	};
}
