//
//	Created by MarcasRealAccount on 18. May. 2021.
//

#include "Engine/Renderer/DynamicRendererData.h"

namespace gp1::renderer
{
	void DynamicRendererData::MarkDirty()
	{
		m_Dirty = m_Editable;
	}

	void DynamicRendererData::SetNonEditable()
	{
		m_Editable = false;
	}

	void DynamicRendererData::SetDynamic(bool dynamic)
	{
		m_Dynamic = dynamic && m_Editable;
	}
} // namespace gp1::renderer