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

		// Callback for ButtonInputBindings
		typedef std::function<void(uint32_t button)> ButtonCallback;

		struct ButtonInputBinding : public IInputBinding {
		public:
			ButtonInputBinding(std::string id, InputLocation location, ButtonInputType inputType, uint32_t button, ButtonCallback callback);

			virtual void HandleEvent(Event& event);

		private:
			ButtonInputType m_inputType;	// The type of event to listen for

			ButtonCallback m_callback;		// The callback to call if the corrent event was passed to HandleEvent()
		};

	} // namespace input

} // namespace gp1
