//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#pragma once

#include <string>
#include <stdint.h>

namespace gp1 {

	class Event;

	namespace input {

		// The device where an input can be gotten from.
		enum class InputLocation : uint32_t {
			KEYBOARD,
			MOUSE,
			LAST = MOUSE,
			UNKNOWN
		};

		// The type of input.
		enum class InputType : uint32_t {
			BUTTON,
			AXIS
		};

		struct IInputBinding {
		public:
			IInputBinding(std::string id, InputType type, InputLocation location, uint32_t index);

			/// <summary>
			/// Handles an event from the Event System.
			/// </summary>
			/// <param name="event">A reference to an event to try to handle.</param>
			virtual void HandleEvent(Event& event) = 0;

			/// <summary>
			/// Sets the input location and index of this Input Binding.
			/// And then sets it in the input configuration.
			/// </summary>
			/// <param name="location">The input location for the binding i.e. InputLocation::KEYBOARD for a key and InputLocation::MOUSE for a mouse button.</param>
			/// <param name="index">The actual index for the key, button, axis et cetera.</param>
			void SetBinding(InputLocation location, uint32_t index);

			/// <summary>
			/// Sets the input location of this Input Binding.
			/// </summary>
			/// <param name="location">The input location for the binding i.e. InputLocation::KEYBOARD for a key and InputLocation::MOUSE for a mouse button.</param>
			void SetInputLocation(InputLocation location);

			/// <summary>
			/// Sets the index of this Input Binding.
			/// </summary>
			/// <param name="index">The actual index for the key, button, axis et cetera.</param>
			void SetIndex(uint32_t index);

			// Gets the config id of this Input Binding.
			const std::string& GetId() const;
			// Gets the type of input this Input Binding is.
			const InputType& GetType() const;
			// Gets the input location of this Input Binding.
			const InputLocation& GetLocation() const;
			// Gets the index of this input Binding.
			const uint32_t& GetIndex() const;

		private:
			std::string m_id;			// Id to use for storing & loading the input from configuration file.
			InputType m_type;			// The type of input to expect i.e. is it a button or an axis.
			InputLocation m_location;	// The location of the input i.e. is this input binding for a Keyboard or a Mouse
			uint32_t m_index;			// The index like keycode or buttoncode? or the axis index like 0 for Mouse X and 1 for Mouse Y.
		};

	} // namespace input

} // namespace gp1
