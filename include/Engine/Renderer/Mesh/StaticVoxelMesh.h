//	
//	Created by MarcasRealAccount on 30. Oct. 2020
//	

#include "Engine/Renderer/Mesh/Mesh.h"

#include <glm.hpp>

namespace gp1 {

	struct StaticVoxelMeshVertex {
		glm::fvec3 position{ 0.0f, 0.0f, 0.0f };
		glm::fvec3 normal{ 0.0f, 0.0f, 0.0f };
		glm::fvec2 uv{ 0.0f, 0.0f };
		uint32_t SSBOIndex = 0;
	};

	struct StaticVoxelMesh : public Mesh {
	private:
		virtual MeshData* CreateCustomMeshData(Renderer* renderer) override;

	public:
		std::vector<StaticVoxelMeshVertex> m_Vertices;	// This mesh's vertices.
	};

} // namespace gp1
