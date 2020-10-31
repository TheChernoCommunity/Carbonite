//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Mesh/SkeletalMesh.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanMeshData.h"

namespace gp1 {

	struct VulkanSkeletalMeshData : public VulkanMeshData {
	public:
		VulkanSkeletalMeshData(Mesh* mesh);
	};

} // namespace gp1
