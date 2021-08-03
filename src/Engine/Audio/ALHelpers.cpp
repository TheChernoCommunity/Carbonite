//
//	Created by Sausty on Nov. 11. 2020
//	Edited by MarcasRealAccount on 7. Dec. 2020
//
//	Description:
//		Functions used to initialise OpenAL device and context, must be initialized before using any audio sources
//

#if false // TODO: Remove when audio library is cross platform

#include "Engine/Audio/ALHelpers.h"

namespace gp1::audio
{
	bool CheckALError(Logger logger)
	{
		ALenum error = alGetError();
		if (error != AL_NO_ERROR)
		{
			switch (error)
			{
			case AL_INVALID_NAME:
				logger.LogError("OpenAL Error (AL_INVALID_NAME) : A bad name (ID) was passed to an OpenAL function.");
				break;
			case AL_INVALID_ENUM:
				logger.LogError("OpenAL Error (AL_INVALID_ENUM) : An invalid enum was passed to an OpenAL function.");
				break;
			case AL_INVALID_VALUE:
				logger.LogError("OpenAL Error (AL_INVALID_VALUE) : An invalid value was passed to an OpenAL function.");
				break;
			case AL_INVALID_OPERATION:
				logger.LogError("OpenAL Error (AL_INVALID_OPERATION) : The requested OpenAL operation is not valid.");
				break;
			case AL_OUT_OF_MEMORY:
				logger.LogError("OpenAL Error (AL_OUT_OF_MEMORY) : OpenAL memory is full!");
				break;
			default:
				logger.LogError("OpenAL Error (Unknow OpenAL Error)");
			}

			return false;
		}

		return true;
	}

	bool CheckALCError(Logger logger)
	{
		ALCcontext* ctx    = alcGetCurrentContext();
		ALCdevice*  device = alcGetContextsDevice(ctx);

		ALCenum error = alcGetError(device);
		if (error != ALC_NO_ERROR)
		{
			switch (error)
			{
			case ALC_INVALID_ENUM:
				logger.LogError("OpenAL Error (ALC_INVALID_ENUM) : An invalid enum was passed to an OpenAL function.");
				break;
			case ALC_INVALID_VALUE:
				logger.LogError("OpenAL Error (ALC_INVALID_VALUE) : An invalid value was passed to an OpenAL function.");
				break;
			case ALC_INVALID_DEVICE:
				logger.LogError("OpenAL Error (ALC_INVALID_DEVICE) : An invalid device was passed to an OpenAL function.");
				break;
			case ALC_INVALID_CONTEXT:
				logger.LogError("OpenAL Error (ALC_INVALID_CONTEXT) : An invalid context was passed to an OpenAL function.");
				break;
			case ALC_OUT_OF_MEMORY:
				logger.LogError("OpenAL Error (ALC_OUT_OF_MEMORY) : OpenAL memory is full!");
				break;
			default:
				logger.LogError("OpenAL Error (Unknow OpenALC Error)");
			}

			return false;
		}

		return true;
	}

	bool InitAL(Logger logger)
	{
		const ALCchar* defaultDeviceString = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
		ALCdevice*     device              = alcOpenDevice(defaultDeviceString);

		if (!device)
		{
			logger.LogError("Failed to get a default device for OpenAL!");
			return false;
		}

		ALCcontext* context = alcCreateContext(device, nullptr);

		if (!alcMakeContextCurrent(context))
		{
			logger.LogError("Failed to create the OpenAL context!");
			return false;
		}

		return true;
	}

	bool ShutdownAL(Logger logger)
	{
		ALCcontext* context = alcGetCurrentContext();
		ALCdevice*  device  = alcGetContextsDevice(context);

		if (!alcMakeContextCurrent(NULL))
		{
			logger.LogError("Failed to reset OpenAL context!");
			return false;
		}

		alcDestroyContext(context);

		if (!alcCloseDevice(device))
		{
			logger.LogError("Failed to close OpenAL device!");
			return false;
		}

		return true;
	}

} // namespace gp1::audio

#endif