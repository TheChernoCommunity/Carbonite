//
//	Created by Sausty on Nov. 11. 2020
//	Edited by MarcasRealAccount on 7. Dec. 2020.
//
//	Description:
//		Implementation of AudioCore.h
//

#if false // TODO: Remove when audio library is cross platform

#include "Engine/Audio/AudioCore.h"
#include "Engine/Audio/Audio.h"

namespace gp1::audio
{
	Logger AudioCore::s_AudioLogger = Logger { "AudioCore" };

	void AudioCore::Init()
	{
		InitAL(s_AudioLogger);
		Audio::Init();
	}

	void AudioCore::Shutdown()
	{
		ShutdownAL(s_AudioLogger);
	}

} // namespace gp1::audio

#endif