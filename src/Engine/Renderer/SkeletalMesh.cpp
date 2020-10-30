//	
//	Created by MarcasRealAccount on 30. Oct. 2020
//	

#include "Engine/Renderer/SkeletalMesh.h"

namespace gp1 {

	MeshData* SkeletalMesh::CreateCustomMeshData(Renderer* renderer) {
		return renderer->CreateSkeletalMeshData(this);
	}

	OpenGLSkeletalMeshData::OpenGLSkeletalMeshData(Mesh* mesh)
		: OpenGLMeshData(mesh) {}

	bool OpenGLSkeletalMeshData::HasVertices() {
		return reinterpret_cast<SkeletalMesh*>(GetMesh())->m_Vertices.size() > 0;
	}

	uint32_t OpenGLSkeletalMeshData::GetCustomDataSize() {
		return static_cast<uint32_t>(reinterpret_cast<SkeletalMesh*>(GetMesh())->m_Vertices.size());
	}

	void OpenGLSkeletalMeshData::InitCustomGLData() {
		CreateVBOs(this->m_NumVBOs + 1);
		BindNextVBO(GL_ARRAY_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, reinterpret_cast<SkeletalMesh*>(GetMesh())->m_Vertices.size() * sizeof(SkeletalMeshVertex), reinterpret_cast<SkeletalMesh*>(GetMesh())->m_Vertices.data(), GL_STATIC_DRAW);
		CreateVertexAttribArrays(5);
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::POSITION), 3, GL_FLOAT, false, sizeof(SkeletalMeshVertex), offsetof(SkeletalMeshVertex, position));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::NORMAL), 3, GL_FLOAT, false, sizeof(SkeletalMeshVertex), offsetof(SkeletalMeshVertex, normal));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::UV), 2, GL_FLOAT, false, sizeof(SkeletalMeshVertex), offsetof(SkeletalMeshVertex, uv));
		SetVertexAttribIPointer(static_cast<uint32_t>(VertexAttribIndex::JOINT_INDICES), 3, GL_UNSIGNED_INT, sizeof(SkeletalMeshVertex), offsetof(SkeletalMeshVertex, jointIndices));
		SetVertexAttribPointer(static_cast<uint32_t>(VertexAttribIndex::JOINT_WEIGHTS), 3, GL_FLOAT, false, sizeof(SkeletalMeshVertex), offsetof(SkeletalMeshVertex, jointWeights));
		UnbindVBO(GL_ARRAY_BUFFER);
	}

	void OpenGLSkeletalMeshData::ClearCustomData() {
		reinterpret_cast<SkeletalMesh*>(GetMesh())->m_Vertices.clear();
	}

} // namespace gp1
