//	
//	Created by MarcasRealAccount on 17. Oct. 2020
//	

#include "Game/Game.h"

namespace gp1 {

	Game::Game()
		: m_Logger("Game") {}

	void Game::StartApp() {
		m_Logger.LogTrace("Started Game");
	}

	void Game::StopApp() {
		m_Logger.LogTrace("Stopped Game");
	}

} // namespace gp1
