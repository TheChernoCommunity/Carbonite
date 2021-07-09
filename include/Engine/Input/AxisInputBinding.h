//
//	Created by MarcasRealAccount on 8. Oct. 2020
//

#pragma once

#include "Engine/Input/IInputBinding.h"

#include <functional>
#include <unordered_map>

namespace gp1::input
{
	class InputHandler;

	struct AxisCallbackData
	{
	public:
		// Get the delta value of the axis.
		double GetDeltaValue() const;

	public:
		InputLocation      m_Location;      // The location of the axis binding.
		uint32_t           m_Axis;          // The axis index of the axis binding.
		double             m_Value;         // The value of the axis.
		double             m_PreviousValue; // The previous value of the axis.
		const std::string& m_Id;            // The id of the binding.
	};

	// Callback for AxisInputBinding
	typedef std::function<void(AxisCallbackData data)> AxisCallback;

	struct AxisInputBinding : public IInputBinding
	{
	public:
		AxisInputBinding(InputGroup* inputGroup, const std::string& id, uint32_t axis, InputLocation location, AxisCallback callback);

		virtual void HandleEvent(events::Event& event) override;

		// Binds the callback for this binding.
		void BindCallback(AxisCallback callback);

		friend InputHandler;

	private:
		// Get the previous axis value of a given axis, if not found the previous value is set to value.
		static double GetPreviousAxisValue(InputLocation location, uint32_t axis, double value = 0);
		// Set the previous axis value of a given axis.
		static void SetPreviousAxisValue(InputLocation location, uint32_t axis, double value);

	private:
		AxisCallback m_callback; // The callback to call if the corrent event was passed to HandleEvent()

	private:
		static std::unordered_map<uint64_t, double> s_PreviousAxisValues; // The previous axis values.
	};

	namespace axises
	{
		constexpr uint32_t mouseX      = 0;
		constexpr uint32_t mouseY      = 1;
		constexpr uint32_t mouseWheelX = 2;
		constexpr uint32_t mouseWheelY = 3;
		constexpr uint32_t mouseLast   = mouseWheelY;

		constexpr uint32_t gamepadLeftX        = 0;
		constexpr uint32_t gamepadLeftY        = 1;
		constexpr uint32_t gamepadRightX       = 2;
		constexpr uint32_t gamepadRightY       = 3;
		constexpr uint32_t gamepadLeftTrigger  = 4;
		constexpr uint32_t gamepadRightTrigger = 5;
		constexpr uint32_t gamepadLast         = gamepadRightTrigger;

	} // namespace axises

} // namespace gp1::input
