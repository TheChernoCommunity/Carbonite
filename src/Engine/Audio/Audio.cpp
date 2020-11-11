/*
	Created by Sausty on Nov. 11. 2020

	Description:
		Implementation of the AudioSource, Audio and AudioLibrary class.
*/

#include "Engine/Audio/Audio.h"

#include <minimp3.h>
#include <minimp3_ex.h>
#include <dr_wav.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include <filesystem>

#include "Engine/Audio/ALHelpers.h"
#include "Engine/Audio/AudioCore.h"

namespace gp1
{
	static ALCdevice* s_AudioDevice = nullptr;
	static mp3dec_t s_Mp3d;

	static uint8_t* s_AudioScratchBuffer;
	static uint32_t s_AudioScratchBufferSize = 10 * 1024 * 1024;

	struct ReadWavData
	{
		unsigned int Channels = 0;
		unsigned int SampleRate = 0;
		uint64_t TotalPCMFrameCount = 0;
		std::vector<uint16_t> PCMData;
		uint64_t GetTotalSamples() { return TotalPCMFrameCount * Channels; }
	};

	enum class AudioFileFormat
	{
		None = 0,
		MP3,
		WAV,
		FLAC,
		OGG
	};

	static AudioFileFormat GetAudioFormat(const std::string& filename)
	{
		std::filesystem::path path = filename;
		std::string extension = path.extension().string();

		if (extension == ".wav")  return AudioFileFormat::WAV;
		if (extension == ".ogg")  return AudioFileFormat::OGG;
		if (extension == ".mp3")  return AudioFileFormat::MP3;
		if (extension == ".flac") return AudioFileFormat::FLAC;

		return AudioFileFormat::None;
	}

	static ALenum GetOpenALFormat(uint32_t channels)
	{
		switch (channels)
		{
			case 1:  return AL_FORMAT_MONO16;
			case 2:  return AL_FORMAT_STEREO16;
		}
		// assert
		return 0;
	}

	// AUDIO SOURCE //

	AudioSource::AudioSource(uint32_t buffer)
		: m_BufferHandle(buffer)
	{
	}

	AudioSource Audio::LoadAudioSourceWAV(const std::string& filename)
	{
		ReadWavData stereoData;
		drwav_int16* pSampleData = drwav_open_file_and_read_pcm_frames_s16(filename.c_str(), &stereoData.Channels, &stereoData.SampleRate, &stereoData.TotalPCMFrameCount, nullptr);

		if (pSampleData == NULL)
			AudioCore::s_AudioLogger.LogError("Failed to load audio file!");
		if (stereoData.GetTotalSamples() > uint64_t(std::numeric_limits<size_t>::max()))
			AudioCore::s_AudioLogger.LogError("Too much data in file for 32bit addressed vector!");

		stereoData.PCMData.resize(size_t(stereoData.GetTotalSamples()));
		std::memcpy(stereoData.PCMData.data(), pSampleData, stereoData.PCMData.size() * /*twobytes_in_s15*/2);
		drwav_free(pSampleData, nullptr);

		auto alFormat = GetOpenALFormat(stereoData.Channels);

		ALuint buffer;
		alGenBuffers(1, &buffer);
		alBufferData(buffer, alFormat, stereoData.PCMData.data(), stereoData.PCMData.size() * 2, stereoData.SampleRate);

		AudioSource result = { buffer };
		alGenSources(1, &result.m_SourceHandle);
		alSourcei(result.m_SourceHandle, AL_BUFFER, buffer);

		CheckALError(AudioCore::s_AudioLogger);

		return result;
	}

	AudioSource Audio::LoadAudioSourceMP3(const std::string& filename)
	{
		mp3dec_file_info_t info;
		int loadResult = mp3dec_load(&s_Mp3d, filename.c_str(), &info, NULL, NULL);
		uint32_t size = info.samples * sizeof(mp3d_sample_t);

		auto sampleRate = info.hz;
		auto channels = info.channels;
		auto alFormat = GetOpenALFormat(channels);

		ALuint buffer;
		alGenBuffers(1, &buffer);
		alBufferData(buffer, alFormat, info.buffer, size, sampleRate);

		AudioSource result = { buffer };
		alGenSources(1, &result.m_SourceHandle);
		alSourcei(result.m_SourceHandle, AL_BUFFER, buffer);

		CheckALError(AudioCore::s_AudioLogger);

		return result;
	}

	AudioSource::~AudioSource()
	{
		// BUG : The chunk of code below will result in an OpenAL error if uncommented for some reason :(

		//alDeleteBuffers(1, &m_BufferHandle);
		//alDeleteSources(1, &m_SourceHandle);
	}

	void AudioSource::SetPosition(float x, float y, float z)
	{
		m_Position[0] = x;
		m_Position[1] = y;
		m_Position[2] = z;

		alSourcefv(m_SourceHandle, AL_POSITION, m_Position);
	}

	void AudioSource::SetGain(float gain)
	{
		m_Gain = gain;

		alSourcef(m_SourceHandle, AL_GAIN, gain);
	}

	void AudioSource::SetPitch(float pitch)
	{
		m_Pitch = pitch;

		alSourcef(m_SourceHandle, AL_PITCH, pitch);
	}

	void AudioSource::SetSpatial(bool spatial)
	{
		m_Spatial = spatial;

		alSourcei(m_SourceHandle, AL_SOURCE_SPATIALIZE_SOFT, spatial ? AL_TRUE : AL_FALSE);
		alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	}

	void AudioSource::SetLoop(bool loop)
	{
		m_Loop = loop;

		alSourcei(m_SourceHandle, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
	}

	AudioSource AudioSource::LoadFromFile(const std::string& file, bool spatial)
	{
		AudioSource result = Audio::LoadAudioSource(file);
		result.SetSpatial(spatial);
		return result;
	}

	// END AUDIO SOURCE //

	// AUDIO //

	AudioSource Audio::LoadAudioSource(const std::string& filename)
	{
		auto format = GetAudioFormat(filename);
		switch (format)
		{
			case AudioFileFormat::WAV:  return LoadAudioSourceWAV(filename);
			case AudioFileFormat::MP3:  return LoadAudioSourceMP3(filename);
		}

		return AudioSource(0);
	}

	void Audio::Play(const AudioSource& source)
	{
		alSourcePlay(source.m_SourceHandle);
	}

	void Audio::Stop(const AudioSource& source)
	{
		alSourceStop(source.m_SourceHandle);
	}

	void Audio::Init()
	{
		mp3dec_init(&s_Mp3d);

		s_AudioScratchBuffer = new uint8_t[s_AudioScratchBufferSize];

		ALfloat listenerPos[] = { 0.0,0.0,0.0 };
		ALfloat listenerVel[] = { 0.0,0.0,0.0 };
		ALfloat listenerOri[] = { 0.0,0.0,-1.0, 0.0,1.0,0.0 };
		alListenerfv(AL_POSITION, listenerPos);
		alListenerfv(AL_VELOCITY, listenerVel);
		alListenerfv(AL_ORIENTATION, listenerOri);
	}

	// END AUDIO //

	// AUDIO LIBRARY //

	void AudioLibrary::Add(const std::string& name, const std::string& file, bool spatial)
	{
		auto result = AudioSource::LoadFromFile(file, spatial);
		m_AudioCache[name] = result;
	}

	AudioSource AudioLibrary::AddAndGet(const std::string& name, const std::string& file, bool spatial)
	{
		auto result = AudioSource::LoadFromFile(file, spatial);
		m_AudioCache[name] = result;
		return result;
	}

	AudioSource AudioLibrary::Get(const std::string& name)
	{
		return m_AudioCache[name];
	}

	void AudioLibrary::Remove(const std::string& name)
	{
		m_AudioCache.erase(name);
	}

	// END AUDIO LIBRARY //
}
