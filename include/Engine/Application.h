//	
//	Created by MarcasRealAccount on 17. Oct. 2020
//	

#pragma once

#include "Engine/Utility/Core.h"

namespace gp1 {

	class Application {
	public:
		void Start();
		void Stop();

	private:
		virtual void StartApp() = 0;
		virtual void StopApp() = 0;
	};

} // namespace gp1
