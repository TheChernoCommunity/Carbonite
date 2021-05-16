//
//	Created by MarcasRealAccount on 17. Oct. 2020
//
//	TODOs for the future:
//	- Maybe have m_Renderer.Render() get executed from a render thread as opposed to the window thread.
//

#include "Engine/Application.h"
#include "Engine/Input/InputHandler.h"
#include "Engine/Input/JoystickHandler.h"
#include "Engine/Renderer/Shader/Shader.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Utility/Config/ConfigManager.h"
#include "Engine/Utility/Logger.h"

#include "Engine/Renderer/Mesh/StaticMesh.h"
#include "Engine/Renderer/Shader/Material.h"
#include "Engine/Renderer/Texture/Loaders/TextureLoaders.h"
#include "Engine/Renderer/Texture/TextureCubeMap.h"

#include "Engine/Audio/AudioCore.h"

#include "Engine/Utility/Locale/LocaleManager.h"
#include <chrono>

namespace gp1
{
	Application* Application::s_Instance = nullptr;

	//----
	// TODO: Please remove this when some actual rendering will take place, as this is just a test entity.
	TestEntity::TestEntity()
	    : m_Mesh(new renderer::mesh::StaticMesh()), m_Material(new renderer::shader::Material())
	{
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

		m_Material->SetShader(renderer::shader::Shader::GetShader("shaderMeshDefault"));
		renderer::shader::Uniform<renderer::texture::TextureCubeMap*>* tex = m_Material->GetUniform<renderer::texture::TextureCubeMap*>("tex");
		if (tex)
		{
			renderer::texture::TextureCubeMap* t = new renderer::texture::TextureCubeMap();
			t->m_Width                           = 1;
			t->m_Height                          = 1;
			{
				renderer::texture::Texture2D& te = t->m_Textures[renderer::texture::TextureCubeMapFaceIndex::POSITIVE_X];
				te.m_Data.push_back(255);
				te.m_Data.push_back(0);
				te.m_Data.push_back(0);
				te.m_Data.push_back(255);
			}
			{
				renderer::texture::Texture2D& te = t->m_Textures[renderer::texture::TextureCubeMapFaceIndex::POSITIVE_Y];
				te.m_Data.push_back(0);
				te.m_Data.push_back(255);
				te.m_Data.push_back(0);
				te.m_Data.push_back(255);
			}
			{
				renderer::texture::Texture2D& te = t->m_Textures[renderer::texture::TextureCubeMapFaceIndex::POSITIVE_Z];
				te.m_Data.push_back(0);
				te.m_Data.push_back(0);
				te.m_Data.push_back(255);
				te.m_Data.push_back(255);
			}
			{
				renderer::texture::Texture2D& te = t->m_Textures[renderer::texture::TextureCubeMapFaceIndex::NEGATIVE_X];
				te.m_Data.push_back(127);
				te.m_Data.push_back(0);
				te.m_Data.push_back(0);
				te.m_Data.push_back(255);
			}
			{
				renderer::texture::Texture2D& te = t->m_Textures[renderer::texture::TextureCubeMapFaceIndex::NEGATIVE_Y];
				te.m_Data.push_back(0);
				te.m_Data.push_back(127);
				te.m_Data.push_back(0);
				te.m_Data.push_back(255);
			}
			{
				renderer::texture::Texture2D& te = t->m_Textures[renderer::texture::TextureCubeMapFaceIndex::NEGATIVE_Z];
				te.m_Data.push_back(0);
				te.m_Data.push_back(0);
				te.m_Data.push_back(127);
				te.m_Data.push_back(255);
			}
			tex->m_Value = t;
		}

		this->m_Position.z = -5.0f;
	}

	TestEntity::~TestEntity()
	{
		delete this->m_Mesh;
		delete this->m_Material;
	}

	void TestEntity::Update(float deltaTime)
	{
		renderer::shader::Uniform<float>* time = this->m_Material->GetUniform<float>("time");
		if (time) time->m_Value = static_cast<float>(glfwGetTime());

		this->m_Rotation.y += deltaTime * 10.0f;
	}

	renderer::mesh::Mesh* TestEntity::GetMesh() const
	{
		return this->m_Mesh;
	}

	renderer::shader::Material* TestEntity::GetMaterial() const
	{
		return this->m_Material;
	}
	//----

	Application::Application()
	{
		locale::LocaleManager::SetLocalization("en-us");
		Logger::Init();
#if false // TODO: Remove when audio library is cross platform
		audio::AudioCore::Init();
#endif
		m_Window.Init();
		input::InputHandler::s_Window = &m_Window;
		input::JoystickHandler::Init();
		m_Renderer = renderer::Renderer::GetRenderer(renderer::RendererType::OPENGL, &m_Window);
		m_Renderer->Init();

		//----
		// TODO: Please remove this when some actual rendering will take place, as this is just a test entity.
		this->m_Scene.AttachEntity(&this->m_TestEntity);
		//----
		this->m_Scene.AttachEntity(&this->m_Camera);
		this->m_Camera.SetAsMainCamera();
	}

	void Application::Run()
	{
		auto  lastFrame = std::chrono::high_resolution_clock::now();
		float deltaTime = 0.0f;
		while (!m_Window.IsCloseRequested())
		{
			auto curFrame = std::chrono::high_resolution_clock::now();
			deltaTime     = (curFrame - lastFrame).count() * 1e-9F;
			lastFrame     = curFrame;

			for (scene::Entity* entity : this->m_Scene.GetEntities())
				entity->Update(deltaTime);

			m_Renderer->Render(&this->m_Scene);
			m_Window.OnUpdate();
			input::JoystickHandler::OnUpdate();
		}
	}

	Application::~Application()
	{
		this->m_Renderer->DeInit();
		delete m_Renderer;
		renderer::shader::Shader::CleanUpShaders();
		m_Window.DeInit();
		input::JoystickHandler::DeInit();
		input::InputHandler::CleanUp();
		config::ConfigManager::SaveConfigs();
#if false // TODO: Remove when audio library is cross platform
		audio::AudioCore::Shutdown();
#endif
		Logger::DeInit();
	}

	Application* Application::GetInstance()
	{
		if (!Application::s_Instance) Application::s_Instance = CreateApplication();
		return Application::s_Instance;
	}

} // namespace gp1
