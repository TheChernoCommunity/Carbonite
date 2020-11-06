//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Renderer.h"

namespace gp1 {

	class VulkanRenderer : public Renderer {
	public:
		VulkanRenderer(Window* window);

		virtual RendererType GetRendererType() const override;

		virtual DebugRenderer* CreateDebugRenderer() override;

		virtual MeshData* CreateSkeletalMeshData(Mesh* mesh) override;
		virtual MeshData* CreateStaticMeshData(Mesh* mesh) override;
		virtual MeshData* CreateStaticVoxelMeshData(Mesh* mesh) override;

		virtual ShaderData* CreateShaderData(Shader* shader) override;

		virtual MaterialData* CreateMaterialData(Material* material) override;

	protected:
		virtual void InitRenderer() override;
		virtual void DeInitRenderer() override;
		virtual void RenderScene(Scene* scene, uint32_t width, uint32_t height) override;
	};
}
