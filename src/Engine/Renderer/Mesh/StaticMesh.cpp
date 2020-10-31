//	
//	Created by MarcasRealAccount on 30. Oct. 2020
//	

#include "Engine/Renderer/Mesh/StaticMesh.h"

namespace gp1 {

	MeshData* StaticMesh::CreateCustomMeshData(Renderer* renderer) {
		return renderer->CreateStaticMeshData(this);
	}

} // namespace gp1
