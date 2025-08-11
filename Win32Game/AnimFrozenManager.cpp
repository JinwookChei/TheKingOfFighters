#include "stdafx.h"
#include "AnimFrozenManager.h"

AnimFrozenManager::AnimFrozenManager() {
}

AnimFrozenManager::~AnimFrozenManager() {
  for (HashTableIterator iter = imageRendererTable_.begin(); iter != imageRendererTable_.end();) {
    RestrictComponentInfo* pDel = (RestrictComponentInfo*)*iter;

    iter = imageRendererTable_.erase(iter);

    delete pDel;
  }

  imageRendererTable_.Cleanup();
}
void AnimFrozenManager::BeginPlay() {
}
void AnimFrozenManager::Tick(unsigned long long deltaTick) {
  for (int i = 0; i < frozenActors_.size(); ++i) {
    unsigned long long actorId = frozenActors_[i];
    ImangeRendererInfo* pFind = nullptr;
    if (0 == imageRendererTable_.Select((void**)&pFind, 1, &actorId, 8)) {
      frozenActors_.erase(frozenActors_.begin() + i);
      --i;
      continue;
    }
    if (true == pFind->isInfinite_) {
      continue;
    }
    pFind->timer_ += deltaTick;
    if (pFind->timer_ >= pFind->duration_) {
      UnFreeze(actorId);
    }
  }
}
bool AnimFrozenManager::Initialize() {
  return imageRendererTable_.Initialize(8, 8);
}

bool AnimFrozenManager::RegistComponent(unsigned long long actorId, ImageRenderer* pImageRenderer) {
  if (nullptr == pImageRenderer) {
    return false;
  }

  ImangeRendererInfo* pFind = nullptr;
  if (0 != imageRendererTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return false;
  }

  ImangeRendererInfo* pNewInfo = new ImangeRendererInfo;
  pNewInfo->actorId_ = actorId;
  pNewInfo->pImageRenderer_ = pImageRenderer;
  pNewInfo->searchHandle_ = imageRendererTable_.Insert(pNewInfo, &pNewInfo->actorId_, 8);

  return nullptr != pNewInfo->searchHandle_;
}

void AnimFrozenManager::UnregistComponent(unsigned long long actorId) {
  ImangeRendererInfo* pFind = nullptr;
  if (0 == imageRendererTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  imageRendererTable_.Delete(pFind->searchHandle_);
}

void AnimFrozenManager::ApplyFreeze(unsigned long long actorId, bool isInfinite /* = true*/, unsigned long long duration /*= 0*/) {
  ImangeRendererInfo* pFind = nullptr;
  if (0 == imageRendererTable_.Select((void**)&pFind, 1, &actorId, 8)) {
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

void AnimFrozenManager::UnFreeze(unsigned long long actorId) {
  ImangeRendererInfo* pFind = nullptr;
  if (0 == imageRendererTable_.Select((void**)&pFind, 1, &actorId, 8)) {
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
