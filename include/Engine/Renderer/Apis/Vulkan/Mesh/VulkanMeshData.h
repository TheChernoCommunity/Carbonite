//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Mesh/Mesh.h"

namespace gp1 {

	class VulkanRenderer;

	struct VulkanMeshData : public MeshData {
	public:
		VulkanMeshData(Mesh* mesh);

		virtual RendererType GetRendererType() const override;

		virtual void CleanUp() override;

		friend VulkanRenderer;
	};

} // namespace gp1
