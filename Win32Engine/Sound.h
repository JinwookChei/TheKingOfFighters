#pragma once

namespace FMOD {
class Sound;
class Channel;
}  // namespace FMOD

class SoundChannel final {
 public:
  ENGINE_API SoundChannel();

  ENGINE_API SoundChannel(SoundChannel&& other) noexcept;

  explicit SoundChannel(FMOD::Channel* channel);

  ENGINE_API ~SoundChannel();

  ENGINE_API SoundChannel& operator=(SoundChannel&& other) noexcept;

  ENGINE_API bool IsEmpty();

  ENGINE_API bool LoopCount(int count);

  ENGINE_API void Volume(float volume);

  ENGINE_API void Play(bool play = true);

  void Destroy();

  ENGINE_API void Pause(bool pause = true);

  ENGINE_API bool IsPause();

  ENGINE_API bool IsPlaying();

 private:
  FMOD::Channel* channel_;
};

class Sound final {
  friend class SoundManager;

 public:
  Sound();

  ~Sound();

  bool Load(const Path& path);

  SoundChannel Play(bool pause = false);

 private:
  FMOD::Sound* sound_;

  void* searchHandle_;
};