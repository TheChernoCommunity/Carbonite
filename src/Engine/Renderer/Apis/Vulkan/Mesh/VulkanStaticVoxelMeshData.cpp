//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanStaticVoxelMeshData.h"

namespace gp1::renderer::apis::vulkan::mesh
{
	VulkanStaticVoxelMeshData::VulkanStaticVoxelMeshData(renderer::mesh::StaticVoxelMesh* mesh)
	    : VulkanMeshData(mesh) {}

} // namespace gp1::renderer::apis::vulkan::mesh
