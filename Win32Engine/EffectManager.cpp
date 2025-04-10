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

bool EffectManager::RegistEffect(unsigned long long effectTag, unsigned long long imageIndex, unsigned int startIndex, unsigned int endIndex, unsigned long long interval, bool loop, const Color8Bit& transColor) {
  std::vector<unsigned int> indices;

  int size = (int)(endIndex - startIndex);
  if (size < 0) {
    return false;
  }

  indices.reserve(size);

  for (unsigned int n = startIndex; n <= endIndex; ++n) {
    indices.push_back(n);
  }

  return RegistEffect(effectTag, imageIndex, indices, interval, loop, transColor);
}

bool EffectManager::RegistEffect(unsigned long long effectTag, unsigned long long imageIndex, const std::vector<unsigned int>& indices, unsigned long long interval, bool loop, const Color8Bit& transColor) {
  std::vector<unsigned long long> intervals;
  intervals.reserve(indices.size());

  for (size_t n = 0; n < indices.size(); ++n) {
    intervals.push_back(interval);
  }

  return RegistEffect(effectTag, imageIndex, indices, intervals, loop, transColor);
}

bool EffectManager::RegistEffect(unsigned long long effectTag, unsigned long long imageIndex, const std::vector<unsigned int>& indices, const std::vector<unsigned long long> intervals, bool loop, const Color8Bit& transColor) {
  EffectInfo* pFind;
  if (0 != effectTable_.Select((void**)&pFind, 8, &effectTag, 8)) {
    return false;
  }

  if (0 >= indices.size()) {
    return false;
  }

  EffectInfo* newEffectInfo = new EffectInfo;
  newEffectInfo->imageIndex_ = imageIndex;
  newEffectInfo->effectTag_ = effectTag;
  newEffectInfo->indices_ = indices;
  newEffectInfo->intervals_ = intervals;
  newEffectInfo->loop_ = loop;
  newEffectInfo->transColor_ = transColor;
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


  Effect* newEffect = level->SpawnActor<Effect>(ActorGroupEngineType::ActorGroupEngineType_None);
  newEffect->SetPosition(position);
  newEffect->SetEffectInfo(pFind);
  newEffect->Initialize();

  //LinkToLinkedListFIFO(&effectHead_, &effectTail_, newEffect->GetEffectLink());
  return newEffect;
}