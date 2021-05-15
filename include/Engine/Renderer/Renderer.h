//
//	Created by MarcasRealAccount on 29. Oct. 2020
//

#pragma once

#include "Engine/Renderer/RendererType.h"
#include "Engine/Scene/Camera.h"

struct GLFWwindow;

namespace gp1
{
	namespace window
	{
		class Window;
	}

	namespace scene
	{
		class Scene;
	}

	namespace renderer
	{
		namespace debug
		{
			class DebugRenderer;
		}

		struct RendererData;
		struct Data;

		class Renderer
		{
		public:
			Renderer(window::Window* window);
			virtual ~Renderer() = default;

			// Get the type of renderer.
			virtual RendererType GetRendererType() const = 0;

			// Initialize the renderer.
			void Init();
			// De-initialize the renderer.
			void DeInit();
			// Render a scene.
			void Render(scene::Scene* scene);

			// Is the DebugRenderer made for this renderer.
			virtual bool IsDebugRendererUsable(debug::DebugRenderer* debugRenderer);
			// Create a DebugRenderer for this renderer.
			virtual debug::DebugRenderer* CreateDebugRenderer() = 0;

			// Is the renderer data usable for this renderer.
			virtual bool IsRendererDataUsable(RendererData* rendererData);
			// Create renderer data that is associated with the given data.
			virtual RendererData* CreateRendererData(Data* data) = 0;

		protected:
			// Initialize the renderer.
			virtual void InitRenderer() = 0;
			// De-initialize the renderer.
			virtual void DeInitRenderer() = 0;
			// Render a scene.
			virtual void RenderScene(scene::Scene* scene, uint32_t width, uint32_t height) = 0;

			// Get the native window handle, this renderer renders to.
			GLFWwindow* GetNativeWindowHandle() const;

			// Get the debug renderer this renderer uses.
			debug::DebugRenderer* GetDebugRenderer();

		public:
			// Get the appropriate renderer for the given type.
			static Renderer* GetRenderer(RendererType rendererType, window::Window* window);

		protected:
			window::Window* m_Window; // The window instance.
		};

	} // namespace renderer

} // namespace gp1
