//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Renderer/Mesh/Mesh.h"

namespace gp1 {

	Mesh::~Mesh() {
		if (this->m_MeshData) {
			this->m_MeshData->CleanUp();
			delete this->m_MeshData;
		}
	}

	void Mesh::MarkDirty() {
		this->m_Dirty = this->m_Editable;
	}

	void Mesh::ClearDirty() {
		this->m_Dirty = false;
	}

	bool Mesh::IsDirty() {
		return this->m_Dirty;
	}

	bool Mesh::IsEditable() {
		return this->m_Editable;
	}

	bool Mesh::IsDynamic() {
		return this->m_IsDynamic;
	}

	MeshData* Mesh::GetMeshData(Renderer* renderer) {
		if (!this->m_MeshData || !renderer->IsMeshDataUsable(this->m_MeshData)) {
			if (this->m_MeshData) {
				this->m_MeshData->CleanUp();
				delete this->m_MeshData;
			}
			this->m_MeshData = CreateCustomMeshData(renderer);
		}
		return this->m_MeshData;
	}

	MeshData::MeshData(Mesh* mesh)
		: m_Mesh(mesh) {}

	MeshData::~MeshData() {
		this->m_Mesh->m_MeshData = nullptr;
	}

} // namespace gp1
