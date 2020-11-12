//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

#pragma once

#include "Engine/Utility/Core.h"
#include "Engine/Window/Window.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/Scene.h"

namespace gp1 {

	struct StaticMesh;

	class TestEntity : public Entity {
	public:
		TestEntity();
		~TestEntity();

		virtual Mesh* GetMesh() const override;

		virtual Material* GetMaterial() const override;

	private:
		StaticMesh* m_Mesh;
		Material* m_Material;
	};

	class Application {
	public:
		~Application();
		static Application* CreateApplication();

		void Run();
	protected:
		Application();

	private:
		static Application* s_Instance;
		Window m_Window{ { 1280, 720, 1280, 720, "Cherno Community Game Project 1", WindowMode::WINDOWED, false } };	// TODO: create init function for application using WindowData

		Scene m_Scene;
		TestEntity m_TestEntity;
		Camera m_Camera;

		Renderer* m_Renderer;
	};

} // namespace gp1
