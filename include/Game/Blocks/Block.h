//
//	Created by Brandon Burton (Izodn) on 30. Aug. 2021
//

#pragma once

namespace blocks
{
	enum class BlockType
	{
		Void,
		Air,
		MoonRock,
		Ocean,
	};

	class Block
	{
	public:
		BlockType GetType() const
		{
			return m_Type;
		};

	protected:
		BlockType m_Type;
	};
}; // namespace blocks
