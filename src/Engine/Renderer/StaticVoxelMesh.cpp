//	
//	Created by MarcasRealAccount on 30. Oct. 2020
//	

#include "Engine/Renderer/StaticVoxelMesh.h"

namespace gp1 {

	MeshData* StaticVoxelMesh::CreateCustomMeshData(Renderer* renderer) {
		return renderer->CreateStaticVoxelMeshData(this);
	}

	OpenGLStaticVoxelMeshData::OpenGLStaticVoxelMeshData(Mesh* mesh)
		: OpenGLMeshData(mesh) {}

	bool OpenGLStaticVoxelMeshData::HasVertices() {
		return reinterpret_cast<StaticVoxelMesh*>(GetMesh())->m_Vertices.size() > 0;
	}

	uint32_t OpenGLStaticVoxelMeshData::GetCustomDataSize() {
		return static_cast<uint32_t>(reinterpret_cast<StaticVoxelMesh*>(GetMesh())->m_Vertices.size());
	}

	void OpenGLStaticVoxelMeshData::InitCustomGLData() {
		CreateVBOs(this->m_NumVBOs + 1);
		BindNextVBO(GL_ARRAY_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, reinterpret_cast<StaticVoxelMesh*>(GetMesh())->m_Vertices.size() * sizeof(StaticVoxelMeshVertex), reinterpret_cast<StaticVoxelMesh*>(GetMesh())->m_Vertices.data(), GL_STATIC_DRAW);
		CreateVertexAttribArrays(4);
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::POSITION), 3, GL_FLOAT, false, sizeof(StaticVoxelMeshVertex), offsetof(StaticVoxelMeshVertex, position));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::NORMAL), 3, GL_FLOAT, false, sizeof(StaticVoxelMeshVertex), offsetof(StaticVoxelMeshVertex, normal));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::UV), 2, GL_FLOAT, false, sizeof(StaticVoxelMeshVertex), offsetof(StaticVoxelMeshVertex, uv));
		SetVertexAttribIPointer(static_cast<uint32_t>(VertexAttribIndex::SSBO_INDEX), 1, GL_UNSIGNED_INT, sizeof(StaticVoxelMeshVertex), offsetof(StaticVoxelMeshVertex, SSBOIndex));
		UnbindVBO(GL_ARRAY_BUFFER);
	}

	void OpenGLStaticVoxelMeshData::ClearCustomData() {
		reinterpret_cast<StaticVoxelMesh*>(GetMesh())->m_Vertices.clear();
	}

} // namespace gp1
