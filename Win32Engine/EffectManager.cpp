#include "stdafx.h"
#include "EffectManager.h"
#include "Effect.h"
#include "Level.h"
#include "CollisionComponent.h"

EffectManager::EffectManager()
    : level_(nullptr) {
}

EffectManager::~EffectManager() {
  for (HashTableIterator iter = effectTable_.begin(); iter != effectTable_.end();) {
    EffectInfo* pDel = (EffectInfo*)*iter;

    iter = effectTable_.erase(iter);

    if (nullptr != pDel->image_) {
      pDel->image_->Release();
    }

    delete pDel;
  }
  effectTable_.Cleanup();
}

EffectManager* EffectManager::Instance() {
  return GEffectManager;
}

bool EffectManager::Initialize(Level* level) {
  if (nullptr == level) {
    return;
  }

  if (false == effectTable_.Initialize(8, 8)) {
    return false;
  }

  level_ = level;

  return true;
}

bool EffectManager::RegistEffect(IImage* image, unsigned long long effectTag, unsigned int startFrame, unsigned int endFrame, unsigned int interval, float velocity, float reach, const Vector& direction) {
  EffectInfo* pEffectInfo;
  if (0 != effectTable_.Select((void**)&pEffectInfo, 1, &effectTag, 8)) {
    return false;
  }

  // NEW
  EffectInfo* newEffectInfo = new EffectInfo();
  newEffectInfo->image_ = image;
  image->AddRef();
  newEffectInfo->effectTag_ = effectTag;
  newEffectInfo->startFrame_ = startFrame;
  newEffectInfo->endFrame_ = endFrame;
  newEffectInfo->interval_ = interval;
  newEffectInfo->velocity_ = velocity;

  effectTable_.Insert(newEffectInfo, &newEffectInfo->effectTag_, 8);

  return true;
}

void EffectManager::SpawnEffect(unsigned int tag, const Vector& position, Actor* owner) {
  EffectInfo* pEffectInfo = nullptr;
  if (0 == effectTable_.Select((void**)&pEffectInfo, 10, &tag, 8))
  {
    return;
  }

  Effect* newEffect = level_->SpawnActor<Effect>(CollisionGroupEngineType_None); 
}
