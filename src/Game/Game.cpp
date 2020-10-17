//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

#include "Game/Game.h"
#include "Engine/Application.h"

namespace gp1 {

	Application* Application::CreateApplication()
	{
		return new Game();
	}

	Game::Game()
		: m_Logger("Game"), Application()
	{

	}


} // namespace gp1
