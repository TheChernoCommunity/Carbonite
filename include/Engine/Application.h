//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

#pragma once

#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Utility/Core.h"
#include "Engine/Window/Window.h"

namespace gp1
{
	//----
	// TODO: Please remove this when some actual rendering will take place, as this is just a test entity.
	namespace renderer::mesh
	{
		struct StaticMesh;
	}

	class TestEntity : public scene::Entity
	{
	public:
		TestEntity();
		~TestEntity();

		virtual void Update(float deltaTime) override;

		virtual renderer::mesh::Mesh* GetMesh() const override;

		virtual renderer::shader::Material* GetMaterial() const override;

	private:
		renderer::mesh::StaticMesh* m_Mesh;
		renderer::shader::Material* m_Material;
	};
	//----

	class Application
	{
	public:
		~Application();

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
		// TODO: Please remove this when some actual rendering will take place, as this is just a test entity.
		TestEntity m_TestEntity;

		renderer::Renderer* m_Renderer; // The renderer of this application.

	private:
		static Application* s_Instance; // The static application instance.
	};

} // namespace gp1
