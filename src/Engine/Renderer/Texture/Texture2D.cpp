//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#include "Engine/Renderer/Texture/Texture2D.h"

namespace gp1::renderer::texture
{
	Texture2D::Texture2D()
	    : Data(this) {}

	void Texture2D::MarkDirty()
	{
		this->m_Dirty = this->m_Editable;
	}

	void Texture2D::ClearDirty()
	{
		this->m_Dirty = false;
	}

	bool Texture2D::IsDirty()
	{
		return this->m_Dirty;
	}

	bool Texture2D::IsEditable()
	{
		return this->m_Editable;
	}

	bool Texture2D::IsDynamic()
	{
		return this->m_IsDynamic;
	}

} // namespace gp1::renderer::texture
