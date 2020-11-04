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
			static bool HandleEvent(Event& event);

			// Sets the current active input group by using an InputGroups id.
			static void SetCurrentActiveInputGroup(std::string id);
			// Sets the current active input group.
			// Setting inputGroup to nullptr causes this to not handle anything.
			static void SetCurrentActiveInputGroup(InputGroup* inputGroup);

			// Creates a new InputGroup with the specified id.
			static InputGroup* CreateInputGroup(std::string id);
			// Gets an InputGroup from its id.
			static InputGroup* GetInputGroup(std::string id);
			// Gets or Creates a new InputGroup with the specified id.
			static InputGroup* GetOrCreateInputGroup(std::string id);
			// Removes the InputGroup from this InputHandler, should not be called unless inside InputGroup's destructor.
			static void RemoveInputGroupImpl(InputGroup* inputGroup);
			// Deletes the pointer, causing it to call 'RemoveInputGroupImpl'
			static void RemoveInputGroup(InputGroup* inputGroup);

			// Sets the bindings to a config.
			static void SetBindingConfigs(std::string id, InputLocation location, uint32_t index);
			// Gets the bindings from a config.
			static void GetBindingConfigs(std::string id, InputLocation* location, uint32_t* index);

		private:
			static std::unordered_map<std::string, InputGroup*> m_inputGroups;	// The InputGroups this InputHandler handles.

			static InputGroup* m_currentInputGroup;								// The currently active InputGroup.
		};

	} // namespace input

} // namespace gp1
