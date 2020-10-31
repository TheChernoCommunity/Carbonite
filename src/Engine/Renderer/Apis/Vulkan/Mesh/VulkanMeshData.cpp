//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#include "Engine/Renderer/Apis/Vulkan/Mesh/VulkanMeshData.h"

namespace gp1 {

	VulkanMeshData::VulkanMeshData(Mesh* mesh)
		: MeshData(mesh) {}

	RendererType VulkanMeshData::GetRendererType() const {
		return RendererType::VULKAN;
	}

	void VulkanMeshData::CleanUp() {}

} // namespace gp1
