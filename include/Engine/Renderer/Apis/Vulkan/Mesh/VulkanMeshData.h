//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#pragma once

#include "Engine/Renderer/Apis/Vulkan/VulkanRendererData.h"
#include "Engine/Renderer/Mesh/Mesh.h"

namespace gp1::renderer::apis::vulkan::mesh
{
	struct VulkanMeshData : public VulkanRendererData
	{
	public:
		template <typename T>
		VulkanMeshData(T* data)
		    : VulkanRendererData(data)
		{
		}

		virtual void CleanUp() override;

		friend VulkanRenderer;
	};

} // namespace gp1::renderer::apis::vulkan::mesh
