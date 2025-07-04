#include "stdafx.h"
#include "Level.h"
#include "Effect.h"
#include "EffectManager.h"

EffectManager::EffectManager() {
}

EffectManager::~EffectManager() {
  for (HashTableIterator iter = effectTable_.begin(); iter != effectTable_.end();) {
    EffectInfo* pDel = (EffectInfo*)*iter;

    iter = effectTable_.erase(iter);

    delete pDel;
  }

  effectTable_.Cleanup();
}

EffectManager* EffectManager::Instance() {
  return GEffectManager;
}

bool EffectManager::Initialize() {
  return effectTable_.Initialize(8, 8);
}

bool EffectManager::RegistEffect(unsigned long long effectTag, unsigned long long imageTag, unsigned int startIndex, unsigned int endIndex, unsigned long long interval, bool loop, const Vector& imageLocalScale, const Color8Bit& transColor, bool isAlphaEffect /* = false*/, float alpha /* = 0.0f*/) {
  std::vector<unsigned int> indices;

  int size = (int)(endIndex - startIndex);
  if (size < 0) {
    return false;
  }

  indices.reserve(size);

  for (unsigned int n = startIndex; n <= endIndex; ++n) {
    indices.push_back(n);
  }

  return RegistEffect(effectTag, imageTag, indices, interval, loop, imageLocalScale,  transColor, isAlphaEffect, alpha);
}

bool EffectManager::RegistEffect(unsigned long long effectTag, unsigned long long imageTag, const std::vector<unsigned int>& indices, unsigned long long interval, bool loop, const Vector& imageLocalScale, const Color8Bit& transColor, bool isAlphaEffect /* = false*/, float alpha /* = 0.0f*/) {
  std::vector<unsigned long long> intervals;
  intervals.reserve(indices.size());

  for (size_t n = 0; n < indices.size(); ++n) {
    intervals.push_back(interval);
  }

  return RegistEffect(effectTag, imageTag, indices, intervals, loop, imageLocalScale, transColor, isAlphaEffect, alpha);
}

bool EffectManager::RegistEffect(unsigned long long effectTag, unsigned long long imageTag, const std::vector<unsigned int>& indices, const std::vector<unsigned long long> intervals, bool loop, const Vector& imageLocalScale,  const Color8Bit& transColor, bool isAlphaEffect /* = false*/, float alpha /* = 0.0f*/) {
  EffectInfo* pFind;
  if (0 != effectTable_.Select((void**)&pFind, 8, &effectTag, 8)) {
    return false;
  }

  if (0 >= indices.size()) {
    return false;
  }

  EffectInfo* newEffectInfo = new EffectInfo;
  newEffectInfo->imageTag_ = imageTag;
  newEffectInfo->effectTag_ = effectTag;
  newEffectInfo->indices_ = indices;
  newEffectInfo->intervals_ = intervals;
  newEffectInfo->loop_ = loop;
  newEffectInfo->imageLocalScale_ = imageLocalScale;
  newEffectInfo->transColor_ = transColor;
  newEffectInfo->isAlphaEffect_ = isAlphaEffect;
  newEffectInfo->alpha_ = alpha;
  newEffectInfo->searchHandle_ = effectTable_.Insert(newEffectInfo, &newEffectInfo->effectTag_, 8);

  return nullptr != newEffectInfo->searchHandle_;
}

Effect* EffectManager::SpawnEffect(Level* level, unsigned long long effectTag, const Vector& position) {
  if (nullptr == level) {
    return nullptr;
  }

  EffectInfo* pFind = nullptr;
  if (0 == effectTable_.Select((void**)&pFind, 1, &effectTag, 8)) {
    return nullptr;
  }

  Effect* newEffect = level->SpawnActor<Effect>(ActorGroupEngineType::ActorGroupEngineType_Effect);
  newEffect->SetPosition(position);
  newEffect->SetEffectInfo(pFind);
  newEffect->SetUseCameraposition(true);
  newEffect->Initialize();

  return newEffect;
}