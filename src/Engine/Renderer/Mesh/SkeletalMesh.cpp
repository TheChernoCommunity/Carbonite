//	
//	Created by MarcasRealAccount on 30. Oct. 2020
//	

#include "Engine/Renderer/Mesh/SkeletalMesh.h"

namespace gp1 {

	MeshData* SkeletalMesh::CreateCustomMeshData(Renderer* renderer) {
		return renderer->CreateSkeletalMeshData(this);
	}

} // namespace gp1
