#include "stdafx.h"
#include "RestrictionManager.h"
#include "AnimFrozenManager.h"

RestrictionManager::RestrictionManager() {
}

RestrictionManager::~RestrictionManager() {
  for (HashTableIterator iter = restrictComponentTable_.begin(); iter != restrictComponentTable_.end();) {
    RestrictComponentInfo* pDel = (RestrictComponentInfo*)*iter;

    iter = restrictComponentTable_.erase(iter);

    delete pDel;
  }

  restrictComponentTable_.Cleanup();
}

RestrictionManager* RestrictionManager::Instance() {
  return GRestrictionManager;
}

bool RestrictionManager::Initialize() {
  return restrictComponentTable_.Initialize(8, 8);
}

bool RestrictionManager::RegistComponent(unsigned long long actorId, RestrictionComponent* pRestrictComponent) {
  if (nullptr == pRestrictComponent) {
    return false;
  }

  RestrictComponentInfo* pFind = nullptr;
  if (0 != restrictComponentTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return false;
  }

  RestrictComponentInfo* pNewInfo = new RestrictComponentInfo;

  pNewInfo->actorId_ = actorId;
  pNewInfo->pRestrictComponent_ = pRestrictComponent;
  pNewInfo->searchHandle_ = restrictComponentTable_.Insert(pNewInfo, &pNewInfo->actorId_, 8);

  return nullptr != pNewInfo->searchHandle_;
}

void RestrictionManager::UnregistComponent(unsigned long long actorId) {
  RestrictComponentInfo* pFind = nullptr;
  if (0 == restrictComponentTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  restrictComponentTable_.Delete(pFind->searchHandle_);
}

void RestrictionManager::ApplyExternalRestrict(unsigned long long actorId, std::initializer_list<PLAYER_RESTRICT_TYPE> restrictList) {
  RestrictComponentInfo* pFind = nullptr;
  if (0 == restrictComponentTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  for (auto restrict : restrictList) {
    pFind->pRestrictComponent_->externRestrict_.restrictBitset_.set(restrict);
  }
}

void RestrictionManager::ResetExternalRestrict(unsigned long long actorId) {
  RestrictComponentInfo* pFind = nullptr;
  if (0 == restrictComponentTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  pFind->pRestrictComponent_->externRestrict_.restrictBitset_.reset();
}
