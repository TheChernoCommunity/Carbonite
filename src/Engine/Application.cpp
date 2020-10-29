//
//	Created by MarcasRealAccount on 17. Oct. 2020
//
//	TODOs for the future:
//	- Maybe have m_Renderer.Render() get executed from a render thread as opposed to the window thread.
//

#include "Engine/Application.h"
#include "Engine/Utility/Logger.h"
#include "Engine/Utility/Config/ConfigManager.h"

namespace gp1 {

	Application::Application()
	{
		Logger::Init();
		m_Window.Init();
		m_Renderer.Init();
	}

	void Application::Run()
	{
		while (!m_Window.IsCloseRequested())
		{
			m_Renderer.Render();
			m_Window.OnUpdate();
		}
	}

	Application::~Application()
	{
		m_Renderer.DeInit();
		m_Window.DeInit();
		Logger::DeInit();
		config::ConfigManager::SaveConfigs();
	}

} // namespace gp1
