//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#pragma once

#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanMeshData.h"
#include "Engine/Renderer/Mesh/StaticMesh.h"

namespace gp1::renderer::apis::vulkan::mesh
{
	struct VulkanStaticMeshData : public VulkanMeshData
	{
	public:
		VulkanStaticMeshData(renderer::mesh::StaticMesh* mesh);
	};

} // namespace gp1::renderer::apis::vulkan::mesh
