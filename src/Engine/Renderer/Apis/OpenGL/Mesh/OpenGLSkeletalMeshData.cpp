//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLSkeletalMeshData.h"

namespace gp1 {

	OpenGLSkeletalMeshData::OpenGLSkeletalMeshData(Mesh* mesh)
		: OpenGLMeshData(mesh) {}

	bool OpenGLSkeletalMeshData::HasVertices() {
		return GetMesh<SkeletalMesh>()->m_Vertices.size() > 0;
	}

	uint32_t OpenGLSkeletalMeshData::GetCustomDataSize() {
		return static_cast<uint32_t>(GetMesh<SkeletalMesh>()->m_Vertices.size());
	}

	void OpenGLSkeletalMeshData::InitCustomGLData() {
		CreateVBOs(this->m_NumVBOs + 1);
		BindNextVBO(GL_ARRAY_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, GetMesh<SkeletalMesh>()->m_Vertices.size() * sizeof(SkeletalMeshVertex), GetMesh<SkeletalMesh>()->m_Vertices.data(), GL_STATIC_DRAW);
		CreateVertexAttribArrays(5);
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::POSITION), 3, GL_FLOAT, false, sizeof(SkeletalMeshVertex), offsetof(SkeletalMeshVertex, position));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::NORMAL), 3, GL_FLOAT, false, sizeof(SkeletalMeshVertex), offsetof(SkeletalMeshVertex, normal));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::UV), 2, GL_FLOAT, false, sizeof(SkeletalMeshVertex), offsetof(SkeletalMeshVertex, uv));
		SetVertexAttribIPointer(static_cast<uint32_t>(VertexAttribIndex::JOINT_INDICES), 3, GL_UNSIGNED_INT, sizeof(SkeletalMeshVertex), offsetof(SkeletalMeshVertex, jointIndices));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::JOINT_WEIGHTS), 3, GL_FLOAT, false, sizeof(SkeletalMeshVertex), offsetof(SkeletalMeshVertex, jointWeights));
		UnbindVBO(GL_ARRAY_BUFFER);
	}

	void OpenGLSkeletalMeshData::ClearCustomData() {
		GetMesh<SkeletalMesh>()->m_Vertices.clear();
	}

} // namespace gp1
