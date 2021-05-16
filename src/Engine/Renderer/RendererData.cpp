//
//	Created by MarcasRealAccount on 13. May. 2021
//

#include "Engine/Renderer/RendererData.h"

namespace gp1::renderer
{
	void RendererData::MarkDirty()
	{
		m_Dirty = m_Editable;
	}

	void RendererData::SetNonEditable()
	{
		m_Editable = false;
	}

	void RendererData::SetDynamic(bool dynamic)
	{
		m_Dynamic = dynamic && m_Editable;
	}
} // namespace gp1::renderer