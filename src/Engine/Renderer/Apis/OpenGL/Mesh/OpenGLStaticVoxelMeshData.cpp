//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLStaticVoxelMeshData.h"

namespace gp1 {

	OpenGLStaticVoxelMeshData::OpenGLStaticVoxelMeshData(Mesh* mesh)
		: OpenGLMeshData(mesh) {}

	bool OpenGLStaticVoxelMeshData::HasVertices() {
		return GetMesh<StaticVoxelMesh>()->m_Vertices.size() > 0;
	}

	uint32_t OpenGLStaticVoxelMeshData::GetCustomDataSize() {
		return static_cast<uint32_t>(GetMesh<StaticVoxelMesh>()->m_Vertices.size());
	}

	void OpenGLStaticVoxelMeshData::InitCustomGLData() {
		CreateVBOs(this->m_NumVBOs + 1);
		BindNextVBO(GL_ARRAY_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, GetMesh<StaticVoxelMesh>()->m_Vertices.size() * sizeof(StaticVoxelMeshVertex), GetMesh<StaticVoxelMesh>()->m_Vertices.data(), GL_STATIC_DRAW);
		CreateVertexAttribArrays(4);
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::POSITION), 3, GL_FLOAT, false, sizeof(StaticVoxelMeshVertex), offsetof(StaticVoxelMeshVertex, position));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::NORMAL), 3, GL_FLOAT, false, sizeof(StaticVoxelMeshVertex), offsetof(StaticVoxelMeshVertex, normal));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::UV), 2, GL_FLOAT, false, sizeof(StaticVoxelMeshVertex), offsetof(StaticVoxelMeshVertex, uv));
		SetVertexAttribIPointer(static_cast<uint32_t>(VertexAttribIndex::SSBO_INDEX), 1, GL_UNSIGNED_INT, sizeof(StaticVoxelMeshVertex), offsetof(StaticVoxelMeshVertex, SSBOIndex));
		UnbindVBO(GL_ARRAY_BUFFER);
	}

	void OpenGLStaticVoxelMeshData::ClearCustomData() {
		GetMesh<StaticVoxelMesh>()->m_Vertices.clear();
	}

} // namespace gp1
