//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#pragma once

#include "Engine/Renderer/Mesh/StaticMesh.h"

namespace gp1::renderer::meshGenerators
{
	// Generate an icosphere with the given subdivisions and put it inside the given mesh.
	void GenerateIcosphere(mesh::StaticMesh& mesh, uint32_t subdivisions);

} // namespace gp1::renderer::meshGenerators
