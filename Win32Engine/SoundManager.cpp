#include "stdafx.h"
#include "SoundManager.h"

FMOD::System* GSoundSystem = nullptr;

SoundManager::SoundManager() {
  sounds_.Initialize(8, 4);
}

SoundManager::~SoundManager() {
  Cleanup();
}

SoundManager* SoundManager::Instance() {
  return GSound;
}

bool SoundManager::Load(const Path& path, int key) {
  Sound* pSound = Get(key);
  if (nullptr != pSound) {
    return true;
  }

  pSound = new Sound;
  if (false == pSound->Load(path)) {
    delete pSound;
    return false;
  }

  pSound->searchHandle_ = sounds_.Insert(pSound, &key, 4);

  return true;
}

SoundChannel SoundManager::SoundPlay(int key, bool loop, bool pause) {
  Sound* pSound = Get(key);
  if (nullptr == pSound) {
    return SoundChannel();
  }

  SoundChannel channel = pSound->Play(pause);
  if (loop) {
    channel.LoopCount(-1);
  } else {
    channel.LoopCount(0);
  }
  

  return channel;
}

Sound* SoundManager::Get(int key) {
  Sound* pFind = nullptr;
  if (0 == sounds_.Select((void**)&pFind, 1, &key, 4)) {
    return nullptr;
  }
  return pFind;
}

bool SoundManager::Initialize() {
  HRESULT hr = ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
  if (hr != S_OK && hr != S_FALSE) {
    return false;
  }

  FMOD::System_Create(&GSoundSystem);
  if (nullptr == GSoundSystem) {
    return false;
  }

  if (FMOD_RESULT::FMOD_OK != GSoundSystem->init(32, FMOD_DEFAULT, nullptr)) {
    return false;
  }

  return true;
}

void SoundManager::Tick() {
  if (nullptr == GSoundSystem) {
    return;
  }

  GSoundSystem->update();
}

void SoundManager::Cleanup() {
  for (HashTableIterator iter = sounds_.begin(); iter != sounds_.end(); ++iter) {
    Sound* pSound = (Sound*)*iter;
    delete pSound;
  }
  sounds_.Cleanup();

  if (nullptr != GSoundSystem) {
    GSoundSystem->release();
  }

  ::CoUninitialize();
}
