#include "stdafx.h"
#include "AttackTable.h"
#include "SoundTable.h"

AttackTable::AttackTable() {
}

AttackTable::~AttackTable() {
  for (HashTableIterator iter = attackTable_.begin(); iter != attackTable_.end();) {
    AttackInfo* pDel = (AttackInfo*)*iter;
    iter = attackTable_.erase(iter);

    delete pDel;
  }

  attackTable_.Cleanup();
}

void AttackTable::BeginPlay() {
}

void AttackTable::Tick(unsigned long long deltaTick) {
}

bool AttackTable::Initailize() {
  return attackTable_.Initialize(8, 8);
}

bool AttackTable::RegistAttackInfo(unsigned long long attackTableKey, ATTACK_TYPE attackType, ATTACK_ELEMENT_TYPE elementType, EFFECT_TYPE effectType, bool isProjectileAttack, float damage, Vector knockBackForce, float freezeTime) {
  AttackInfo* pFind;
  if (0 != attackTable_.Select((void**)&pFind, 1, &attackTableKey, 8)) {
    return false;
  }

  AttackInfo* pInfo = new AttackInfo;
  pInfo->attackTableKey_ = attackTableKey;
  pInfo->attackType_ = attackType;
  pInfo->elementType_ = elementType;
  pInfo->effectType_ = effectType;
  pInfo->isProjectileAttack_ = isProjectileAttack;
  pInfo->damage_ = damage;
  pInfo->knockBackForce_ = knockBackForce;
  pInfo->freezeTime_ = freezeTime;
  pInfo->searchHandle_ = attackTable_.Insert(pInfo, &pInfo->attackTableKey_, 8);

  return nullptr != pInfo->searchHandle_;
}

bool AttackTable::SearchAttackInfo(unsigned long long attackTableKey, AttackInfo** outSearchResult) {
  AttackInfo* pInfo;
  if (0 == attackTable_.Select((void**)&pInfo, 1, &attackTableKey, 8)) {
    return false;
  }

  if (nullptr == pInfo) {
    return false;
  }

  *outSearchResult = pInfo;
  return true;
}

void AttackTable::CalculateDamage() {
}
