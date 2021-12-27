#include "PCH.h"

#include "Handle.h"

#include <algorithm>

namespace Graphics::Detail
{
	void HandleBase::addChild(HandleBase* child)
	{
		m_Children.push_back(child);
	}

	void HandleBase::removeChild(HandleBase* child)
	{
		auto itr = std::find(m_Children.begin(), m_Children.end(), child);
		if (itr != m_Children.end())
		{
			if (m_ChildItr < m_Children.size() && m_Children.begin() + m_ChildItr < itr)
				--m_ChildItr;
			m_Children.erase(itr);
		}
	}
} // namespace Graphics::Detail
