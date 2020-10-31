//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Mesh/StaticVoxelMesh.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanMeshData.h"

namespace gp1 {

	struct VulkanStaticVoxelMeshData : public VulkanMeshData {
	public:
		VulkanStaticVoxelMeshData(Mesh* mesh);
	};

} // namespace gp1
