//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#include "Engine/Renderer/Texture/Texture3D.h"

namespace gp1::renderer::texture
{
	Texture3D::Texture3D()
	    : Data(this) {}

	void Texture3D::MarkDirty()
	{
		this->m_Dirty = this->m_Editable;
	}

	void Texture3D::ClearDirty()
	{
		this->m_Dirty = false;
	}

	bool Texture3D::IsDirty()
	{
		return this->m_Dirty;
	}

	bool Texture3D::IsEditable()
	{
		return this->m_Editable;
	}

	bool Texture3D::IsDynamic()
	{
		return this->m_IsDynamic;
	}

} // namespace gp1::renderer::texture
