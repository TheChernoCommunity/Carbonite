//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

#pragma once

#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Utility/Core.h"
#include "Engine/Window/Window.h"

#include <memory>

namespace gp1
{
	class Application
	{
	public:
		~Application();

		inline window::Window& GetWindow()
		{
			return m_Window;
		}

		inline const window::Window& GetWindow() const
		{
			return m_Window;
		}

		inline std::shared_ptr<renderer::Renderer> GetRenderer() const
		{
			return m_Renderer;
		}

		// Run the application.
		void Run();

	protected:
		Application();

	public:
		// Create the application.
		static Application* CreateApplication();

		// Get the application instance.
		static Application* GetInstance();

	private:
		// TODO: create init function for application using WindowData
		window::Window m_Window { { 1280, 720, 1280, 720, "Cherno Community Game Project 1", window::WindowMode::WINDOWED, false } }; // The window of this application.

		scene::Scene  m_Scene; // The scene to use for this application.
		scene::Camera m_Camera;

		std::shared_ptr<renderer::Renderer> m_Renderer;

	private:
		static Application* s_Instance; // The static application instance.
	};

} // namespace gp1
