/*

	Created by Sausty on Nov. 11. 2020

	Description:
		Class used to initialise OpenAL device and context, must be initialized before using any audio sources
*/

#pragma once

#include "Engine/Audio/ALHelpers.h"

namespace gp1
{
	class AudioCore
	{
	public:
		static void Init();
		static void Shutdown();
	private:
		static Logger s_AudioLogger;
	};
}
