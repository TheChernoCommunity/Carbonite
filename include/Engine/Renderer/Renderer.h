//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once

struct GLFWwindow;

namespace gp1 {

	class Window;
	struct Mesh;
	struct MeshData;
	class Material;
	class MaterialData;
	class Shader;
	class ShaderData;

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
		virtual void Init() = 0;
		// De-initialize the renderer.
		virtual void DeInit() = 0;
		// Render a frame.
		virtual void Render() = 0;

		// Is the MeshData made for this renderer.
		virtual bool IsMeshDataUsable(MeshData* meshData);
		// Is the ShaderData made for this renderer.
		virtual bool IsShaderDataUsable(ShaderData* shaderData);
		// Is the MaterialData made for this renderer.
		virtual bool IsMaterialDataUsable(MaterialData* materialData);

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
		GLFWwindow* GetNativeWindowHandle() const;

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
		Window* m_Window;				// The window instance.
	};

} // namespace gp1
