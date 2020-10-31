//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Mesh/StaticMesh.h"
#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanMeshData.h"

namespace gp1 {

	struct VulkanStaticMeshData : public VulkanMeshData {
	public:
		VulkanStaticMeshData(Mesh* mesh);
	};

} // namespace gp1
