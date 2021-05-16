//
//	Created by Sausty on Nov. 11. 2020
//	Edited by MarcasRealAccount on 7. Dec. 2020.
//
//	Description:
//		Class used to initialise OpenAL device and context, must be initialized before using any audio sources
//

#pragma once

#if false // TODO: Remove when audio library is cross platform

#include "Engine/Audio/ALHelpers.h"

namespace gp1::audio
{
	class Audio;
	class AudioSource;

	class AudioCore
	{
	public:
		static void Init();
		static void Shutdown();

	private:
		static Logger s_AudioLogger;

		friend class Audio;
		friend class AudioSource;
	};

} // namespace gp1::audio

#endif