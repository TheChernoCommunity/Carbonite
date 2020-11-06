//
//	Created by MarcasRealAccount on 17. Oct. 2020
//
//	TODOs for the future:
//	- Maybe have m_Renderer.Render() get executed from a render thread as opposed to the window thread.
//

#include "Engine/Application.h"
#include "Engine/Utility/Logger.h"
#include "Engine/Utility/Config/ConfigManager.h"
#include "Engine/Input/InputHandler.h"
#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Scene/Entity.h"

#include "Engine/Renderer/Mesh/StaticMesh.h"
#include "Engine/Renderer/Shader/Material.h"

namespace gp1 {

	TestEntity::TestEntity()
		: m_Mesh(new StaticMesh()), m_Material(new Material()) {
		m_Mesh->m_Vertices.push_back({ { -0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } });
		m_Mesh->m_Vertices.push_back({ { 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } });
		m_Mesh->m_Vertices.push_back({ { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } });
		m_Mesh->m_Vertices.push_back({ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } });

		m_Mesh->m_Indices.push_back(3);
		m_Mesh->m_Indices.push_back(1);
		m_Mesh->m_Indices.push_back(0);
		m_Mesh->m_Indices.push_back(3);
		m_Mesh->m_Indices.push_back(2);
		m_Mesh->m_Indices.push_back(1);

		m_Material->SetShader(Shader::GetShader("shader"));

		this->m_Position.z = -5.0f;
	}

	TestEntity::~TestEntity() {
		delete this->m_Mesh;
		delete this->m_Material;
	}

	Mesh* TestEntity::GetMesh() const {
		return this->m_Mesh;
	}

	Material* TestEntity::GetMaterial() const {
		return this->m_Material;
	}

	Application::Application() {
		Logger::Init();
		m_Window.Init();
		m_Renderer = Renderer::GetRenderer(RendererType::OPENGL, &m_Window);
		m_Renderer->Init();

		//this->m_Scene.AttachEntity(&this->m_TestEntity);
		this->m_Scene.AttachEntity(&this->m_Camera);
		this->m_Camera.SetAsMainCamera();
	}

	void Application::Run() {
		while (!m_Window.IsCloseRequested()) {
			m_Renderer->Render(&this->m_Scene);
			m_Window.OnUpdate();
		}
	}

	Application::~Application() {
		this->m_Renderer->DeInit();
		delete m_Renderer;
		Shader::CleanUpShaders();
		m_Window.DeInit();
		input::InputHandler::CleanUp();
		config::ConfigManager::SaveConfigs();
		Logger::DeInit();
	}

} // namespace gp1
