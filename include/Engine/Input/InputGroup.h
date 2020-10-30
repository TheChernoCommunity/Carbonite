//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#pragma once

#include "Engine/Input/ButtonInputBinding.h"
#include "Engine/Input/AxisInputBinding.h"

#include <unordered_map>

namespace gp1 {

	class Event;

	namespace input {

		class InputHandler;

		class InputGroup {
		public:
			InputGroup(const std::string& id);
			~InputGroup();

			// Sets this input group as the current input group in the InputHandler this is created for.
			void attach();
			// Sets the current input group in the InputHandler this is created for to nullptr making it not handle anything.
			// You don't have to call this function before attaching another InputGroup.
			void detach();

			// Handles an event for this InputGroup.
			void HandleEvent(Event& event);

			// Gets an input binding from its id.
			// You can cast the return value to the correct binding type.
			IInputBinding* GetInputBinding(const std::string& id);

			// Removes the binding from this InputGroup, should not be called unless inside IInputBinding's destructor.
			void RemoveInputBindingImpl(IInputBinding* binding);
			// Deletes the pointer, causing it to call 'RemoveInputBindingImpl'
			void RemoveInputBinding(IInputBinding* binding);

			// Creates a ButtonInputBinding for this input group with the specified id.
			ButtonInputBinding* CreateButtonInputBinding(const std::string& id, uint32_t button, ButtonInputType inputType = ButtonInputType::PRESS, InputLocation location = InputLocation::KEYBOARD, ButtonCallback callback = nullptr);
			// Creates a AxisInputBinding for this input group with the specified id.
			AxisInputBinding* CreateAxisInputBinding(const std::string& id, uint32_t axis, InputLocation location = InputLocation::MOUSE, AxisCallback callback = nullptr);

			// Gets the id of this InputGroup
			const std::string& GetId() const;

		private:
			std::string m_id;													// The id of this InputGroup.
			std::unordered_map<std::string, IInputBinding*> m_inputBindings;	// The bindings this InputGroup handles.
		};

	} // namespace input

} // namespace gp1
