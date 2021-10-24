#include "Graphics/Common.h"

#include <algorithm>

namespace Graphics
{
	HandleBase::HandleBase(const std::vector<HandleBase*>& parents)
	    : m_Parents(parents)
	{
		for (auto parent : parents)
			parent->m_Children.push_back(this);
	}

	HandleBase::~HandleBase()
	{
		for (auto parent : m_Parents)
		{
			auto& children = parent->m_Children;
			auto  itr      = std::find(children.begin(), children.end(), this);
			if (itr != children.end())
				children.erase(itr);
		}
		m_Parents.clear();
	}
} // namespace Graphics