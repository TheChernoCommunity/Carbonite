#pragma once
#include "Game/Block/Block.h"
#include "Game/Item/Item.h"


namespace gp1
{
	class BlockItem : public Block, public Item
	{
	public:
	protected:
		BlockItem(std::string& id);
	private:
		std::string m_ID;
	};
}
