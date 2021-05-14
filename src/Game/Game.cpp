//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

//	Press the screen to move camera, and press Escape to go out.
//	Currently the camera only has a freecam controller using wasd and space, shift.
//	The freecam moves in screen space so w moves forward from the camera's perspective,
//	space moves up from the camera's perspective and right moves right from the camera's perspective.

#include "Game.h"

#include "Engine/Application.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Renderer/DebugRenderer.h"
#include "Engine/Utility/Locale/LocaleManager.h"

Application* Application::CreateApplication()
{
	return new Game();
}

Game::Game()
    : Application(), m_Logger("Game")
{
	// Load the sources
#if false // TODO: Remove when audio library is cross platform
	TestWAV  = audio::AudioSource::LoadFromFile("Sounds/TestWAV.wav");
	TestMP3  = audio::AudioSource::LoadFromFile("Sounds/TestMP3.mp3");
	TestFLAC = audio::AudioSource::LoadFromFile("Sounds/TestFLAC.flac");

	input::InputGroup*         audioInput = input::InputHandler::GetOrCreateInputGroup("audioInput");
	input::ButtonInputBinding* playWav    = audioInput->CreateButtonInputBinding("playWav", input::buttons::key1);
	input::ButtonInputBinding* playMp3    = audioInput->CreateButtonInputBinding("playMp3", input::buttons::key2);
	input::ButtonInputBinding* playFlac   = audioInput->CreateButtonInputBinding("playFlac", input::buttons::key3);
	playWav->BindCallback(std::bind(&Game::PlayWAVCallback, this, std::placeholders::_1));
	playMp3->BindCallback(std::bind(&Game::PlayMP3Callback, this, std::placeholders::_1));
	playFlac->BindCallback(std::bind(&Game::PlayFLACCallback, this, std::placeholders::_1));
#endif

	input::InputGroup*         inMenu    = input::InputHandler::GetOrCreateInputGroup("inMenu");
	input::ButtonInputBinding* closeMenu = inMenu->CreateButtonInputBinding("closeMenu", input::buttons::gamepadTriangle, input::ButtonInputType::PRESS, input::InputLocation::GAMEPAD);
	closeMenu->BindCallback(std::bind(&Game::CloseMenuCallback, this, std::placeholders::_1));
	m_Logger.LogDebug("CloseMenu keybind is: %u, on device: %u", closeMenu->GetIndex(), static_cast<uint32_t>(closeMenu->GetLocation()));

	// First get or create a new InputGroup with InputHandler::GetOrCreateInputGroup(name):
	input::InputGroup* onFoot = input::InputHandler::GetOrCreateInputGroup("onFoot");
	onFoot->SetCaptureMouse(true);
	// Second create either a ButtonInputBinding or AxisInputBinding with their respective create functions:
	input::ButtonInputBinding* openMenu = onFoot->CreateButtonInputBinding("openMenu", input::buttons::gamepadTriangle, input::ButtonInputType::PRESS, input::InputLocation::GAMEPAD);
	// Thirdly if you didn't set the binding in the create function you can do it like this:
	openMenu->BindCallback(std::bind(&Game::OpenMenuCallback, this, std::placeholders::_1));
	// The callback is void(gp1::input::ButtonCallbackData data) or void(gp1::input::AxisCallbackData data) depending on what type of binding.
	// For an example setup look at the callbacks in this class.
	m_Logger.LogDebug("OpenMenu keybind is: %u, on device: %u", openMenu->GetIndex(), static_cast<uint32_t>(openMenu->GetLocation()));

	input::AxisInputBinding* lookX = onFoot->CreateAxisInputBinding("lookX", input::axises::gamepadLeftTrigger, input::InputLocation::GAMEPAD);
	lookX->BindCallback(std::bind(&Game::LookCallback, this, std::placeholders::_1));
	m_Logger.LogDebug("LookX keybind is: %u, on device: %u", lookX->GetIndex(), static_cast<uint32_t>(lookX->GetLocation()));

	input::AxisInputBinding* lookY = onFoot->CreateAxisInputBinding("lookY", input::axises::gamepadRightTrigger, input::InputLocation::GAMEPAD);
	lookY->BindCallback(std::bind(&Game::LookCallback, this, std::placeholders::_1));
	m_Logger.LogDebug("LookY keybind is: %u, on device: %u", lookY->GetIndex(), static_cast<uint32_t>(lookY->GetLocation()));

	renderer::debug::DebugRenderer::DebugDrawPoint({ 0, 0, -2 }, 10.0f);
	renderer::debug::DebugRenderer::DebugDrawSphere({ 0, 0, -2 }, 1.0f, 10.0f);
	renderer::debug::DebugRenderer::DebugDrawLine({ -2, 1, -4 }, { 2, -1, -2 }, 10.0f);
	renderer::debug::DebugRenderer::DebugDrawBox({ 0, 0, -3 }, { 1, 1, 1 }, { 0, 0, 0 }, 10.0f);
	renderer::debug::DebugRenderer::DebugDrawABox({ 0, -2, -7 }, 10.0f);
	renderer::debug::DebugRenderer::DebugDrawABox({ -1, -2, -7 }, 10.0f);
	renderer::debug::DebugRenderer::DebugDrawABox({ -2, -2, -7 }, 10.0f);
}

void Game::LookCallback(input::AxisCallbackData data)
{
	if (data.m_Id == "lookX")
	{
		m_Logger.LogDebug("Moved mouse X to %f", data.m_Value);
	}
	else if (data.m_Id == "lookY")
	{
		m_Logger.LogDebug("Moved mouse Y to %f", data.m_Value);
	}
}

void Game::OpenMenuCallback(input::ButtonCallbackData data)
{
	m_Logger.LogDebug("Opened Menu %u", (uint32_t) data.m_InputType);
	input::InputHandler::SetCurrentActiveInputGroup("inMenu");
}

void Game::CloseMenuCallback(input::ButtonCallbackData data)
{
	m_Logger.LogDebug("Closed Menu %u", (uint32_t) data.m_InputType);
	input::InputHandler::SetCurrentActiveInputGroup("onFoot");
}

#if false // TODO: Remove when audio library is cross platform

void Game::PlayMP3Callback([[maybe_unused]] input::ButtonCallbackData data)
{
	// Play the source
	audio::Audio::Play(TestMP3);
}

void Game::PlayWAVCallback([[maybe_unused]] input::ButtonCallbackData data)
{
	// Play the source
	audio::Audio::Play(TestWAV);
}

void Game::PlayFLACCallback([[maybe_unused]] input::ButtonCallbackData data)
{
	// Play the source
	audio::Audio::Play(TestFLAC);
}

#endif