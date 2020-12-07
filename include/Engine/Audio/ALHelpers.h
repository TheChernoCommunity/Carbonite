//
//	Created by Sausty on Nov. 11. 2020
//	Edited by MarcasRealAccount on 7. Dec. 2020.
//
//	Description:
//		OpenAL utilities for initialising and cleaning up audio device, as well as error handling
//

#pragma once

#include "Engine/Utility/Logger.h"
#include <AL/al.h>
#include <AL/alc.h>

namespace gp1::audio
{
	bool CheckALError(Logger logger);
	bool CheckALCError(Logger logger);
	bool InitAL(Logger logger);
	bool ShutdownAL(Logger logger);

} // namespace gp1::audio
