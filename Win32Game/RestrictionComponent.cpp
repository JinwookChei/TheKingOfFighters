#include "stdafx.h"
#include "KOFLevel.h"
#include "RestrictionManager.h"
#include "RestrictionComponent.h"

RestrictionComponent::RestrictionComponent() {
}

RestrictionComponent::~RestrictionComponent() {
  // Manager 정리
  Level* pLevel = GetOwner()->GetLevel();
  if (nullptr != pLevel) {
    KOFLevel* pKOFLevel = (KOFLevel*)pLevel;
    RestrictionManager* pRestrictManager = pKOFLevel->GetRestrictionManager();
    if (nullptr != pRestrictManager) {
      pRestrictManager->UnregistComponent(GetOwner()->ActorId());
    }
  }

  // Table 정리.
  for (HashTableIterator iter = animStateRestrictTable_.begin(); iter != animStateRestrictTable_.end();) {
    Restriction* pDel = (Restriction*)*iter;

    iter = animStateRestrictTable_.erase(iter);

    delete pDel;
  }
  animStateRestrictTable_.Cleanup();
}

void RestrictionComponent::BeginPlay() {
}

void RestrictionComponent::Tick(unsigned long long deltaTick) {
  // CalculateFinalRestrict();
}

bool RestrictionComponent::Initialize() {
  if (false == animStateRestrictTable_.Initialize(8, 8)) {
    return false;
  }

  // Manager 등록
  Level* pLevel = GetOwner()->GetLevel();
  if (nullptr == pLevel) {
    return false;
  }
  KOFLevel* pKOFLevel = (KOFLevel*)pLevel;
  RestrictionManager* pRestrictManager = pKOFLevel->GetRestrictionManager();
  if (nullptr == pRestrictManager) {
    return false;
  }
  if (false == pRestrictManager->RegistComponent(GetOwner()->ActorId(), this)) {
    return false;
  }


  return true;
}

bool RestrictionComponent::RegistAnimStateRestrict(unsigned long long restrictTag, std::initializer_list<PLAYER_RESTRICT_TYPE> restrictList) {
  Restriction* pFind = nullptr;

  if (0 != animStateRestrictTable_.Select((void**)&pFind, 1, &restrictTag, 8)) {
    return false;
  }

  Restriction* pRestrict = new Restriction;
  pRestrict->restrictTag_ = restrictTag;

  std::bitset<PR_Max> temp;
  for (auto state : restrictList) {
    temp.set(state);
  }

  pRestrict->restrictBitset_ = temp;

  pRestrict->searchHandle_ = animStateRestrictTable_.Insert(pRestrict, &pRestrict->restrictTag_, 8);

  return nullptr != pRestrict->searchHandle_;
}

void RestrictionComponent::ChangeAnimStateRestrict(unsigned long long restrictTag) {
  Restriction* pRestrict = nullptr;
  if (0 == animStateRestrictTable_.Select((void**)&pRestrict, 1, &restrictTag, 8)) {
    return;
  }

  animStateRestrict_.restrictTag_ = pRestrict->restrictTag_;
  animStateRestrict_.restrictBitset_ = pRestrict->restrictBitset_;
  animStateRestrict_.searchHandle_ = pRestrict->searchHandle_;

  CalculateFinalRestrict();
}

void RestrictionComponent::CalculateFinalRestrict() {
  finalRestrict_.restrictBitset_ = animStateRestrict_.restrictBitset_ | externRestrict_.restrictBitset_;
}

bool RestrictionComponent::EqualFinalRestrict(std::initializer_list<PLAYER_RESTRICT_TYPE> compareRestrictList) {
  std::bitset<PR_Max> temp;
  for (auto restrict : compareRestrictList) {
    temp.set(restrict);
  }
  return finalRestrict_.restrictBitset_ == temp;
}

bool RestrictionComponent::ContainFinalRestrict(std::initializer_list<PLAYER_RESTRICT_TYPE> compareRestrictList) {
  for (auto restrict : compareRestrictList) {
    if (false == finalRestrict_.restrictBitset_.test(restrict)) {
      return false;
    }
  }
  return true;
}

bool RestrictionComponent::CanInput() const {
  return !finalRestrict_.restrictBitset_.test({PR_LockInput});
}
