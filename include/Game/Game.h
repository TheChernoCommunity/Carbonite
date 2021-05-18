//
//	Created by MarcasRealAccount on 17. Oct. 2020
//

#pragma once

#include <Engine/Application.h>
#include <Engine/Utility/Logger.h>
#include <Engine/Utility/CVarSystem.h>
#include <Engine/Input/InputHandler.h>
#include <Engine/Audio/Audio.h>

namespace gp1 {

	class Game : public gp1::Application
	{
	public:
		Game();

	private:
		void LookCallback(input::AxisCallbackData data);

		void OpenMenuCallback(input::ButtonCallbackData data);
		void CloseMenuCallback(input::ButtonCallbackData data);

		void PlayMP3Callback(input::ButtonCallbackData data);
		void PlayWAVCallback(input::ButtonCallbackData data);
		void PlayFLACCallback(input::ButtonCallbackData data);
	private:
		Logger m_Logger;
		CVarSystem m_CVarSystem;

		// Audio Data
		AudioSource TestMP3;
		AudioSource TestWAV;
		AudioSource TestFLAC;
	};

} // namespace gp1
