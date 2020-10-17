//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

#pragma once

#include <Engine/Application.h>
#include <Engine/Utility/Logger.h>

namespace gp1 {

	class Game : public gp1::Application
	{
	public:
		Game();
	private:
		Logger m_Logger;
	};

} // namespace gp1
