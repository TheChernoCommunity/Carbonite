//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Shader/Material.h"

namespace gp1 {

	class VulkanRenderer;

	class VulkanMaterialData : public MaterialData {
	public:
		VulkanMaterialData(Material* material);

		virtual void CleanUp() override;

		virtual RendererType GetRendererType() const override;

		friend VulkanRenderer;
	};

} // namespace gp1
