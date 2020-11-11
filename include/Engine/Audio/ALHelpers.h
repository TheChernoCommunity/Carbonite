/*

	Created by Sausty on Nov. 11. 2020

	Description:
		OpenAL utilities for initialising and cleaning up audio device, as well as error handling
*/

#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include "Engine/Utility/Logger.h"

namespace gp1
{
	bool CheckALError(Logger logger);
	bool CheckALCError(Logger logger);
	bool InitAL(Logger logger);
	bool ShutdownAL(Logger logger);
}
