//
//	Created by MarcasRealAccount on 30. Oct. 2020
//

#include "Engine/Renderer/Mesh/Mesh.h"

#include <glm.hpp>

namespace gp1::renderer::mesh
{
	struct SkeletalMeshVertex
	{
	public:
		glm::fvec3 position { 0.0f, 0.0f, 0.0f };     // The position of this vertex.
		glm::fvec3 normal { 0.0f, 0.0f, 0.0f };       // The normal of this vertex.
		glm::fvec2 uv { 0.0f, 0.0f };                 // The uv of this vertex.
		glm::uvec3 jointIndices { 0, 0, 0 };          // The joints that this vertex is affected by.
		glm::fvec3 jointWeights { 0.0f, 0.0f, 0.0f }; // The weights of the joints.
	};

	struct SkeletalMesh : public Mesh
	{
	public:
		SkeletalMesh();

	public:
		std::vector<SkeletalMeshVertex> m_Vertices; // This mesh's vertices.
	};

} // namespace gp1::renderer::mesh
