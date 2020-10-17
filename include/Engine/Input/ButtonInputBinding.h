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
		};

		// Callback for ButtonInputBindings
		typedef std::function<void(ButtonCallbackData data)> ButtonCallback;

		struct ButtonInputBinding : public IInputBinding {
		public:
			ButtonInputBinding(InputGroup* inputGroup, std::string id, uint32_t button, ButtonInputType inputType, InputLocation location, ButtonCallback callback);

			virtual void HandleEvent(Event& event) override;

			// Binds the callback for this binding.
			void BindCallback(ButtonCallback callback);

		private:
			ButtonInputType m_inputType;	// The type of event to listen for

			ButtonCallback m_callback;		// The callback to call if the corrent event was passed to HandleEvent()
		};

	} // namespace input

} // namespace gp1
