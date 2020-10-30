//	
//	Created by MarcasRealAccount on 30. Oct. 2020
//	

#include "Engine/Renderer/StaticMesh.h"

namespace gp1 {

	MeshData* StaticMesh::CreateCustomMeshData(Renderer* renderer) {
		return renderer->CreateStaticMeshData(this);
	}

	OpenGLStaticMeshData::OpenGLStaticMeshData(Mesh* mesh)
		: OpenGLMeshData(mesh) {}

	bool OpenGLStaticMeshData::HasVertices() {
		return reinterpret_cast<StaticMesh*>(GetMesh())->m_Vertices.size() > 0;
	}

	uint32_t OpenGLStaticMeshData::GetCustomDataSize() {
		return static_cast<uint32_t>(reinterpret_cast<StaticMesh*>(GetMesh())->m_Vertices.size());
	}

	void OpenGLStaticMeshData::InitCustomGLData() {
		CreateVBOs(this->m_NumVBOs + 1);
		BindNextVBO(GL_ARRAY_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, reinterpret_cast<StaticMesh*>(GetMesh())->m_Vertices.size() * sizeof(StaticMeshVertex), reinterpret_cast<StaticMesh*>(GetMesh())->m_Vertices.data(), GL_STATIC_DRAW);
		CreateVertexAttribArrays(3);
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::POSITION), 3, GL_FLOAT, false, sizeof(StaticMeshVertex), offsetof(StaticMeshVertex, position));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::NORMAL), 3, GL_FLOAT, false, sizeof(StaticMeshVertex), offsetof(StaticMeshVertex, normal));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::UV), 2, GL_FLOAT, false, sizeof(StaticMeshVertex), offsetof(StaticMeshVertex, uv));
		UnbindVBO(GL_ARRAY_BUFFER);
	}

	void OpenGLStaticMeshData::ClearCustomData() {
		reinterpret_cast<StaticMesh*>(GetMesh())->m_Vertices.clear();
	}

} // namespace gp1
