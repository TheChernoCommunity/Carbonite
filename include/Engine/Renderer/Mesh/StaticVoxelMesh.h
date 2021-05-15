//
//	Created by MarcasRealAccount on 30. Oct. 2020
//

#include "Engine/Renderer/Mesh/Mesh.h"

#include <glm.hpp>

namespace gp1::renderer::mesh
{
	struct StaticVoxelMeshVertex
	{
	public:
		glm::fvec3 position { 0.0f, 0.0f, 0.0f }; // The position of this vertex.
		glm::fvec3 normal { 0.0f, 0.0f, 0.0f };   // The normal of this vertex.
		glm::fvec2 uv { 0.0f, 0.0f };             // The uv of this vertex.
		uint32_t   SSBOIndex = 0;                 // The texture this vertex uses.
	};

	struct StaticVoxelMesh : public Mesh
	{
	public:
		StaticVoxelMesh();

	public:
		std::vector<StaticVoxelMeshVertex> m_Vertices; // This mesh's vertices.
	};

} // namespace gp1::renderer::mesh
