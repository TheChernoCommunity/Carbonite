//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Utility/Logger.h"

namespace gp1 {

	class VulkanRenderer;

	class VulkanShaderData : public ShaderData {
	public:
		VulkanShaderData(Shader* shader);

		virtual RendererType GetRendererType() const override;
		virtual void CleanUp() override;

		friend VulkanRenderer;

	private:
		static Logger m_Logger;	// The shader's logger.
	};

} // namespace gp1
