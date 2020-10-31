//	
//	Created by MarcasRealAccount on 30. Oct. 2020
//	

#include "Engine/Renderer/Mesh/Mesh.h"

namespace gp1 {

	struct StaticVoxelMeshVertex {
		struct { float x, y, z; } position{ 0.0f, 0.0f, 0.0f };
		struct { float x, y, z; } normal{ 0.0f, 0.0f, 0.0f };
		struct { float x, y; } uv{ 0.0f, 0.0f };
		uint32_t SSBOIndex = 0;
	};

	struct StaticVoxelMesh : public Mesh {
	private:
		virtual MeshData* CreateCustomMeshData(Renderer* renderer) override;

	public:
		std::vector<StaticVoxelMeshVertex> m_Vertices;	// This mesh's vertices.
	};

} // namespace gp1
