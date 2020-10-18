//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

#include "Engine/Application.h"
#include "Engine/Utility/Logger.h"
#include "Engine/Configuration/ConfigurationManager.h"

namespace gp1 {

	Application::Application()
	{
		Logger::Init();
	}

	void Application::Run()
	{

	}

	Application::~Application()
	{
		configuration::ConfigurationManager::SaveConfigurations();
		Logger::DeInit();
	}

} // namespace gp1
