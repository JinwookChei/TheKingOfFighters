#include "stdafx.h"
#include "ActorFreezeManager.h"

ActorFreezeManager::ActorFreezeManager() {
}

ActorFreezeManager::~ActorFreezeManager() {
  for (HashTableIterator iter = actorFreezeTable_.begin(); iter != actorFreezeTable_.end();) {
    ActorFreezeInfo* pDel = (ActorFreezeInfo*)*iter;

    iter = actorFreezeTable_.erase(iter);

    delete pDel;
  }

  actorFreezeTable_.Cleanup();
}

void ActorFreezeManager::BeginPlay() {
}

void ActorFreezeManager::Tick(unsigned long long deltaTick) {
  for (int i = 0; i < frozenActors_.size(); ++i) {
    unsigned long long actorId = frozenActors_[i];
    ActorFreezeInfo* pFind = nullptr;
    if (0 == actorFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
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

bool ActorFreezeManager::Initialize() {
  return actorFreezeTable_.Initialize(8, 8);
}

bool ActorFreezeManager::RegistActor(unsigned long long actorId, Actor* pActor) {
  if (nullptr == pActor) {
    return false;
  }

  ActorFreezeInfo* pFind = nullptr;
  if (0 != actorFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return false;
  }

  ActorFreezeInfo* pNewInfo = new ActorFreezeInfo;
  pNewInfo->actorId_ = actorId;
  pNewInfo->pActor_ = pActor;
  pNewInfo->searchHandle_ = actorFreezeTable_.Insert(pNewInfo, &pNewInfo->actorId_, 8);

  return nullptr != pNewInfo->searchHandle_;
}

void ActorFreezeManager::UnregistActor(unsigned long long actorId) {
  auto iter = std::find(frozenActors_.begin(), frozenActors_.end(), actorId);
  if (iter != frozenActors_.end()) {
    frozenActors_.erase(iter);
  }

  ActorFreezeInfo* pFind = nullptr;
  if (0 == actorFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  actorFreezeTable_.Delete(pFind->searchHandle_);
  delete pFind;
}

void ActorFreezeManager::ApplyFreeze(unsigned long long actorId, bool isInfinite /*= true*/, unsigned long long duration /*= 0*/) {
  ActorFreezeInfo* pFind = nullptr;
  if (0 == actorFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  auto iter = std::find(frozenActors_.begin(), frozenActors_.end(), actorId);
  if (iter == frozenActors_.end()) {
    frozenActors_.push_back(actorId);
  }

  pFind->pActor_->SetEnableTick(false);
  pFind->isInfinite_ = isInfinite;
  pFind->duration_ = duration;
  pFind->timer_ = 0;
}

void ActorFreezeManager::Defreeze(unsigned long long actorId) {
  ActorFreezeInfo* pFind = nullptr;
  if (0 == actorFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  auto iter = std::find(frozenActors_.begin(), frozenActors_.end(), actorId);
  if (iter != frozenActors_.end()) {
    frozenActors_.erase(iter);
  }

  if (nullptr != pFind->pActor_) {
    pFind->pActor_->SetEnableTick(true);
  }
}
