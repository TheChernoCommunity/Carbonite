//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

#pragma once

#include "Engine/Utility/Core.h"

namespace gp1 {

	class Application {
	public:
		~Application();
		static Application* CreateApplication();

		void Run();
	protected:
		Application();

	private:
		static Application* s_Instance;
	};


} // namespace gp1
