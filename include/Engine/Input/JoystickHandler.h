//
//	Created by MarcasRealAccount on 5. Nov. 2020
//

#pragma once

#include "Engine/Utility/Logger.h"

#include <stdint.h>

struct GLFWgamepadstate;

namespace gp1
{
	namespace input
	{
		struct JoystickGamepadInput
		{
		public:
			bool           m_Connected  = false;   // Is this joystick connected.
			bool           m_IsGamepad  = false;   // Is this joystick a gamepad.
			unsigned char* m_Buttons    = nullptr; // The buttons this joystick has.
			int32_t        m_NumButtons = 0;       // The number of buttons this joystick has.
		};

		class JoystickHandler
		{
		public:
			// Initialize the JoystickHandler.
			static void Init();
			// DeInitialize the JoystickHandler.
			static void DeInit();
			// Update the JoystickHandler.
			static void OnUpdate();

		private:
			// The joystick callback.
			static void JoystickCallback(int jid, int event);

		private:
			static JoystickGamepadInput* s_Joysticks; // The joysticks this JoystickHandler holds.
			static Logger                s_Logger;    // The logger that this JoystickHandler uses to report errors.
		};

	} // namespace input

} // namespace gp1
