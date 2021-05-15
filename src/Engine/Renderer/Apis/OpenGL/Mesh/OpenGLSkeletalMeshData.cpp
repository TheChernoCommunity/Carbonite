//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLSkeletalMeshData.h"

namespace gp1::renderer::apis::opengl::mesh
{
	OpenGLSkeletalMeshData::OpenGLSkeletalMeshData(renderer::mesh::SkeletalMesh* skeletalMesh)
	    : OpenGLMeshData(skeletalMesh) {}

	bool OpenGLSkeletalMeshData::HasVertices()
	{
		return GetDataUnsafe<renderer::mesh::SkeletalMesh>()->m_Vertices.size() > 0;
	}

	uint32_t OpenGLSkeletalMeshData::GetCustomDataSize()
	{
		return static_cast<uint32_t>(GetDataUnsafe<renderer::mesh::SkeletalMesh>()->m_Vertices.size());
	}

	void OpenGLSkeletalMeshData::InitCustomGLData()
	{
		renderer::mesh::SkeletalMesh* mesh = GetDataUnsafe<renderer::mesh::SkeletalMesh>();
		CreateVBOs(this->m_NumVBOs + 1);
		BindNextVBO(GL_ARRAY_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, mesh->m_Vertices.size() * sizeof(renderer::mesh::SkeletalMeshVertex), mesh->m_Vertices.data(), GL_STATIC_DRAW);
		CreateVertexAttribArrays(5);
		SetVertexAttribPointer(static_cast<uint32_t>(renderer::mesh::VertexAttribIndex::POSITION), 3, GL_FLOAT, false, sizeof(renderer::mesh::SkeletalMeshVertex), offsetof(renderer::mesh::SkeletalMeshVertex, position));
		SetVertexAttribPointer(static_cast<uint32_t>(renderer::mesh::VertexAttribIndex::NORMAL), 3, GL_FLOAT, false, sizeof(renderer::mesh::SkeletalMeshVertex), offsetof(renderer::mesh::SkeletalMeshVertex, normal));
		SetVertexAttribPointer(static_cast<uint32_t>(renderer::mesh::VertexAttribIndex::UV), 2, GL_FLOAT, false, sizeof(renderer::mesh::SkeletalMeshVertex), offsetof(renderer::mesh::SkeletalMeshVertex, uv));
		SetVertexAttribIPointer(static_cast<uint32_t>(renderer::mesh::VertexAttribIndex::JOINT_INDICES), 3, GL_UNSIGNED_INT, sizeof(renderer::mesh::SkeletalMeshVertex), offsetof(renderer::mesh::SkeletalMeshVertex, jointIndices));
		SetVertexAttribPointer(static_cast<uint32_t>(renderer::mesh::VertexAttribIndex::JOINT_WEIGHTS), 3, GL_FLOAT, false, sizeof(renderer::mesh::SkeletalMeshVertex), offsetof(renderer::mesh::SkeletalMeshVertex, jointWeights));
		UnbindVBO(GL_ARRAY_BUFFER);
	}

	void OpenGLSkeletalMeshData::ClearCustomData()
	{
		GetDataUnsafe<renderer::mesh::SkeletalMesh>()->m_Vertices.clear();
	}

} // namespace gp1::renderer::apis::opengl::mesh
