//
//	Created by MarcasRealAccount on 8. Oct. 2020
//

#pragma once

#include "Engine/Input/InputGroup.h"

#include <unordered_map>

namespace gp1
{
	namespace events
	{
		class Event;
	}

	namespace window
	{
		class Window;
	}

	class Application;

	namespace input
	{
		class InputHandler
		{
		public:
			// Clearas all input's.
			static void CleanUp();

			// Handles events for Input Bindings
			static bool HandleEvent(events::Event& event);

			// Sets the current active input group by using an InputGroups id.
			static void SetCurrentActiveInputGroup(const std::string& id);
			// Sets the current active input group.
			// Setting inputGroup to nullptr causes this to not handle anything.
			static void SetCurrentActiveInputGroup(InputGroup* inputGroup);

			// Creates a new InputGroup with the specified id.
			static InputGroup* CreateInputGroup(const std::string& id);
			// Gets an InputGroup from its id.
			static InputGroup* GetInputGroup(const std::string& id);
			// Gets or Creates a new InputGroup with the specified id.
			static InputGroup* GetOrCreateInputGroup(const std::string& id);
			// Removes the InputGroup from this InputHandler, should not be called unless inside InputGroup's destructor.
			static void RemoveInputGroupImpl(InputGroup* inputGroup);
			// Deletes the pointer, causing it to call 'RemoveInputGroupImpl'
			static void RemoveInputGroup(InputGroup* inputGroup);

			// Sets the bindings to a config.
			static void SetBindingConfigs(const std::string& id, InputType inputType, InputLocation location, uint32_t index);
			// Gets the bindings from a config.
			static void GetBindingConfigs(const std::string& id, InputType inputType, InputLocation* location, uint32_t* index);

			friend Application;

		private:
			static std::unordered_map<std::string, InputGroup*> s_inputGroups; // The InputGroups this InputHandler handles.

			static InputGroup*     s_currentInputGroup; // The currently active InputGroup.
			static window::Window* s_Window;            // The window of this application.
		};

	} // namespace input

} // namespace gp1
