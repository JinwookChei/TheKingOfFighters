#pragma once

#include "Sound.h"

class SoundManager final {
  friend class EngineCore;

 public:
  SoundManager();

  ~SoundManager();

  JO_API static SoundManager* Instance();

  JO_API bool Load(const Path& path, int key);

  JO_API SoundChannel SoundPlay(int key, bool pause = false);

 private:
  Sound* Get(int key);

  bool Initialize();

  void Tick();

  void Cleanup();

  HashTable sounds_;
};