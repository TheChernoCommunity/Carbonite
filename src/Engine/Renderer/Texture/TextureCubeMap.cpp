//
//	Created by MarcasRealAccount on 6. Dec. 2020.
//

#include "Engine/Renderer/Texture/TextureCubeMap.h"

namespace gp1::renderer::texture
{
	TextureCubeMap::TextureCubeMap()
	    : Data(this) {}

	void TextureCubeMap::MarkDirty()
	{
		this->m_Dirty = this->m_Editable;
	}

	void TextureCubeMap::ClearDirty()
	{
		this->m_Dirty = false;
	}

	bool TextureCubeMap::IsDirty()
	{
		return this->m_Dirty;
	}

	bool TextureCubeMap::IsEditable()
	{
		return this->m_Editable;
	}

	bool TextureCubeMap::IsDynamic()
	{
		return this->m_IsDynamic;
	}

} // namespace gp1::renderer::texture
