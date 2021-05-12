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
#include <stdexcept>

namespace gp1
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		locale::LocaleManager::SetLocalization("en-us");
		Logger::Init();
		m_Renderer = renderer::Renderers::s_Renderers->GetBestRenderer(&m_Window);
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

		this->m_Scene.AttachEntity(&this->m_Camera);
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
