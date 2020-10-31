//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#include "Engine/Renderer/Apis/Vulkan/Shader/VulkanShaderData.h"

namespace gp1 {

	Logger VulkanShaderData::m_Logger("Vulkan Shader");

	VulkanShaderData::VulkanShaderData(Shader* shader)
		: ShaderData(shader) {}

	RendererType VulkanShaderData::GetRendererType() const {
		return RendererType::OPENGL;
	}

	void VulkanShaderData::CleanUp() {
	}

} // namespace gp1
