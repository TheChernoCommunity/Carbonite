#include "Engine/Renderer/Data.h"

namespace gp1
{
	void Data::MarkDirty()
	{
		m_Dirty = m_Editable;
	}

	void Data::SetNonEditable()
	{
		m_Editable = false;
	}

	void Data::SetDynamic(bool dynamic)
	{
		m_Dynamic = dynamic && m_Editable;
	}
} // namespace gp1