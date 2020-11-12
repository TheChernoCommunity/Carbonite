//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once

#include "Engine/Scene/Camera.h"

struct GLFWwindow;

namespace gp1 {

	class Window;
	class DebugRenderer;
	struct Mesh;
	struct MeshData;
	class Material;
	class MaterialData;
	class Shader;
	class ShaderData;
	class Scene;

	enum class RendererType {
		OPENGL,
		VULKAN
	};

	class Renderer {
	public:
		Renderer(Window* window);
		virtual ~Renderer() = default;

		virtual RendererType GetRendererType() const = 0;

		// Initialize the renderer.
		void Init();
		// De-initialize the renderer.
		void DeInit();
		// Render a scene.
		void Render(Scene* scene);

		// Is the DebugRenderer made for this renderer.
		virtual bool IsDebugRendererUsable(DebugRenderer* debugRenderer);

		// Is the MeshData made for this renderer.
		virtual bool IsMeshDataUsable(MeshData* meshData);
		// Is the ShaderData made for this renderer.
		virtual bool IsShaderDataUsable(ShaderData* shaderData);
		// Is the MaterialData made for this renderer.
		virtual bool IsMaterialDataUsable(MaterialData* materialData);

		// Create a DebugRenderer for this renderer.
		virtual DebugRenderer* CreateDebugRenderer() = 0;

		// Create a SkeletalMeshData for this renderer.
		virtual MeshData* CreateSkeletalMeshData(Mesh* mesh) = 0;
		// Create a StaticMeshData for this renderer.
		virtual MeshData* CreateStaticMeshData(Mesh* mesh) = 0;
		// Create a StaticVoxelMeshData for this renderer.
		virtual MeshData* CreateStaticVoxelMeshData(Mesh* mesh) = 0;

		// Create a ShaderData for this renderer.
		virtual ShaderData* CreateShaderData(Shader* shader) = 0;

		// Create a MaterialData for this renderer.
		virtual MaterialData* CreateMaterialData(Material* material) = 0;

	protected:
		// Initialize the renderer.
		virtual void InitRenderer() = 0;
		// De-initialize the renderer.
		virtual void DeInitRenderer() = 0;
		// Render a scene.
		virtual void RenderScene(Scene* scene, uint32_t width, uint32_t height) = 0;

		GLFWwindow* GetNativeWindowHandle() const;

		DebugRenderer* GetDebugRenderer();

		template <typename T>
		T* GetMeshData(Mesh* mesh) {
			return reinterpret_cast<T*>(mesh->GetMeshData(this));
		}

		template <typename T>
		T* GetMaterialData(Material* material) {
			return reinterpret_cast<T*>(material->GetMaterialData(this));
		}

		template <typename T>
		T* GetShaderData(MaterialData* materialData) {
			return GetShaderData<T>(materialData->GetMaterial<Material>()->GetShader());
		}

		template <typename T>
		T* GetShaderData(Shader* shader) {
			return reinterpret_cast<T*>(shader->GetShaderData(this));
		}

	public:
		// Get the appropriate renderer for the type.
		static Renderer* GetRenderer(RendererType rendererType, Window* window);

	protected:
		Window* m_Window;	// The window instance.
	};

} // namespace gp1
