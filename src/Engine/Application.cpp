//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

#include "Engine/Application.h"
#include "Engine/Audio/AudioCore.h"
#include "Engine/Input/InputHandler.h"
#include "Engine/Input/JoystickHandler.h"
#include "Engine/Renderer/Renderers.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Utility/Config/ConfigManager.h"
#include "Engine/Utility/Locale/LocaleManager.h"
#include "Engine/Utility/Logger.h"

#include <chrono>
#include <cstring>
#include <stdexcept>

namespace gp1
{
	//----
	// TODO(MarcasRealAccount): Please remove this when some actual rendering will take place, as this is just a test entity.
	TestEntity::TestEntity()
	    : m_Mesh(Application::GetInstance()->GetRenderer()->CreateStaticMesh()), m_Material(Application::GetInstance()->GetRenderer()->CreateMaterial())
	{
		m_Mesh->m_Vertices.push_back({ { -0.5f, 0.5f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } });
		m_Mesh->m_Vertices.push_back({ { 0.5f, 0.5f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } });
		m_Mesh->m_Vertices.push_back({ { 0.5f, -0.5f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } });
		m_Mesh->m_Vertices.push_back({ { -0.5f, -0.5f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } });

		m_Mesh->m_Indices.push_back(3);
		m_Mesh->m_Indices.push_back(1);
		m_Mesh->m_Indices.push_back(0);
		m_Mesh->m_Indices.push_back(3);
		m_Mesh->m_Indices.push_back(2);
		m_Mesh->m_Indices.push_back(1);

		std::shared_ptr<renderer::ShaderProgram> shaderProgram = Application::GetInstance()->GetRenderer()->CreateShaderProgram();

		const char* pVertexShaderCode   = R"(
#version 430 core

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inNormal;
layout(location = 2) in vec2 inUV;

layout(location = 0) out vec2 passUV;

layout(std140, binding = 0) uniform Camera {
	mat4 Camera_projectionViewMatrix;
};

uniform Object {
	mat4 Object_transformationMatrix;
};

void main(void) {
	gl_Position = Camera_projectionViewMatrix * Object_transformationMatrix * inPosition;
	passUV = inUV;
}
)";
		const char* pFragmentShaderCode = R"(
#version 430 core

layout(location = 0) in vec2 inUV;

layout(location = 0) out vec4 outColor;

void main(void) {
	outColor = vec4(inUV, 0.0, 1.0);
}
)";

		renderer::Shader* vertexShader = shaderProgram->GetShader(renderer::EShaderType::VertexShader);
		vertexShader->m_Data           = std::vector<uint8_t>(pVertexShaderCode, pVertexShaderCode + strlen(pVertexShaderCode));

		renderer::Shader* fragmentShader = shaderProgram->GetShader(renderer::EShaderType::FragmentShader);
		fragmentShader->m_Data           = std::vector<uint8_t>(pFragmentShaderCode, pFragmentShaderCode + strlen(pFragmentShaderCode));

		shaderProgram->AddUniformBuffer("Object");
		shaderProgram->AddUniformBufferElement("Object", "transformationMatrix", renderer::EUniformType::FMat4);

		m_Material->SetShaderProgram(shaderProgram);

		m_Position.z = -5.0f;
	}

	void TestEntity::Update(float deltaTime)
	{
		m_Rotation.y += deltaTime * 10.0f;
	}
	//----

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
		locale::LocaleManager::SetLocalization("en-us");
		Logger::Init();
		m_Renderer = renderer::Renderers::s_Renderers->GetBestRenderer();
		if (!m_Renderer)
			throw std::runtime_error("No valid renderer found!");
#if false // TODO: Remove when audio library is cross platform
		audio::AudioCore::Init();
#endif
		m_Renderer->SetWindowHints();
		m_Window.Init();
		input::InputHandler::s_Window = &m_Window;
		input::JoystickHandler::Init();
		m_Renderer->Init();

		m_Scene.AttachEntity(&m_Camera);

		//----
		// TODO(MarcasRealAccount): Please remove this when some actual rendering will take place, as this is just a test entity.
		m_TestEntity = std::make_shared<TestEntity>();
		m_Scene.AttachEntity(m_TestEntity.get());
		//----
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

			m_Scene.Update(deltaTime);

			m_Renderer->Render(&m_Camera);

			m_Window.OnUpdate();
			input::JoystickHandler::OnUpdate();
		}
	}

	Application::~Application()
	{
		m_Renderer->DeInit();
		m_Renderer.reset();
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
