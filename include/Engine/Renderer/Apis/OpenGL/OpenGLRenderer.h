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

		virtual void Init() override;
		virtual void DeInit() override;
		virtual void Render() override;

		virtual MeshData* CreateSkeletalMeshData(Mesh* mesh) override;
		virtual MeshData* CreateStaticMeshData(Mesh* mesh) override;
		virtual MeshData* CreateStaticVoxelMeshData(Mesh* mesh) override;

		virtual ShaderData* CreateShaderData(Shader* shader) override;

		virtual MaterialData* CreateMaterialData(Material* material) override;

	private:
		// Render a mesh with a material.
		void RenderMeshWithMaterial(OpenGLMeshData* mesh, OpenGLMaterialData* material);
		// Render a mesh.
		void RenderMesh(OpenGLMeshData* mesh);

		// Set up data for the material.
		void PreMaterial(OpenGLMaterialData* material);
		// Clean up data for the material.
		void PostMaterial(OpenGLMaterialData* material);

		StaticMesh* m_Mesh = nullptr;
		Material* m_Material = nullptr;
	};

} // namespace gp1
