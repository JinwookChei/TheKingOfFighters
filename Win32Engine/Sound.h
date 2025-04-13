#pragma once

namespace FMOD {
class Sound;
class Channel;
}  // namespace FMOD

class SoundChannel final {
 public:
  JO_API SoundChannel();

  JO_API SoundChannel(SoundChannel&& other) noexcept;

  explicit SoundChannel(FMOD::Channel* channel);

  JO_API ~SoundChannel();

  JO_API SoundChannel& operator=(SoundChannel&& other) noexcept;

  JO_API bool IsEmpty();

  JO_API bool LoopCount(int count);

  JO_API void Volume(float volume);

  JO_API void Play(bool play = true);

  void Destroy();

  JO_API void Pause(bool pause = true);

  JO_API bool IsPause();

  JO_API bool IsPlaying();

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