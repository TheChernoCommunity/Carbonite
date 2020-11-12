//	
//	Created by MarcasRealAccount on 31. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Renderer.h"

namespace gp1 {

	struct StaticMesh;
	struct OpenGLMeshData;
	class OpenGLMaterialData;

	class OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer(Window* window);

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

	private:
		// Render an entity.
		void RenderEntity(Entity* entity);
		// Render a mesh with a material.
		void RenderMeshWithMaterial(OpenGLMeshData* mesh, OpenGLMaterialData* material);
		// Render a mesh.
		void RenderMesh(OpenGLMeshData* mesh);

		// Set up data for the material.
		void PreMaterial(OpenGLMaterialData* material);
		// Clean up data for the material.
		void PostMaterial(OpenGLMaterialData* material);
	};

} // namespace gp1
