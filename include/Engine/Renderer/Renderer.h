//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace gp1 {

	class Window;
	struct MeshData;
	struct OpenGLMeshData;
	struct Mesh;
	class ShaderData;
	class Shader;
	class MaterialData;
	class OpenGLMaterialData;
	class Material;

	struct StaticMesh;

	enum class RendererType {
		OPENGL
	};

	class Renderer {
	public:
		Renderer(Window* window);
		virtual ~Renderer() = default;

		virtual RendererType GetRendererType() const = 0;

		// Initialize the renderer.
		virtual void Init() = 0;
		// De-initialize the renderer.
		virtual void DeInit() = 0;
		// Render a frame.
		virtual void Render() = 0;

		// Is the MeshData made for this renderer.
		virtual bool IsMeshDataUsable(MeshData* meshData) = 0;
		// Is the ShaderData made for this renderer.
		virtual bool IsShaderDataUsable(ShaderData* shaderData) = 0;
		// Is the MaterialData made for this renderer.
		virtual bool IsMaterialDataUsable(MaterialData* materialData) = 0;

		// Create a StaticMeshData for this renderer.
		virtual MeshData* CreateStaticMeshData(Mesh* mesh) = 0;
		// Create a SkeletalMeshData for this renderer.
		virtual MeshData* CreateSkeletalMeshData(Mesh* mesh) = 0;
		// Create a StaticVoxelMeshData for this renderer.
		virtual MeshData* CreateStaticVoxelMeshData(Mesh* mesh) = 0;

		// Create a ShaderData for this renderer.
		virtual ShaderData* CreateShaderData(Shader* shader) = 0;

		// Create a MaterialData for this renderer.
		virtual MaterialData* CreateMaterialData(Material* material) = 0;

	protected:
		GLFWwindow* GetNativeWindowHandle() const;

	public:
		// Get the appropriate renderer for the type.
		static Renderer* GetRenderer(RendererType rendererType, Window* window);

	protected:
		Window* m_Window;				// The window instance.

		StaticMesh* m_Mesh = nullptr;
		Material* m_Material = nullptr;
	};

	class OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer(Window* window);

		virtual RendererType GetRendererType() const override;

		virtual void Init() override;
		virtual void DeInit() override;
		virtual void Render() override;

		virtual bool IsMeshDataUsable(MeshData* meshData) override;
		virtual bool IsShaderDataUsable(ShaderData* shaderData) override;
		virtual bool IsMaterialDataUsable(MaterialData* materialData) override;

		virtual MeshData* CreateStaticMeshData(Mesh* mesh) override;
		virtual MeshData* CreateSkeletalMeshData(Mesh* mesh) override;
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
	};

} // namespace gp1
