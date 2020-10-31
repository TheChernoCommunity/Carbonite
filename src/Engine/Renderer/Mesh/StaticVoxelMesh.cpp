//	
//	Created by MarcasRealAccount on 30. Oct. 2020
//	

#include "Engine/Renderer/Mesh/StaticVoxelMesh.h"

namespace gp1 {

	MeshData* StaticVoxelMesh::CreateCustomMeshData(Renderer* renderer) {
		return renderer->CreateStaticVoxelMeshData(this);
	}

} // namespace gp1
