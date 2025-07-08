#include "stdafx.h"
#include "Sound.h"

SoundChannel::SoundChannel()
    : channel_(nullptr) {
}

SoundChannel::SoundChannel(SoundChannel&& other) noexcept
    : channel_(other.channel_) {
  other.channel_ = nullptr;
}

SoundChannel::SoundChannel(FMOD::Channel* channel)
    : channel_(channel) {
}

SoundChannel::~SoundChannel() {
  Destroy();
}

SoundChannel& SoundChannel::operator=(SoundChannel&& other) noexcept {
  channel_ = other.channel_;
  other.channel_ = nullptr;
  return *this;
}

bool SoundChannel::IsEmpty() {
  if (nullptr == channel_) {
    return true;
  }

  bool isPlaying = false;

  return FMOD_RESULT::FMOD_ERR_INVALID_HANDLE == channel_->isPlaying(&isPlaying);
}

bool SoundChannel::LoopCount(int count) {
  if (IsEmpty()) {
    return false;
  }

  if (FMOD_RESULT::FMOD_OK != channel_->setLoopCount(count)) {
    return false;
  }

  return true;
}

void SoundChannel::Volume(float volume) {
  if (IsEmpty()) {
    return;
  }

  channel_->setVolume(volume);
}

void SoundChannel::Play(bool play) {
  if (IsEmpty()) {
    return;
  }

  if (!play) {
    channel_->setPosition(0, FMOD_TIMEUNIT_MS);
  }

  channel_->setPaused(!play);
}

void SoundChannel::Destroy() {
  if (IsEmpty()) {
    return;
  }

  channel_->stop();
}

void SoundChannel::Pause(bool pause) {
  if (IsEmpty()) {
    return;
  }

  channel_->setPaused(pause);
}

bool SoundChannel::IsPause() {
  if (IsEmpty()) {
    return false;
  }
  bool pauseValue = false;
  channel_->getPaused(&pauseValue);
  return pauseValue;
}

bool SoundChannel::IsPlaying() {
  if (IsEmpty()) {
    return false;
  }
  if (IsPause()) {
    return false;
  }

  bool playValue = false;
  channel_->isPlaying(&playValue);
  return playValue;
}

Sound::Sound()
    : sound_(nullptr),
      searchHandle_(nullptr) {
}

Sound::~Sound() {
}

bool Sound::Load(const Path& path) {
  if (nullptr == GSoundSystem) {
    return false;
  }

  if (FMOD_RESULT::FMOD_OK != GSoundSystem->createSound(path.GetPathString().c_str(), FMOD_LOOP_NORMAL, nullptr, &sound_)) {
    sound_ = nullptr;
    return false;
  }

  return true;
}

SoundChannel Sound::Play(bool pause) {
  if (nullptr == GSoundSystem) {
    return SoundChannel();
  }
  if (nullptr == sound_) {
    return SoundChannel();  
  }

  FMOD::Channel* channel = nullptr;
  if (FMOD_RESULT::FMOD_OK != GSoundSystem->playSound(sound_, nullptr, pause, &channel)) {
    return SoundChannel();
  }

  return SoundChannel(channel);
}
