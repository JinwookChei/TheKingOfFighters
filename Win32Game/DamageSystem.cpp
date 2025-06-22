#include "stdafx.h"
#include "DamageSystem.h"

DamageSystem::DamageSystem() {
}

DamageSystem::~DamageSystem() {
  for (HashTableIterator iter = damageTable_.begin(); iter != damageTable_.end();) {
    DamageInfo* pDel = (DamageInfo*)*iter;
    iter = damageTable_.erase(iter);

    delete pDel;
  }

  damageTable_.Cleanup();
}

void DamageSystem::BeginPlay() {
}

void DamageSystem::Tick(unsigned long long deltaTick) {
}

bool DamageSystem::Initailize() {
  return damageTable_.Initialize(8, 8);
}

bool DamageSystem::RegistDamageInfo(unsigned long long damageInfoTag, float damage, Vector knockBackForce) {
  DamageInfo* pFind;
  if (0 != damageTable_.Select((void**)&pFind, 1, &damageInfoTag, 8)) {
    return false;
  }

  DamageInfo* pInfo = new DamageInfo;
  pInfo->damageInfoTag = damageInfoTag;
  pInfo->damage_ = damage;
  pInfo->knockBackForce_ = knockBackForce;
  pInfo->searchHandle_ = damageTable_.Insert(pInfo, &pInfo->damageInfoTag, 8);

  return nullptr != pInfo->searchHandle_;
}

bool DamageSystem::SearchDamageInfo(unsigned long long damageInfoTag, DamageInfo** outSearchResult) {
  DamageInfo* pInfo;
  if (0 == damageTable_.Select((void**)&pInfo, 1, &damageInfoTag, 8)) {
    return false;
  }

  if (nullptr == pInfo) {
    return false;
  }

  return true;
}

void DamageSystem::CalculateDamage() {
}
