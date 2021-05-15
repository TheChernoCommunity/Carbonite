//
//	Created by MarcasRealAccount on 8. Oct. 2020
//

#pragma once

#include "Engine/Input/InputHandler.h"
#include "Engine/Events/Event.h"
#include "Engine/Input/AxisInputBinding.h"
#include "Engine/Input/ButtonInputBinding.h"
#include "Engine/Utility/Config/ConfigManager.h"
#include "Engine/Window/Window.h"

#include "Engine/Events/GamepadEvent.h"
#include "Engine/Events/JoystickEvent.h"
#include "Engine/Events/MouseEvent.h"

namespace gp1::input
{
	extern EnumVector<std::pair<InputType, std::pair<InputLocation, uint32_t>>> InputNames;

	std::unordered_map<std::string, InputGroup*> InputHandler::s_inputGroups;

	InputGroup*     InputHandler::s_currentInputGroup = nullptr;
	window::Window* InputHandler::s_Window            = nullptr;

	void InputHandler::CleanUp()
	{
		for (auto group : InputHandler::s_inputGroups)
		{
			delete group.second;
		}
	}

	bool InputHandler::HandleEvent(events::Event& event)
	{
		if (InputHandler::s_currentInputGroup != nullptr)
		{
			if (InputHandler::s_Window->GetInputMode(GLFW_CURSOR) == GLFW_CURSOR_NORMAL && InputHandler::s_currentInputGroup->DoesCaptureMouse())
				InputHandler::s_Window->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else if (InputHandler::s_Window->GetInputMode(GLFW_CURSOR) == GLFW_CURSOR_DISABLED && !InputHandler::s_currentInputGroup->DoesCaptureMouse())
				InputHandler::s_Window->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			InputHandler::s_currentInputGroup->HandleEvent(event);
		}

		events::EventType type = event.GetType();
		switch (type)
		{
		case events::EventType::MOUSE_MOVED_EVENT:
		{
			events::mouse::MouseMovedEvent& movedEvent = *reinterpret_cast<events::mouse::MouseMovedEvent*>(&event);
			AxisInputBinding::SetPreviousAxisValue(InputLocation::MOUSE, axises::mouseX, movedEvent.GetX());
			AxisInputBinding::SetPreviousAxisValue(InputLocation::MOUSE, axises::mouseY, movedEvent.GetY());
			break;
		}
		case events::EventType::MOUSE_SCROLLED_EVENT:
		{
			events::mouse::MouseScrollEvent& scrollEvent = *reinterpret_cast<events::mouse::MouseScrollEvent*>(&event);
			AxisInputBinding::SetPreviousAxisValue(InputLocation::MOUSE, axises::mouseWheelX, scrollEvent.GetX());
			AxisInputBinding::SetPreviousAxisValue(InputLocation::MOUSE, axises::mouseWheelY, scrollEvent.GetY());
			break;
		}
		case events::EventType::GAMEPAD_AXIS_CHANGE_EVENT:
		{
			events::gamepad::GamepadAxisEvent& axisEvent = *reinterpret_cast<events::gamepad::GamepadAxisEvent*>(&event);
			AxisInputBinding::SetPreviousAxisValue(InputLocation::GAMEPAD, axisEvent.GetAxis(), axisEvent.GetValue());
			break;
		}
		case events::EventType::JOYSTICK_AXIS_CHANGE_EVENT:
		{
			events::joystick::JoystickAxisEvent& axisEvent = *reinterpret_cast<events::joystick::JoystickAxisEvent*>(&event);
			AxisInputBinding::SetPreviousAxisValue(InputLocation::JOYSTICK, axisEvent.GetAxis(), axisEvent.GetValue());
			break;
		}
		}

		return event.Handled;
	}

	void InputHandler::SetCurrentActiveInputGroup(const std::string& id)
	{
		SetCurrentActiveInputGroup(GetInputGroup(id));
	}

	void InputHandler::SetCurrentActiveInputGroup(InputGroup* inputGroup)
	{
		InputHandler::s_currentInputGroup = inputGroup;
	}

	InputGroup* InputHandler::CreateInputGroup(const std::string& id)
	{
		if (InputHandler::s_inputGroups.find(id) != InputHandler::s_inputGroups.end())
			return nullptr;

		InputGroup* inputGroup = new InputGroup(id);
		InputHandler::s_inputGroups.insert(std::pair(id, inputGroup));
		if (InputHandler::s_currentInputGroup == nullptr)
			InputHandler::s_currentInputGroup = inputGroup;
		return inputGroup;
	}

	InputGroup* InputHandler::GetInputGroup(const std::string& id)
	{
		auto itr = InputHandler::s_inputGroups.find(id);
		if (itr != InputHandler::s_inputGroups.end())
			return itr->second;
		return nullptr;
	}

	InputGroup* InputHandler::GetOrCreateInputGroup(const std::string& id)
	{
		InputGroup* inputGroup = GetInputGroup(id);
		if (inputGroup != nullptr)
			return inputGroup;
		return CreateInputGroup(id);
	}

	void InputHandler::RemoveInputGroupImpl(InputGroup* inputGroup)
	{
		auto itr = InputHandler::s_inputGroups.find(inputGroup->GetId());
		if (itr != InputHandler::s_inputGroups.end())
			InputHandler::s_inputGroups.erase(itr);
	}

	void InputHandler::RemoveInputGroup(InputGroup* inputGroup)
	{
		delete inputGroup;
	}

	void InputHandler::SetBindingConfigs(const std::string& id, InputType inputType, InputLocation location, uint32_t index)
	{
		config::ConfigFile* inputBindings = config::ConfigManager::GetConfigFile("InputBindings");
		inputBindings->SetConfigEnum(id, { inputType, { location, index } }, InputNames);
	}

	void InputHandler::GetBindingConfigs(const std::string& id, InputType inputType, InputLocation* location, uint32_t* index)
	{
		config::ConfigFile* inputBindings = config::ConfigManager::GetConfigFile("InputBindings");
		auto                input         = inputBindings->GetConfigEnum(id, { inputType, { *location, *index } }, InputNames);
		if (input.first != inputType)
			return;

		*location = input.second.first;
		*index    = input.second.second;
	}

	// PLEASE GOD NOOOO:
	EnumVector<std::pair<InputType, std::pair<InputLocation, uint32_t>>> InputNames = {
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keySpace } }, "Key.Space" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyApostrophe } }, "Key.Apostrophe" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyComma } }, "Key.Comma" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyMinus } }, "Key.Minus" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyPeriod } }, "Key.Period" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keySlash } }, "Key.Slash" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::key0 } }, "Key.0" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::key1 } }, "Key.1" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::key2 } }, "Key.2" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::key3 } }, "Key.3" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::key4 } }, "Key.4" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::key5 } }, "Key.5" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::key6 } }, "Key.6" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::key7 } }, "Key.7" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::key8 } }, "Key.8" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::key9 } }, "Key.9" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keySemicolon } }, "Key.Semicolon" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyEqual } }, "Key.Equal" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyA } }, "Key.A" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyB } }, "Key.B" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyC } }, "Key.C" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyD } }, "Key.D" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyE } }, "Key.E" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF } }, "Key.F" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyG } }, "Key.G" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyH } }, "Key.H" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyI } }, "Key.I" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyJ } }, "Key.J" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyK } }, "Key.K" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyL } }, "Key.L" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyM } }, "Key.M" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyN } }, "Key.N" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyO } }, "Key.O" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyP } }, "Key.P" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyQ } }, "Key.Q" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyR } }, "Key.R" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyS } }, "Key.S" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyT } }, "Key.T" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyU } }, "Key.U" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyV } }, "Key.V" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyW } }, "Key.W" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyX } }, "Key.X" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyY } }, "Key.Y" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyZ } }, "Key.Z" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyLeftBracket } }, "Key.LeftBracket" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyBackslash } }, "Key.Backslash" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyRightBracket } }, "Key.RightBracket" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyGraveAccent } }, "Key.GraveAccent" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyWorld1 } }, "Key.World1" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyWorld2 } }, "Key.World2" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyEscape } }, "Key.Escape" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyEnter } }, "Key.Enter" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyTab } }, "Key.Tab" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyBackspace } }, "Key.Backspace" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyInsert } }, "Key.Insert" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyDelete } }, "Key.Delete" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyRight } }, "Key.Right" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyLeft } }, "Key.Left" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyDown } }, "Key.Down" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyUp } }, "Key.Up" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyPageUp } }, "Key.PageUp" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyPageDown } }, "Key.PageDown" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyHome } }, "Key.Home" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyEnd } }, "Key.End" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyCapsLock } }, "Key.CapsLock" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyScrollLock } }, "Key.ScrollLock" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyNumLock } }, "Key.NumLock" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyPrintScreen } }, "Key.PrintScreen" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyPause } }, "Key.Pause" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF1 } }, "Key.F1" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF2 } }, "Key.F2" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF3 } }, "Key.F3" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF4 } }, "Key.F4" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF5 } }, "Key.F5" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF6 } }, "Key.F6" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF7 } }, "Key.F7" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF8 } }, "Key.F8" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF9 } }, "Key.F9" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF10 } }, "Key.F10" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF11 } }, "Key.F11" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF12 } }, "Key.F12" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF13 } }, "Key.F13" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF14 } }, "Key.F14" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF15 } }, "Key.F15" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF16 } }, "Key.F16" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF17 } }, "Key.F17" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF18 } }, "Key.F18" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF19 } }, "Key.F19" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF20 } }, "Key.F20" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF21 } }, "Key.F21" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF22 } }, "Key.F22" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF23 } }, "Key.F23" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF24 } }, "Key.F24" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyF25 } }, "Key.F25" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKp0 } }, "Key.Kp0" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKp1 } }, "Key.Kp1" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKp2 } }, "Key.Kp2" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKp3 } }, "Key.Kp3" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKp4 } }, "Key.Kp4" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKp5 } }, "Key.Kp5" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKp6 } }, "Key.Kp6" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKp7 } }, "Key.Kp7" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKp8 } }, "Key.Kp8" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKp9 } }, "Key.Kp9" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKpDecimal } }, "Key.KpDecimal" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKpDivide } }, "Key.KpDivide" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKpMultiply } }, "Key.KpMultiply" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKpSubtract } }, "Key.KpSubtract" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKpAdd } }, "Key.KpAdd" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKpEnter } }, "Key.KpEnter" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyKpEqual } }, "Key.KpEqual" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyLeftShift } }, "Key.LeftShift" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyLeftControl } }, "Key.LeftControl" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyLeftAlt } }, "Key.LeftAlt" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyLeftSuper } }, "Key.LeftSuper" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyRightShift } }, "Key.RightShift" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyRightControl } }, "Key.RightControl" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyRightAlt } }, "Key.RightAlt" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyRightSuper } }, "Key.RightSuper" },
		{ { InputType::BUTTON, { InputLocation::KEYBOARD, buttons::keyMenu } }, "Key.Menu" },
		{ { InputType::BUTTON, { InputLocation::MOUSE, buttons::mouseLeft } }, "Mouse.Left" },
		{ { InputType::BUTTON, { InputLocation::MOUSE, buttons::mouseRight } }, "Mouse.Right" },
		{ { InputType::BUTTON, { InputLocation::MOUSE, buttons::mouseMiddle } }, "Mouse.Middle" },
		{ { InputType::BUTTON, { InputLocation::MOUSE, buttons::mouse1 } }, "Mouse.1" },
		{ { InputType::BUTTON, { InputLocation::MOUSE, buttons::mouse2 } }, "Mouse.2" },
		{ { InputType::BUTTON, { InputLocation::MOUSE, buttons::mouse3 } }, "Mouse.3" },
		{ { InputType::BUTTON, { InputLocation::MOUSE, buttons::mouse4 } }, "Mouse.4" },
		{ { InputType::BUTTON, { InputLocation::MOUSE, buttons::mouse5 } }, "Mouse.5" },
		{ { InputType::BUTTON, { InputLocation::MOUSE, buttons::mouse6 } }, "Mouse.6" },
		{ { InputType::BUTTON, { InputLocation::MOUSE, buttons::mouse7 } }, "Mouse.7" },
		{ { InputType::BUTTON, { InputLocation::MOUSE, buttons::mouse8 } }, "Mouse.8" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadA } }, "Gamepad.A" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadB } }, "Gamepad.B" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadX } }, "Gamepad.X" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadY } }, "Gamepad.Y" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadLeftBumper } }, "Gamepad.LeftBumper" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadRightBumper } }, "Gamepad.RightBumper" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadBack } }, "Gamepad.Back" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadStart } }, "Gamepad.Start" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadGuide } }, "Gamepad.Guide" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadLeftThumb } }, "Gamepad.LeftThumb" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadRightThumb } }, "Gamepad.RightThumb" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadDPadUp } }, "Gamepad.DPadUp" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadDPadRight } }, "Gamepad.DPadRight" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadDPadDown } }, "Gamepad.DPadDown" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadDPadLeft } }, "Gamepad.DPadLeft" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadCross } }, "Gamepad.Cross" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadCircle } }, "Gamepad.Circle" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadSquare } }, "Gamepad.Square" },
		{ { InputType::BUTTON, { InputLocation::GAMEPAD, buttons::gamepadTriangle } }, "Gamepad.Triangle" },
		{ { InputType::AXIS, { InputLocation::MOUSE, axises::mouseX } }, "Mouse.X" },
		{ { InputType::AXIS, { InputLocation::MOUSE, axises::mouseY } }, "Mouse.Y" },
		{ { InputType::AXIS, { InputLocation::MOUSE, axises::mouseWheelX } }, "Mouse.WheelX" },
		{ { InputType::AXIS, { InputLocation::MOUSE, axises::mouseWheelY } }, "Mouse.WheelY" },
		{ { InputType::AXIS, { InputLocation::GAMEPAD, axises::gamepadLeftX } }, "Gamepad.LeftX" },
		{ { InputType::AXIS, { InputLocation::GAMEPAD, axises::gamepadLeftY } }, "Gamepad.LeftY" },
		{ { InputType::AXIS, { InputLocation::GAMEPAD, axises::gamepadRightX } }, "Gamepad.RightX" },
		{ { InputType::AXIS, { InputLocation::GAMEPAD, axises::gamepadRightY } }, "Gamepad.RightY" },
		{ { InputType::AXIS, { InputLocation::GAMEPAD, axises::gamepadLeftTrigger } }, "Gamepad.LeftTrigger" },
		{ { InputType::AXIS, { InputLocation::GAMEPAD, axises::gamepadRightTrigger } }, "Gamepad.RightTrigger" }
	};

} // namespace gp1::input
