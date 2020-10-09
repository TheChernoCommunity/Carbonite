//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#pragma once

#include "Engine/Input/IInputBinding.h"
#include <functional>

namespace gp1 {

	namespace input {

		// Callback for AxisInputBinding
		typedef std::function<void(InputLocation location, uint32_t axis, double value)> AxisCallback;

#define SetAxisCallback(bindingPtr, functionPtr) bindingPtr->SetCallback(std::bind(functionPtr, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))

		struct AxisInputBinding : public IInputBinding {
		public:
			AxisInputBinding(InputGroup* inputGroup, std::string id, uint32_t axis, InputLocation location, AxisCallback callback);

			virtual void HandleEvent(Event& event) override;

			// Sets the callback for this binding.
			void SetCallback(AxisCallback callback);

		private:
			AxisCallback m_callback;	// The callback to call if the corrent event was passed to HandleEvent()
		};

	} // namespace input

} // namespace gp1
