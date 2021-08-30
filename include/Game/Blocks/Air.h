//
//	Created by Brandon Burton (Izodn) on 30. Aug. 2021
//

#pragma once

#include "Block.h"

namespace blocks
{
	class Air : virtual public Block
	{
	protected:
		BlockType m_Type = BlockType::Air;
	};
}; // namespace blocks
