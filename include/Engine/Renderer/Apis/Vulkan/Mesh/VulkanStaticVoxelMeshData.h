//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#pragma once

#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanMeshData.h"
#include "Engine/Renderer/Mesh/StaticVoxelMesh.h"

namespace gp1::renderer::apis::vulkan::mesh
{
	struct VulkanStaticVoxelMeshData : public VulkanMeshData
	{
	public:
		VulkanStaticVoxelMeshData(renderer::mesh::StaticVoxelMesh* mesh);
	};

} // namespace gp1::renderer::apis::vulkan::mesh
