//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

#include "Game/Game.h"
#include "Engine/Application.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"

namespace gp1 {

	Application* Application::CreateApplication() {
		return new Game();
	}

	Game::Game()
		: m_Logger("Game"), Application() {

		// First get or create a new InputGroup with InputHandler::GetOrCreateInputGroup(name):
		input::InputGroup* onFoot = input::InputHandler::GetOrCreateInputGroup("onFoot");
		// Second create either a ButtonInputBinding or AxisInputBinding with their respective create functions:
		input::ButtonInputBinding* openMenu = onFoot->CreateButtonInputBinding("openMenu", 256);
		// Thirdly if you didn't set the binding in the create function you can do it like this:
		openMenu->BindCallback(std::bind(&Game::OpenMenuCallback, this, std::placeholders::_1));
		// The callback is void(gp1::input::ButtonCallbackData data) or void(gp1::input::AxisCallbackData data) depending on what type of binding.
		// For an example setup look at the callbacks in this class.
		m_Logger.LogDebug("OpenMenu keybind is: %u, on device: %u", openMenu->GetIndex(), (uint32_t)openMenu->GetLocation());

		input::AxisInputBinding* lookX = onFoot->CreateAxisInputBinding("lookX", 0);
		lookX->BindCallback(std::bind(&Game::LookCallback, this, std::placeholders::_1));
		m_Logger.LogDebug("LookX keybind is: %u, on device: %u", lookX->GetIndex(), (uint32_t)lookX->GetLocation());

		input::AxisInputBinding* lookY = onFoot->CreateAxisInputBinding("lookY", 1);
		lookY->BindCallback(std::bind(&Game::LookCallback, this, std::placeholders::_1));
		m_Logger.LogDebug("LookY keybind is: %u, on device: %u", lookY->GetIndex(), (uint32_t)lookY->GetLocation());

		input::InputGroup* inMenu = input::InputHandler::GetOrCreateInputGroup("inMenu");
		input::ButtonInputBinding* closeMenu = inMenu->CreateButtonInputBinding("closeMenu", 256);
		closeMenu->BindCallback(std::bind(&Game::CloseMenuCallback, this, std::placeholders::_1));
		m_Logger.LogDebug("CloseMenu keybind is: %u, on device: %u", closeMenu->GetIndex(), (uint32_t)closeMenu->GetLocation());

		input::InputHandler::HandleEvent(KeyPressedEvent(256, false));
		input::InputHandler::HandleEvent(MouseMovedEvent(100, 50));
		input::InputHandler::HandleEvent(KeyPressedEvent(256, false));
		input::InputHandler::HandleEvent(MouseMovedEvent(50, 100));
	}

	void Game::LookCallback(input::AxisCallbackData data) {
		switch (data.m_Axis) {
		case 0:
			m_Logger.LogDebug("Moved mouse X to %f", data.m_Value);
			break;
		case 1:
			m_Logger.LogDebug("Moved mouse Y to %f", data.m_Value);
			break;
		}
	}

	void Game::OpenMenuCallback(input::ButtonCallbackData data) {
		m_Logger.LogDebug("Opened Menu");
		input::InputHandler::SetCurrentActiveInputGroup("inMenu");
	}

	void Game::CloseMenuCallback(input::ButtonCallbackData data) {
		m_Logger.LogDebug("Closed Menu");
		input::InputHandler::SetCurrentActiveInputGroup("onFoot");
	}

} // namespace gp1
