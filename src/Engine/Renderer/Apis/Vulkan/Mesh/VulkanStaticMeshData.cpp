//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanStaticMeshData.h"

namespace gp1::renderer::apis::vulkan::mesh
{
	VulkanStaticMeshData::VulkanStaticMeshData(renderer::mesh::StaticMesh* mesh)
	    : VulkanMeshData(mesh) {}

} // namespace gp1::renderer::apis::vulkan::mesh
