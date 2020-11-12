//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#include "Engine/Renderer/Apis/Vulkan/Shader/VulkanMaterialData.h"
#include "Engine/Renderer/Shader/Shader.h"

namespace gp1 {

	VulkanMaterialData::VulkanMaterialData(Material* material)
		: MaterialData(material) {}

	void VulkanMaterialData::CleanUp() {}

	RendererType VulkanMaterialData::GetRendererType() const {
		return RendererType::OPENGL;
	}

} // namespace gp1
