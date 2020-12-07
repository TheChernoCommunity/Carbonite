//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#include "Engine/Renderer/Texture/Texture2DArray.h"

namespace gp1::renderer::texture
{
	Texture2DArray::Texture2DArray()
	    : Data(this) {}

	void Texture2DArray::MarkDirty()
	{
		this->m_Dirty = this->m_Editable;
	}

	void Texture2DArray::ClearDirty()
	{
		this->m_Dirty = false;
	}

	bool Texture2DArray::IsDirty()
	{
		return this->m_Dirty;
	}

	bool Texture2DArray::IsEditable()
	{
		return this->m_Editable;
	}

	bool Texture2DArray::IsDynamic()
	{
		return this->m_IsDynamic;
	}

} // namespace gp1::renderer::texture
