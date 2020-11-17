#include "Game/BlockItem/BlockItem.h"

namespace gp1
{
	BlockItem::BlockItem(std::string& id)
		: m_ID(id), Block(m_ID), Item(m_ID, false, false)
	{
		
	}

}
