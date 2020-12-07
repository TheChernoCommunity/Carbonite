//
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#include "Engine/Renderer/Mesh/Mesh.h"

namespace gp1::renderer::mesh
{
	void Mesh::MarkDirty()
	{
		this->m_Dirty = this->m_Editable;
	}

	void Mesh::ClearDirty()
	{
		this->m_Dirty = false;
	}

	bool Mesh::IsDirty()
	{
		return this->m_Dirty;
	}

	bool Mesh::IsEditable()
	{
		return this->m_Editable;
	}

	bool Mesh::IsDynamic()
	{
		return this->m_IsDynamic;
	}

} // namespace gp1::renderer::mesh
