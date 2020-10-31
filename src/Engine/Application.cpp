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

namespace gp1 {

	Application::Application() {
		Logger::Init();
		m_Window.Init();
		m_Renderer = Renderer::GetRenderer(RendererType::VULKAN, &m_Window);
		m_Renderer->Init();
	}

	void Application::Run() {
		while (!m_Window.IsCloseRequested()) {
			m_Renderer->Render();
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
