//	
//	Created by MarcasRealAccount on 5. Nov. 2020
//	

#include "Engine/Input/JoystickHandler.h"
#include "Engine/Window/Window.h"
#include "Engine/Events/EventHandler.h"
#include "Engine/Events/JoystickEvent.h"
#include "Engine/Events/GamepadEvent.h"

namespace gp1 {

	namespace input {

		JoystickGamepadInput* JoystickHandler::m_Joysticks = nullptr;

		Logger JoystickHandler::m_Logger("JoystickHandler");

		void JoystickHandler::Init() {
			JoystickHandler::m_Joysticks = new JoystickGamepadInput[GLFW_JOYSTICK_LAST];

			for (uint32_t i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_LAST; i++) {
				JoystickHandler::m_Joysticks[i] = JoystickGamepadInput();

				if (glfwJoystickIsGamepad(i)) {
					JoystickHandler::m_Joysticks[i].m_Connected = true;
					JoystickHandler::m_Joysticks[i].m_IsGamepad = true;
					JoystickHandler::m_Joysticks[i].m_NumButtons = GLFW_GAMEPAD_BUTTON_LAST + 1;
					JoystickHandler::m_Joysticks[i].m_Buttons = new unsigned char[JoystickHandler::m_Joysticks[i].m_NumButtons];
					memset(JoystickHandler::m_Joysticks[i].m_Buttons, 0, JoystickHandler::m_Joysticks[i].m_NumButtons);
					JoystickHandler::m_Logger.LogDebug("Gamepad connected");
				} else if (glfwJoystickPresent(i)) {
					JoystickHandler::m_Joysticks[i].m_Connected = true;
					JoystickHandler::m_Joysticks[i].m_IsGamepad = false;
					const unsigned char* buttons = glfwGetJoystickButtons(i, &JoystickHandler::m_Joysticks[i].m_NumButtons);
					_CRT_UNUSED(buttons);
					JoystickHandler::m_Joysticks[i].m_Buttons = new unsigned char[JoystickHandler::m_Joysticks[i].m_NumButtons];
					memset(JoystickHandler::m_Joysticks[i].m_Buttons, 0, JoystickHandler::m_Joysticks[i].m_NumButtons);
					JoystickHandler::m_Logger.LogDebug("Joystick connected");
				}
			}

			glfwSetJoystickCallback(JoystickHandler::JoystickCallback);
		}

		void JoystickHandler::DeInit() {
			for (uint32_t i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_LAST; i++) {
				if (JoystickHandler::m_Joysticks[i].m_Buttons)
					delete[] JoystickHandler::m_Joysticks[i].m_Buttons;
			}
			delete[] JoystickHandler::m_Joysticks;
		}

		void JoystickHandler::OnUpdate() {
			for (uint32_t i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_LAST; i++) {
				JoystickGamepadInput& input = JoystickHandler::m_Joysticks[i];
				if (input.m_Connected) {
					if (input.m_IsGamepad) {
						GLFWgamepadstate state;
						glfwGetGamepadState(i, &state);

						if (!input.m_Connected)
							continue;

						for (uint32_t axis = 0; axis <= GLFW_GAMEPAD_AXIS_LAST; axis++) {
							GamepadAxisEvent event(i, axis, state.axes[axis]);
							EventHandler::PushEvent(event);
						}

						for (uint32_t button = 0; button <= GLFW_GAMEPAD_BUTTON_LAST; button++) {
							if (state.buttons[button] != input.m_Buttons[button]) {
								if (state.buttons[button] == GLFW_PRESS) {
									GamepadButtonPressedEvent event(i, button);
									EventHandler::PushEvent(event);
								} else if (state.buttons[button] == GLFW_RELEASE) {
									GamepadButtonReleasedEvent event(i, button);
									EventHandler::PushEvent(event);
								}
							}
						}

						memcpy(input.m_Buttons, state.buttons, input.m_NumButtons);
					} else {
						int32_t numAxises;
						const float* axises = glfwGetJoystickAxes(i, &numAxises);
						int32_t numButtons;
						const unsigned char* buttons = glfwGetJoystickButtons(i, &numButtons);

						if (!input.m_Connected)
							continue;

						for (int32_t axis = 0; axis < numAxises; axis++) {
							JoystickAxisEvent event(i, axis, axises[axis]);
							EventHandler::PushEvent(event);
						}

						for (int32_t button = 0; button < input.m_NumButtons; button++) {
							if (buttons[button] != input.m_Buttons[button]) {
								if (buttons[button] == GLFW_PRESS) {
									JoystickButtonPressedEvent event(i, button);
									EventHandler::PushEvent(event);
								} else if (buttons[button] == GLFW_RELEASE) {
									JoystickButtonReleasedEvent event(i, button);
									EventHandler::PushEvent(event);
								}
							}
						}

						memcpy(input.m_Buttons, buttons, input.m_NumButtons);
					}
				}
			}
		}

		void JoystickHandler::JoystickCallback(int jid, int event) {
			JoystickGamepadInput& input = JoystickHandler::m_Joysticks[jid];
			if (event == GLFW_CONNECTED) {
				input.m_Connected = true;
				if (glfwJoystickIsGamepad(jid)) {
					input.m_IsGamepad = true;
					input.m_NumButtons = GLFW_GAMEPAD_BUTTON_LAST + 1;
					input.m_Buttons = new unsigned char[input.m_NumButtons];
					memset(input.m_Buttons, 0, input.m_NumButtons);
					JoystickHandler::m_Logger.LogDebug("Gamepad connected");
				} else if (glfwJoystickPresent(jid)) {
					input.m_IsGamepad = false;
					const unsigned char* buttons = glfwGetJoystickButtons(jid, &input.m_NumButtons);
					_CRT_UNUSED(buttons);
					input.m_Buttons = new unsigned char[input.m_NumButtons];
					memset(input.m_Buttons, 0, input.m_NumButtons);
					JoystickHandler::m_Logger.LogDebug("Joystick connected");
				}
			} else if (event == GLFW_DISCONNECTED) {
				if (input.m_IsGamepad)
					JoystickHandler::m_Logger.LogDebug("Gamepad disconnected");
				else
					JoystickHandler::m_Logger.LogDebug("Joystick disconnected");
				if (input.m_Buttons)
					delete[] input.m_Buttons;
				input.m_Connected = false;
				input.m_IsGamepad = false;
				input.m_Buttons = nullptr;
				input.m_NumButtons = 0;
			}
		}

	} // namespace input

} // namespace gp1
