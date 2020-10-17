//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

#pragma once

#include <Engine/Application.h>
#include <Engine/Utility/Logger.h>
#include <Engine/Input/InputHandler.h>

namespace gp1 {

	class Game : public gp1::Application
	{
	public:
		Game();

	private:
		void LookCallback(input::AxisCallbackData data);

		void OpenMenuCallback(input::ButtonCallbackData data);
		void CloseMenuCallback(input::ButtonCallbackData data);

	private:
		Logger m_Logger;
	};

} // namespace gp1
