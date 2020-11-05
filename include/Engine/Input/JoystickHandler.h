//	
//	Created by MarcasRealAccount on 5. Nov. 2020
//	

#pragma once

#include "Engine/Utility/Logger.h"

#include <stdint.h>

struct GLFWgamepadstate;

namespace gp1 {

	class Window;

	namespace input {

		struct JoystickGamepadInput {
			bool m_Connected = false;
			bool m_IsGamepad = false;
			unsigned char* m_Buttons = nullptr;
			int32_t m_NumButtons = 0;
		};

		class JoystickHandler {
		public:
			static void Init();
			static void DeInit();
			static void OnUpdate();

		private:
			static void JoystickCallback(int jid, int event);

		private:
			static JoystickGamepadInput* m_Joysticks;

			static Logger m_Logger;
		};

	} // namespace input

} // namespace gp1
