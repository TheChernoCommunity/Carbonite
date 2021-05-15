//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanSkeletalMeshData.h"

namespace gp1::renderer::apis::vulkan::mesh
{
	VulkanSkeletalMeshData::VulkanSkeletalMeshData(renderer::mesh::SkeletalMesh* mesh)
	    : VulkanMeshData(mesh) {}

} // namespace gp1::renderer::apis::vulkan::mesh
