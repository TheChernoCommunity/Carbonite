//	
//	Created by MarcasRealAccount on 8. Oct. 2020
//	

#pragma once

#include "Engine/Input/InputGroup.h"

#include <unordered_map>

namespace gp1 {

	class Event;

	namespace input {

		class InputHandler {
		public:
			// Handles events for Input Bindings
			void HandleEvent(Event& event);

			// Sets the current active input group by using an InputGroups id.
			void SetCurrentActiveInputGroup(std::string id);
			// Sets the current active input group.
			// Setting inputGroup to nullptr causes this to not handle anything.
			void SetCurrentActiveInputGroup(InputGroup* inputGroup);

			// Creates a new InputGroup with the specified id.
			InputGroup* CreateInputGroup(std::string id);
			// Gets an InputGroup from its id.
			InputGroup* GetInputGroup(std::string id);
			// Removes the InputGroup from this InputHandler, should not be called unless inside InputGroup's destructor.
			void RemoveInputGroupImpl(InputGroup* inputGroup);
			// Deletes the pointer, causing it to call 'RemoveInputGroupImpl'
			void RemoveInputGroup(InputGroup* inputGroup);

		private:
			std::unordered_map<std::string, InputGroup*> m_inputGroups;	// The InputGroups this InputHandler handles.

			InputGroup* m_currentInputGroup = nullptr;					// The currently active InputGroup.
		};

	} // namespace input

} // namespace gp1
