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
	static std::unique_ptr<renderer::StaticMesh>     s_TestEntityMesh;
	static std::unique_ptr<renderer::Material>       s_TestEntityMaterial;
	static std::unique_ptr<renderer::TextureCubeMap> s_TestEntityTexture;
	static std::unique_ptr<renderer::ShaderProgram>  s_TestEntityShaderProgram;

	TestEntity::TestEntity()
	    : m_Mesh(s_TestEntityMesh.get()), m_Material(s_TestEntityMaterial.get())
	{
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
		Logger::Init();
		locale::LocaleManager::SetLocalization("en-us");

		config::ConfigFile*    applicationConfigs = config::ConfigManager::GetConfigFile("Application");
		config::ConfigSection* rendererSection    = applicationConfigs->GetOrCreateSection("Renderer");

		const std::string& selectedRenderer = rendererSection->GetConfig("Selected", "best");

		if (selectedRenderer.empty() || selectedRenderer == "best")
		{
			m_Renderer = renderer::Renderers::s_Renderers->GetBestRenderer();
			if (!m_Renderer)
				throw std::runtime_error("No valid renderer found!");
		}
		else
		{
			m_Renderer = renderer::Renderers::s_Renderers->GetRenderer(selectedRenderer);
			if (!m_Renderer)
				throw std::runtime_error(selectedRenderer + " is not compatible with this system!");
		}
#if false // TODO: Remove when audio library is cross platform
		audio::AudioCore::Init();
#endif
		m_Renderer->SetWindowHints();
		m_Window.Init();
		m_Window.SetTitle(m_Window.GetTitle() + " (" + renderer::Renderers::s_Renderers->GetName(m_Renderer.get()) + ")");
		input::InputHandler::s_Window = &m_Window;
		input::JoystickHandler::Init();
		m_Renderer->Init();

		m_Camera = std::make_unique<scene::Camera>();
		m_Scene.AttachEntity(m_Camera.get());

		//----
		// TODO(MarcasRealAccount): Please remove this when some actual rendering will take place, as this is just a test entity.
		s_TestEntityMesh          = renderer::StaticMesh::Create();
		s_TestEntityMaterial      = renderer::Material::Create();
		s_TestEntityTexture       = renderer::TextureCubeMap::Create();
		s_TestEntityShaderProgram = renderer::ShaderProgram::Create();

		s_TestEntityMesh->m_Vertices.push_back({ { -0.5f, 0.5f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } });
		s_TestEntityMesh->m_Vertices.push_back({ { 0.5f, 0.5f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } });
		s_TestEntityMesh->m_Vertices.push_back({ { 0.5f, -0.5f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } });
		s_TestEntityMesh->m_Vertices.push_back({ { -0.5f, -0.5f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } });

		s_TestEntityMesh->m_Indices.push_back(3);
		s_TestEntityMesh->m_Indices.push_back(1);
		s_TestEntityMesh->m_Indices.push_back(0);
		s_TestEntityMesh->m_Indices.push_back(3);
		s_TestEntityMesh->m_Indices.push_back(2);
		s_TestEntityMesh->m_Indices.push_back(1);

		s_TestEntityTexture->m_Width  = 2;
		s_TestEntityTexture->m_Height = 2;

		s_TestEntityTexture->m_Textures[renderer::TextureCubeMapFaceIndex::PositiveX] = { 255, 0, 0, 255, 0, 255, 0, 255, 0, 0, 255, 255, 255, 255, 255, 255 };
		s_TestEntityTexture->m_Textures[renderer::TextureCubeMapFaceIndex::PositiveY] = { 0, 255, 0, 255, 0, 0, 255, 255, 255, 0, 0, 255, 255, 255, 255, 255 };
		s_TestEntityTexture->m_Textures[renderer::TextureCubeMapFaceIndex::PositiveZ] = { 0, 0, 255, 255, 255, 0, 0, 255, 0, 255, 0, 255, 255, 255, 255, 255 };
		s_TestEntityTexture->m_Textures[renderer::TextureCubeMapFaceIndex::NegativeX] = { 127, 0, 0, 255, 0, 127, 0, 255, 0, 0, 127, 255, 127, 127, 127, 255 };
		s_TestEntityTexture->m_Textures[renderer::TextureCubeMapFaceIndex::NegativeY] = { 0, 127, 0, 255, 0, 0, 127, 255, 127, 0, 0, 255, 127, 127, 127, 255 };
		s_TestEntityTexture->m_Textures[renderer::TextureCubeMapFaceIndex::NegativeZ] = { 0, 0, 127, 255, 127, 0, 0, 255, 0, 127, 0, 255, 127, 127, 127, 255 };

		s_TestEntityTexture->m_Filter.m_Magnify  = renderer::ETextureFilter::Nearest;
		s_TestEntityTexture->m_Filter.m_Minimize = renderer::ETextureFilter::Nearest;

		const char* pVertexShaderCode   = R"(
#version 410 core

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inNormal;
layout(location = 2) in vec2 inUV;

layout(location = 0) out vec4 outNormal;
layout(location = 1) out vec2 outUV;
layout(location = 2) out vec3 outToCamera;

layout(std140) uniform gCamera {
	mat4 Camera_projectionViewMatrix;
	mat4 Camera_projectionMatrix;
	mat4 Camera_viewMatrix;
};

uniform Object {
	mat4 Object_transformationMatrix;
};

void main(void) {
	vec4 worldPosition = Object_transformationMatrix * inPosition;
	gl_Position = Camera_projectionViewMatrix * worldPosition;

	outNormal = Object_transformationMatrix * vec4(inNormal.xyz, 0.0);
	outUV = inUV;
	outToCamera = (inverse(Camera_viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
}
)";
		const char* pFragmentShaderCode = R"(
#version 410 core

layout(location = 0) in vec4 inNormal;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 inToCamera;

layout(location = 0) out vec4 outColor;

uniform Object {
	mat4 Object_transformationMatrix;
};

uniform samplerCube Object_tex;

void main(void) {
	outColor = texture(Object_tex, normalize(inToCamera));
}
)";

		renderer::Shader* vertexShader = s_TestEntityShaderProgram->AddShader(renderer::EShaderType::VertexShader);
		vertexShader->m_Data           = std::vector<uint8_t>(pVertexShaderCode, pVertexShaderCode + strlen(pVertexShaderCode));

		renderer::Shader* fragmentShader = s_TestEntityShaderProgram->AddShader(renderer::EShaderType::FragmentShader);
		fragmentShader->m_Data           = std::vector<uint8_t>(pFragmentShaderCode, pFragmentShaderCode + strlen(pFragmentShaderCode));

		s_TestEntityShaderProgram->AddUniformBuffer("Object");
		s_TestEntityShaderProgram->AddUniformBufferElement("Object", "transformationMatrix", renderer::EUniformType::FMat4);
		s_TestEntityShaderProgram->AddUniformBufferElement("Object", "tex", renderer::EUniformType::TextureCubeMap);

		s_TestEntityMaterial->SetShaderProgram(s_TestEntityShaderProgram.get());

		renderer::UniformTextureCubeMap* textureUniform = s_TestEntityMaterial->GetUniform<renderer::UniformTextureCubeMap>("Object", "tex");
		if (textureUniform)
			textureUniform->SetValue(s_TestEntityTexture.get());

		for (size_t i = 0; i < sizeof(m_TestEntities) / sizeof(*m_TestEntities); i++)
		{
			m_TestEntities[i] = std::make_unique<TestEntity>();
			m_Scene.AttachEntity(m_TestEntities[i].get());
		}
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

			m_Renderer->BeginFrame();
			m_Renderer->Render(m_Camera.get());
			m_Renderer->EndFrame();

			m_Window.OnUpdate();
			input::JoystickHandler::OnUpdate();
		}
	}

	Application::~Application()
	{
		//----
		// TODO(MarcasRealAccount): Please remove this when some actual rendering will take place, as this is just a test entity.
		s_TestEntityMesh.reset();
		s_TestEntityMaterial.reset();
		s_TestEntityTexture.reset();
		s_TestEntityShaderProgram.reset();
		//----

		m_Renderer->DeInit();
		m_Renderer.reset();
		m_Window.DeInit();
		input::JoystickHandler::DeInit();
		input::InputHandler::CleanUp();
#if false // TODO: Remove when audio library is cross platform
		audio::AudioCore::Shutdown();
#endif
		config::ConfigManager::SaveConfigs();
		Logger::DeInit();
	}

	Application* Application::GetInstance()
	{
		if (!Application::s_Instance) Application::s_Instance = CreateApplication();
		return Application::s_Instance;
	}

} // namespace gp1
