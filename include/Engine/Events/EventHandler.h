//
// Created by sfulham on 8/10/20.
//

#pragma once

#include "Event.h"

namespace gp1
{
    class EventHandler
    {
    public:
        template<typename T>
        static void PushEvent(T& e)
        {

        }

        template<typename T, typename F>
        void Dispatch(Event& e, const F& f)
        {
            if(e.GetType() == T::GetTypeS() && (e.Handled == false))
            {
                e.Handled = f(static_cast<T&>(e));
            }
        }
    };
}
