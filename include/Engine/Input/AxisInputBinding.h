//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#pragma once

#include "Engine/Input/IInputBinding.h"
#include <functional>

namespace gp1 {

	namespace input {

		struct AxisCallbackData {
			InputLocation m_Location;
			uint32_t m_Axis;
			double m_Value;
			const std::string& m_Id;
		};

		// Callback for AxisInputBinding
		typedef std::function<void(AxisCallbackData data)> AxisCallback;

		struct AxisInputBinding : public IInputBinding {
		public:
			AxisInputBinding(InputGroup* inputGroup, std::string id, uint32_t axis, InputLocation location, AxisCallback callback);

			virtual void HandleEvent(Event& event) override;

			// Binds the callback for this binding.
			void BindCallback(AxisCallback callback);

		private:
			AxisCallback m_callback;	// The callback to call if the corrent event was passed to HandleEvent()
		};

		namespace axises {
			constexpr uint32_t mouseX = 0;
			constexpr uint32_t mouseY = 1;
			constexpr uint32_t mouseWheelX = 2;
			constexpr uint32_t mouseWheelY = 3;
			constexpr uint32_t mouseLast = mouseWheelY;
		}

	} // namespace input

} // namespace gp1
