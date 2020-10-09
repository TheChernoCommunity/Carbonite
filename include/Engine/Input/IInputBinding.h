//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#pragma once

#include <string>
#include <stdint.h>

namespace gp1 {

	class Event;

	namespace input {

		class InputGroup;

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
			IInputBinding(InputGroup* inputGroup, std::string id, InputType type, uint32_t index, InputLocation location);
			// This destructor is virtual to stop the warning "delete of an abstract class 'IInputBinding' that has a non-virtual destructor results in undefined behaviour. Though there is no need to implement this destructor in subclasses
			virtual ~IInputBinding();

			// Handles an event form tht Event System.
			virtual void HandleEvent(Event& event) = 0;

			// Sets the input location and index of this Input Binding.  And then sets it in the input configuration.
			void SetBinding(InputLocation location, uint32_t index);
			// Sets the input location of this Input Binding.
			void SetInputLocation(InputLocation location);
			// Sets the index of this Input Binding.
			void SetIndex(uint32_t index);

			// Gets the InputGroup this is part of.
			InputGroup* GetInputGroup() const;

			// Gets the config id of this Input Binding.
			const std::string& GetId() const;
			// Gets the type of input this Input Binding is.
			const InputType& GetType() const;
			// Gets the input location of this Input Binding.
			const InputLocation& GetLocation() const;
			// Gets the index of this input Binding.
			const uint32_t& GetIndex() const;

		private:
			InputGroup* m_inputGroup;	// The input group this binding is part of.

			std::string m_id;			// Id to use for storing & loading the input from configuration file.
			InputType m_type;			// The type of input to expect i.e. is it a button or an axis.
			InputLocation m_location;	// The location of the input i.e. is this input binding for a Keyboard or a Mouse
			uint32_t m_index;			// The index like keycode or buttoncode? or the axis index like 0 for Mouse X and 1 for Mouse Y.
		};

	} // namespace input

} // namespace gp1
