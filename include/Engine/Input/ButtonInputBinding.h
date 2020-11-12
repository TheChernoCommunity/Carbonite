//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#pragma once
#include "Engine/Input/IInputBinding.h"

#include <functional>

namespace gp1 {

	namespace input {

		// The type of event for ButtonInputBindings
		enum class ButtonInputType {
			PRESS,
			RELEASE,
			REPEAT
		};

		struct ButtonCallbackData {
			InputLocation m_Location;
			ButtonInputType m_InputType;
			uint32_t m_Button;
			const std::string& m_Id;
		};

		// Callback for ButtonInputBindings
		typedef std::function<void(ButtonCallbackData data)> ButtonCallback;

		struct ButtonInputBinding : public IInputBinding {
		public:
			ButtonInputBinding(InputGroup* inputGroup, const std::string& id, uint32_t button, ButtonInputType inputType, InputLocation location, ButtonCallback callback);

			virtual void HandleEvent(Event& event) override;

			// Binds the callback for this binding.
			void BindCallback(ButtonCallback callback);

		private:
			ButtonInputType m_inputType;	// The type of event to listen for

			ButtonCallback m_callback;		// The callback to call if the corrent event was passed to HandleEvent()
		};

		namespace buttons {
			constexpr uint32_t keySpace = 32;
			constexpr uint32_t keyApostrophe = 39;
			constexpr uint32_t keyComma = 44;
			constexpr uint32_t keyMinus = 45;
			constexpr uint32_t keyPeriod = 46;
			constexpr uint32_t keySlash = 47;
			constexpr uint32_t key0 = 48;
			constexpr uint32_t key1 = 49;
			constexpr uint32_t key2 = 50;
			constexpr uint32_t key3 = 51;
			constexpr uint32_t key4 = 52;
			constexpr uint32_t key5 = 53;
			constexpr uint32_t key6 = 54;
			constexpr uint32_t key7 = 55;
			constexpr uint32_t key8 = 56;
			constexpr uint32_t key9 = 57;
			constexpr uint32_t keySemicolon = 59;
			constexpr uint32_t keyEqual = 61;
			constexpr uint32_t keyA = 65;
			constexpr uint32_t keyB = 66;
			constexpr uint32_t keyC = 67;
			constexpr uint32_t keyD = 68;
			constexpr uint32_t keyE = 69;
			constexpr uint32_t keyF = 70;
			constexpr uint32_t keyG = 71;
			constexpr uint32_t keyH = 72;
			constexpr uint32_t keyI = 73;
			constexpr uint32_t keyJ = 74;
			constexpr uint32_t keyK = 75;
			constexpr uint32_t keyL = 76;
			constexpr uint32_t keyM = 77;
			constexpr uint32_t keyN = 78;
			constexpr uint32_t keyO = 79;
			constexpr uint32_t keyP = 80;
			constexpr uint32_t keyQ = 81;
			constexpr uint32_t keyR = 82;
			constexpr uint32_t keyS = 83;
			constexpr uint32_t keyT = 84;
			constexpr uint32_t keyU = 85;
			constexpr uint32_t keyV = 86;
			constexpr uint32_t keyW = 87;
			constexpr uint32_t keyX = 88;
			constexpr uint32_t keyY = 89;
			constexpr uint32_t keyZ = 90;
			constexpr uint32_t keyLeftBracket = 91;
			constexpr uint32_t keyBackslash = 92;
			constexpr uint32_t keyRightBracket = 93;
			constexpr uint32_t keyGraveAccent = 96;
			constexpr uint32_t keyWorld1 = 161;
			constexpr uint32_t keyWorld2 = 162;
			constexpr uint32_t keyEscape = 256;
			constexpr uint32_t keyEnter = 257;
			constexpr uint32_t keyTab = 258;
			constexpr uint32_t keyBackspace = 259;
			constexpr uint32_t keyInsert = 260;
			constexpr uint32_t keyDelete = 261;
			constexpr uint32_t keyRight = 262;
			constexpr uint32_t keyLeft = 263;
			constexpr uint32_t keyDown = 264;
			constexpr uint32_t keyUp = 265;
			constexpr uint32_t keyPageUp = 266;
			constexpr uint32_t keyPageDown = 267;
			constexpr uint32_t keyHome = 268;
			constexpr uint32_t keyEnd = 269;
			constexpr uint32_t keyCapsLock = 280;
			constexpr uint32_t keyScrollLock = 281;
			constexpr uint32_t keyNumLock = 282;
			constexpr uint32_t keyPrintScreen = 283;
			constexpr uint32_t keyPause = 284;
			constexpr uint32_t keyF1 = 290;
			constexpr uint32_t keyF2 = 291;
			constexpr uint32_t keyF3 = 292;
			constexpr uint32_t keyF4 = 293;
			constexpr uint32_t keyF5 = 294;
			constexpr uint32_t keyF6 = 295;
			constexpr uint32_t keyF7 = 296;
			constexpr uint32_t keyF8 = 297;
			constexpr uint32_t keyF9 = 298;
			constexpr uint32_t keyF10 = 299;
			constexpr uint32_t keyF11 = 300;
			constexpr uint32_t keyF12 = 301;
			constexpr uint32_t keyF13 = 302;
			constexpr uint32_t keyF14 = 303;
			constexpr uint32_t keyF15 = 304;
			constexpr uint32_t keyF16 = 305;
			constexpr uint32_t keyF17 = 306;
			constexpr uint32_t keyF18 = 307;
			constexpr uint32_t keyF19 = 308;
			constexpr uint32_t keyF20 = 309;
			constexpr uint32_t keyF21 = 310;
			constexpr uint32_t keyF22 = 311;
			constexpr uint32_t keyF23 = 312;
			constexpr uint32_t keyF24 = 313;
			constexpr uint32_t keyF25 = 314;
			constexpr uint32_t keyKp0 = 320;
			constexpr uint32_t keyKp1 = 321;
			constexpr uint32_t keyKp2 = 322;
			constexpr uint32_t keyKp3 = 323;
			constexpr uint32_t keyKp4 = 324;
			constexpr uint32_t keyKp5 = 325;
			constexpr uint32_t keyKp6 = 326;
			constexpr uint32_t keyKp7 = 327;
			constexpr uint32_t keyKp8 = 328;
			constexpr uint32_t keyKp9 = 329;
			constexpr uint32_t keyKpDecimal = 330;
			constexpr uint32_t keyKpDivide = 331;
			constexpr uint32_t keyKpMultiply = 332;
			constexpr uint32_t keyKpSubtract = 333;
			constexpr uint32_t keyKpAdd = 334;
			constexpr uint32_t keyKpEnter = 335;
			constexpr uint32_t keyKpEqual = 336;
			constexpr uint32_t keyLeftShift = 340;
			constexpr uint32_t keyLeftControl = 341;
			constexpr uint32_t keyLeftAlt = 342;
			constexpr uint32_t keyLeftSuper = 343;
			constexpr uint32_t keyRightShift = 344;
			constexpr uint32_t keyRightControl = 345;
			constexpr uint32_t keyRightAlt = 346;
			constexpr uint32_t keyRightSuper = 347;
			constexpr uint32_t keyMenu = 348;
			constexpr uint32_t keyLast = keyMenu;

			constexpr uint32_t mouse1 = 0;
			constexpr uint32_t mouse2 = 1;
			constexpr uint32_t mouse3 = 2;
			constexpr uint32_t mouse4 = 3;
			constexpr uint32_t mouse5 = 4;
			constexpr uint32_t mouse6 = 5;
			constexpr uint32_t mouse7 = 6;
			constexpr uint32_t mouse8 = 7;
			constexpr uint32_t mouseLast = mouse8;
			constexpr uint32_t mouseLeft = mouse1;
			constexpr uint32_t mouseRight = mouse2;
			constexpr uint32_t mouseMiddle = mouse3;
		}

	} // namespace input

} // namespace gp1
