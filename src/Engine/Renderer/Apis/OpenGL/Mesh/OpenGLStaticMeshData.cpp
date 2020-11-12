//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLStaticMeshData.h"

namespace gp1 {

	OpenGLStaticMeshData::OpenGLStaticMeshData(Mesh* mesh)
		: OpenGLMeshData(mesh) {}

	bool OpenGLStaticMeshData::HasVertices() {
		return GetMesh<StaticMesh>()->m_Vertices.size() > 0;
	}

	uint32_t OpenGLStaticMeshData::GetCustomDataSize() {
		return static_cast<uint32_t>(GetMesh<StaticMesh>()->m_Vertices.size());
	}

	void OpenGLStaticMeshData::InitCustomGLData() {
		CreateVBOs(this->m_NumVBOs + 1);
		BindNextVBO(GL_ARRAY_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, GetMesh<StaticMesh>()->m_Vertices.size() * sizeof(StaticMeshVertex), GetMesh<StaticMesh>()->m_Vertices.data(), GL_STATIC_DRAW);
		CreateVertexAttribArrays(3);
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::POSITION), 3, GL_FLOAT, false, sizeof(StaticMeshVertex), offsetof(StaticMeshVertex, position));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::NORMAL), 3, GL_FLOAT, false, sizeof(StaticMeshVertex), offsetof(StaticMeshVertex, normal));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::UV), 2, GL_FLOAT, false, sizeof(StaticMeshVertex), offsetof(StaticMeshVertex, uv));
		UnbindVBO(GL_ARRAY_BUFFER);
	}

	void OpenGLStaticMeshData::ClearCustomData() {
		GetMesh<StaticMesh>()->m_Vertices.clear();
	}

} // namespace gp1
