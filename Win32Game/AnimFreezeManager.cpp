#include "stdafx.h"
#include "AnimFreezeManager.h"

AnimFreezeManager::AnimFreezeManager() {
}

AnimFreezeManager::~AnimFreezeManager() {
  for (HashTableIterator iter = rendererFreezeTable_.begin(); iter != rendererFreezeTable_.end();) {
    AnimFreezeInfo* pDel = (AnimFreezeInfo*)*iter;

    iter = rendererFreezeTable_.erase(iter);

    delete pDel;
  }

  rendererFreezeTable_.Cleanup();
}
void AnimFreezeManager::BeginPlay() {
}
void AnimFreezeManager::Tick(unsigned long long deltaTick) {
  for (int i = 0; i < frozenActors_.size(); ++i) {
    unsigned long long actorId = frozenActors_[i];
    AnimFreezeInfo* pFind = nullptr;
    if (0 == rendererFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
      frozenActors_.erase(frozenActors_.begin() + i);
      --i;
      continue;
    }
    if (true == pFind->isInfinite_) {
      continue;
    }
    pFind->timer_ += deltaTick;
    if (pFind->timer_ >= pFind->duration_) {
      Defreeze(actorId);
    }
  }
}
bool AnimFreezeManager::Initialize() {
  return rendererFreezeTable_.Initialize(8, 8);
}

bool AnimFreezeManager::RegistComponent(unsigned long long actorId, ImageRenderer* pImageRenderer) {
  if (nullptr == pImageRenderer) {
    return false;
  }

  AnimFreezeInfo* pFind = nullptr;
  if (0 != rendererFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return false;
  }

  AnimFreezeInfo* pNewInfo = new AnimFreezeInfo;
  pNewInfo->actorId_ = actorId;
  pNewInfo->pImageRenderer_ = pImageRenderer;
  pNewInfo->searchHandle_ = rendererFreezeTable_.Insert(pNewInfo, &pNewInfo->actorId_, 8);

  return nullptr != pNewInfo->searchHandle_;
}

void AnimFreezeManager::UnregistComponent(unsigned long long actorId) {
  auto iter = std::find(frozenActors_.begin(), frozenActors_.end(), actorId);
  if (iter != frozenActors_.end()) {
    frozenActors_.erase(iter);
  }

  AnimFreezeInfo* pFind = nullptr;
  if (0 == rendererFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  rendererFreezeTable_.Delete(pFind->searchHandle_);
}

void AnimFreezeManager::ApplyFreeze(unsigned long long actorId, bool isInfinite /* = true*/, unsigned long long duration /*= 0*/) {
  AnimFreezeInfo* pFind = nullptr;
  if (0 == rendererFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  auto iter = std::find(frozenActors_.begin(), frozenActors_.end(), actorId);
  if (iter == frozenActors_.end()) {
    frozenActors_.push_back(actorId);
  }

  pFind->pImageRenderer_->AnimFreeze();
  pFind->isInfinite_ = isInfinite;
  pFind->duration_ = duration;
  pFind->timer_ = 0;
}

void AnimFreezeManager::Defreeze(unsigned long long actorId) {
  AnimFreezeInfo* pFind = nullptr;
  if (0 == rendererFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  auto iter = std::find(frozenActors_.begin(), frozenActors_.end(), actorId);
  if (iter != frozenActors_.end()) {
    frozenActors_.erase(iter);
  }

  if (nullptr != pFind->pImageRenderer_) {
    pFind->pImageRenderer_->UnAnimFreeze();
  }
}
