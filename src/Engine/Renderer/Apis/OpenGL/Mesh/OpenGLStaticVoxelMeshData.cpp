//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLStaticVoxelMeshData.h"

namespace gp1::renderer::apis::opengl::mesh
{
	OpenGLStaticVoxelMeshData::OpenGLStaticVoxelMeshData(renderer::mesh::StaticVoxelMesh* staticVoxelMesh)
	    : OpenGLMeshData(staticVoxelMesh) {}

	bool OpenGLStaticVoxelMeshData::HasVertices()
	{
		return GetDataUnsafe<renderer::mesh::StaticVoxelMesh>()->m_Vertices.size() > 0;
	}

	uint32_t OpenGLStaticVoxelMeshData::GetCustomDataSize()
	{
		return static_cast<uint32_t>(GetDataUnsafe<renderer::mesh::StaticVoxelMesh>()->m_Vertices.size());
	}

	void OpenGLStaticVoxelMeshData::InitCustomGLData()
	{
		renderer::mesh::StaticVoxelMesh* mesh = GetDataUnsafe<renderer::mesh::StaticVoxelMesh>();
		CreateVBOs(this->m_NumVBOs + 1);
		BindNextVBO(GL_ARRAY_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, mesh->m_Vertices.size() * sizeof(renderer::mesh::StaticVoxelMeshVertex), mesh->m_Vertices.data(), GL_STATIC_DRAW);
		CreateVertexAttribArrays(4);
		SetVertexAttribPointer(static_cast<uint32_t>(renderer::mesh::VertexAttribIndex::POSITION), 3, GL_FLOAT, false, sizeof(renderer::mesh::StaticVoxelMeshVertex), offsetof(renderer::mesh::StaticVoxelMeshVertex, position));
		SetVertexAttribPointer(static_cast<uint32_t>(renderer::mesh::VertexAttribIndex::NORMAL), 3, GL_FLOAT, false, sizeof(renderer::mesh::StaticVoxelMeshVertex), offsetof(renderer::mesh::StaticVoxelMeshVertex, normal));
		SetVertexAttribPointer(static_cast<uint32_t>(renderer::mesh::VertexAttribIndex::UV), 2, GL_FLOAT, false, sizeof(renderer::mesh::StaticVoxelMeshVertex), offsetof(renderer::mesh::StaticVoxelMeshVertex, uv));
		SetVertexAttribIPointer(static_cast<uint32_t>(renderer::mesh::VertexAttribIndex::SSBO_INDEX), 1, GL_UNSIGNED_INT, sizeof(renderer::mesh::StaticVoxelMeshVertex), offsetof(renderer::mesh::StaticVoxelMeshVertex, SSBOIndex));
		UnbindVBO(GL_ARRAY_BUFFER);
	}

	void OpenGLStaticVoxelMeshData::ClearCustomData()
	{
		GetDataUnsafe<renderer::mesh::StaticVoxelMesh>()->m_Vertices.clear();
	}

} // namespace gp1::renderer::apis::opengl::mesh
