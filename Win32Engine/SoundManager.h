#pragma once

#include "Sound.h"

class SoundManager final {
  friend class EngineCore;

 public:
  SoundManager();

  ~SoundManager();

  ENGINE_API static SoundManager* Instance();

  ENGINE_API bool Load(const Path& path, int key);

  ENGINE_API SoundChannel SoundPlay(int key, bool loop = false, bool pause = false);

 private:
  Sound* Get(int key);

  bool Initialize();

  void Tick();

  void Cleanup();

  HashTable sounds_;
};