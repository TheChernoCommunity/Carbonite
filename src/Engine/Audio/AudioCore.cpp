//
//	Created by Sausty on Nov. 11. 2020
//
//	Description:
//		Implementation of AudioCore.h
//

#include "Engine/Audio/AudioCore.h"
#include "Engine/Audio/Audio.h"

namespace gp1
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
}
