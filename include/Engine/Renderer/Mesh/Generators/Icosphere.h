//
//	Created by MarcasRealAccount on 16. May. 2021
//

#pragma once

#include "Engine/Renderer/Mesh/StaticMesh.h"

#include <memory>

namespace gp1::renderer::meshGenerators
{
	void GenerateIcosphere(std::shared_ptr<StaticMesh> mesh, uint32_t subdivisions);
} // namespace gp1::renderer::meshGenerators