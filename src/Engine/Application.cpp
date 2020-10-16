//	
//	Created by MarcasRealAccount on 17. Oct. 2020
//	

#include "Engine/Application.h"
#include "Engine/Utility/Logger.h"

namespace gp1 {

	void Application::Start() {
		// Start engine modules here:
		Logger::Init();
		StartApp();
	}

	void Application::Stop() {
		StopApp();
		// Stop engine modules here:
		// I would recommend stopping them in the opposite order of starting.
		Logger::Deinit();
	}

} // namespace gp1
