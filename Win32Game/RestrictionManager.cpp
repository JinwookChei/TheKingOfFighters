#include "stdafx.h"
#include "RestrictionManager.h"

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

void RestrictionManager::BeginPlay() {
}

void RestrictionManager::Tick(unsigned long long curTick) {
  for (HashTableIterator iter = restrictComponentTable_.begin(); iter != restrictComponentTable_.end(); ++iter) {
    RestrictComponentInfo* pInfo = (RestrictComponentInfo*)*iter;
    pInfo->pRestrictComponent_->externRestrict_.restrictBitset_.reset();
  }

  for (auto it = activeRestrictions_.begin(); it != activeRestrictions_.end();) {
    ActiveRestrictionInfo& info = *it;

    // 1. nullptr 체크 또는 제약 비트가 없는 경우 제거
    if (info.pRestrictComponent_ == nullptr || info.restrictBitset_.none()) {
      it = activeRestrictions_.erase(it);
      continue;
    }

    // 3. 제약 적용
    info.pRestrictComponent_->externRestrict_.restrictBitset_ |= info.restrictBitset_;

    // 4. 타이머 갱신 및 만료 체크
    if (!info.isInfinite_) {
      info.timer_ += curTick;
      if (info.timer_ >= info.duration_) {
        it = activeRestrictions_.erase(it);
        continue;
      }
    }
    ++it;
  }
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
  delete pFind;
}

void RestrictionManager::ApplyExternalRestrict(
    unsigned long long actorId,
    std::initializer_list<PLAYER_RESTRICT_TYPE> restrictList,
    bool isInfinite /*= true*/,
    unsigned long long duration /*= 0*/) {
  RestrictComponentInfo* pFind = nullptr;
  if (0 == restrictComponentTable_.Select((void**)&pFind, 1, &actorId, 8)) {
    return;
  }

  std::bitset<PR_Max> tempBitset;
  for (auto restrict : restrictList) {
    tempBitset.set(restrict);
  }

  ActiveRestrictionInfo activeInfo;
  activeInfo.actorId_ = actorId;
  activeInfo.pRestrictComponent_ = pFind->pRestrictComponent_;
  activeInfo.restrictBitset_ = tempBitset;
  activeInfo.isInfinite_ = isInfinite;
  activeInfo.duration_ = duration;
  activeRestrictions_.push_back(activeInfo);
}

void RestrictionManager::ReleaseExternalRestrict(unsigned long long actorId, std::initializer_list<PLAYER_RESTRICT_TYPE> restrictList) {
  for (auto& item : activeRestrictions_) {
    if (item.actorId_ == actorId) {
      for (auto type : restrictList) {
        item.restrictBitset_.reset(type);
      }
    }
  }
}

void RestrictionManager::ClearExternalRestrict(unsigned long long actorId) {
  for (auto it = activeRestrictions_.begin(); it != activeRestrictions_.end();) {
    if (actorId == it->actorId_) {
      it = activeRestrictions_.erase(it);
    } else {
      ++it;
    }
  }
}