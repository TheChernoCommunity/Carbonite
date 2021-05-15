//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#pragma once

#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanMeshData.h"
#include "Engine/Renderer/Mesh/SkeletalMesh.h"

namespace gp1::renderer::apis::vulkan::mesh
{
	struct VulkanSkeletalMeshData : public VulkanMeshData
	{
	public:
		VulkanSkeletalMeshData(renderer::mesh::SkeletalMesh* mesh);
	};

} // namespace gp1::renderer::apis::vulkan::mesh
