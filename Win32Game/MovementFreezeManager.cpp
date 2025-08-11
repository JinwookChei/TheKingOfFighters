#include "stdafx.h"
#include "MovementComponent.h"
#include "MovementFreezeManager.h"

MovementFreezeManager::MovementFreezeManager() {
}

MovementFreezeManager::~MovementFreezeManager() {
  for (HashTableIterator iter = movementFreezeTable_.begin(); iter != movementFreezeTable_.end();) {
    RestrictComponentInfo* pDel = (RestrictComponentInfo*)*iter;

    iter = movementFreezeTable_.erase(iter);

    delete pDel;
  }

  movementFreezeTable_.Cleanup();
}

void MovementFreezeManager::BeginPlay() {
}

void MovementFreezeManager::Tick(unsigned long long deltaTick) {
  for (int i = 0; i < frozenActors_.size(); ++i) {
    unsigned long long actorId = frozenActors_[i];
    MovementFreezeInfo* pFind = nullptr;
    if (0 == movementFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
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

bool MovementFreezeManager::Initialize() {
  return movementFreezeTable_.Initialize(8, 8);
}

bool MovementFreezeManager::RegistComponent(unsigned long long actorId, MovementComponent* pMovementComponent) {
  if (nullptr == pMovementComponent) {
    return false;
  }

  MovementFreezeInfo* pFind = nullptr;
  if (0 != movementFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return false;
  }

  MovementFreezeInfo* pNewInfo = new MovementFreezeInfo;
  pNewInfo->actorId_ = actorId;
  pNewInfo->pMovementComponent_ = pMovementComponent;
  pNewInfo->searchHandle_ = movementFreezeTable_.Insert(pNewInfo, &pNewInfo->actorId_, 8);

  return nullptr != pNewInfo->searchHandle_;
}

void MovementFreezeManager::UnregistComponent(unsigned long long actorId) {
  auto iter = std::find(frozenActors_.begin(), frozenActors_.end(), actorId);
  if (iter != frozenActors_.end()) {
    frozenActors_.erase(iter);
  }

  MovementFreezeInfo* pFind = nullptr;
  if (0 == movementFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  movementFreezeTable_.Delete(pFind->searchHandle_);
}

void MovementFreezeManager::ApplyFreeze(unsigned long long actorId, bool isInfinite /*= true*/, unsigned long long duration /*= 0*/) {
  MovementFreezeInfo* pFind = nullptr;
  if (0 == movementFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  auto iter = std::find(frozenActors_.begin(), frozenActors_.end(), actorId);
  if (iter == frozenActors_.end()) {
    frozenActors_.push_back(actorId);
  }

  pFind->pMovementComponent_->SetEnableTick(false);
  pFind->isInfinite_ = isInfinite;
  pFind->duration_ = duration;
  pFind->timer_ = 0;
}

void MovementFreezeManager::Defreeze(unsigned long long actorId) {
  MovementFreezeInfo* pFind = nullptr;
  if (0 == movementFreezeTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  auto iter = std::find(frozenActors_.begin(), frozenActors_.end(), actorId);
  if (iter != frozenActors_.end()) {
    frozenActors_.erase(iter);
  }

  if (nullptr != pFind->pMovementComponent_) {
    pFind->pMovementComponent_->SetEnableTick(true);
  }
}