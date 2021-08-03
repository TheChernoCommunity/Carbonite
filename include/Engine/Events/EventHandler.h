//
// Created by sfulham on 8/10/20.
// Edited by MarcasRealAccount on 4. Nov. 2020.
//

#pragma once

#include "Engine/Events/Event.h"
#include "Engine/Input/InputHandler.h"

namespace gp1::events
{
	class EventHandler
	{
	public:
		// Push an event to be handled
		template <typename T>
		static void PushEvent(T& e)
		{
			Dispatch<T>(e, input::InputHandler::HandleEvent);
		}

		// Handle an event
		template <typename T, typename F>
		static void Dispatch(Event& e, const F& f)
		{
			if (e.GetType() == T::GetTypeS() && (e.Handled == false))
			{
				e.Handled = f(static_cast<T&>(e));
			}
		}
	};

} // namespace gp1::events
