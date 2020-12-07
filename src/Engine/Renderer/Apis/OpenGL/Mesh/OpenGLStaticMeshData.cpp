//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Renderer/Apis/OpenGL/Mesh/OpenGLStaticMeshData.h"

namespace gp1::renderer::apis::opengl::mesh
{
	OpenGLStaticMeshData::OpenGLStaticMeshData(renderer::mesh::StaticMesh* staticMesh)
	    : OpenGLMeshData(staticMesh) {}

	bool OpenGLStaticMeshData::HasVertices()
	{
		return GetDataUnsafe<renderer::mesh::StaticMesh>()->m_Vertices.size() > 0;
	}

	uint32_t OpenGLStaticMeshData::GetCustomDataSize()
	{
		return static_cast<uint32_t>(GetDataUnsafe<renderer::mesh::StaticMesh>()->m_Vertices.size());
	}

	void OpenGLStaticMeshData::InitCustomGLData()
	{
		renderer::mesh::StaticMesh* mesh = GetDataUnsafe<renderer::mesh::StaticMesh>();
		CreateVBOs(this->m_NumVBOs + 1);
		BindNextVBO(GL_ARRAY_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, mesh->m_Vertices.size() * sizeof(renderer::mesh::StaticMeshVertex), mesh->m_Vertices.data(), GL_STATIC_DRAW);
		CreateVertexAttribArrays(3);
		SetVertexAttribPointer(static_cast<uint32_t>(renderer::mesh::VertexAttribIndex::POSITION), 3, GL_FLOAT, false, sizeof(renderer::mesh::StaticMeshVertex), offsetof(renderer::mesh::StaticMeshVertex, position));
		SetVertexAttribPointer(static_cast<uint32_t>(renderer::mesh::VertexAttribIndex::NORMAL), 3, GL_FLOAT, false, sizeof(renderer::mesh::StaticMeshVertex), offsetof(renderer::mesh::StaticMeshVertex, normal));
		SetVertexAttribPointer(static_cast<uint32_t>(renderer::mesh::VertexAttribIndex::UV), 2, GL_FLOAT, false, sizeof(renderer::mesh::StaticMeshVertex), offsetof(renderer::mesh::StaticMeshVertex, uv));
		UnbindVBO(GL_ARRAY_BUFFER);
	}

	void OpenGLStaticMeshData::ClearCustomData()
	{
		GetDataUnsafe<renderer::mesh::StaticMesh>()->m_Vertices.clear();
	}

} // namespace gp1::renderer::apis::opengl::mesh
