//
//	Created by Sausty on Nov. 11. 2020
//
//	Description:
//		Class that represents an Audio Source.
//
//	TODOS:
//		- FLAC support
//		- OGG support
//

#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

namespace gp1 {
class AudioCore;

class AudioSource {
public:
  AudioSource() = default;
  ~AudioSource();

  void SetPosition(float x, float y, float z);
  void SetGain(float gain);
  void SetPitch(float pitch);
  void SetSpatial(bool spatial);
  void SetLoop(bool loop);

  static AudioSource LoadFromFile(const std::string &file,
                                  bool spatial = false);

private:
  AudioSource(uint32_t buffer);

  uint32_t m_BufferHandle = 0;
  uint32_t m_SourceHandle = 0;

  bool m_Spatial = false;
  float m_Position[3] = {0.0f, 0.0f, 0.0f};
  float m_Gain = 1.0f;
  float m_Pitch = 1.0f;
  bool m_Loop = false;

  friend class Audio;
};

class Audio {
public:
  static AudioSource LoadAudioSource(const std::string &filename);

  static void Play(const AudioSource &source);
  static void Stop(const AudioSource &source);

private:
  static void Init();

  static AudioSource LoadAudioSourceWAV(const std::string &filename);
  static AudioSource LoadAudioSourceMP3(const std::string &filename);

  friend class AudioCore;
};

class AudioLibrary {
public:
  void Add(const std::string &name, const std::string &file,
           bool spatial = false);
  AudioSource AddAndGet(const std::string &name, const std::string &file,
                        bool spatial = false);

  AudioSource Get(const std::string &name);
  void Remove(const std::string &name);

private:
  std::unordered_map<std::string, AudioSource> m_AudioCache;
};
} // namespace gp1
