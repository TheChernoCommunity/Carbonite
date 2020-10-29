//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/Shader/Material.h"

namespace gp1 {

	class Window;

	class Renderer {
	public:
		Renderer(Window* window);

		// Initialize the renderer.
		void Init();
		// De-initialize the renderer.
		void DeInit();
		// Render a frame.
		void Render();

	private:
		// Render a mesh with a material.
		void RenderMeshWithMaterial(Mesh& mesh, Material& material);
		// Render a mesh.
		void RenderMesh(Mesh& mesh);
		// Set up data for rendering of a mesh.
		void PreRenderMesh(Mesh& mesh);
		// Render a mesh.
		void MidRenderMesh(Mesh& mesh);
		// Clean up data from rendering of a mesh.
		void PostRenderMesh(Mesh& mesh);

		// Set up data for the material.
		void PreMaterial(Material& material);
		// Clean up data for the material.
		void PostMaterial(Material& material);

	private:
		Window* m_Window;	// The window instance.

		Mesh m_Mesh;
		Material m_Material;
	};

} // namespace gp1
