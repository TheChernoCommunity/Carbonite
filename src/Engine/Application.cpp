//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

#include "Engine/Application.h"
#include "Engine/Utility/Logger.h"
<<<<<<< HEAD
#include "Engine/Configuration/ConfigurationManager.h"
=======
>>>>>>> maths
#include "Engine/Utility/Maths/Matrix.h"

namespace gp1 {

	Application::Application()
	{
		Logger::Init();
		m_Window.Init();
	}

	void Application::Run()
	{
		while (!m_Window.IsCloseRequested())
		{
			m_Window.OnUpdate();
		}
	}

	Application::~Application()
	{
		configuration::ConfigurationManager::SaveConfigurations();
		m_Window.DeInit();
		Logger::DeInit();
	}

} // namespace gp1
