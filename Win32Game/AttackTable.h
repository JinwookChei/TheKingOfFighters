#pragma once

enum ATTACK_TYPE {
  ATTYPE_None = -1,
  ATTYPE_NormalAttack = 0,
  ATTYPE_LowAttack,
  ATTYPE_HighAttack,
  ATTYPE_StrongAttack,
  ATTYPE_Max
};

enum ATTACK_ELEMENT_TYPE {
  ELMTTYPE_None = -1,
  ELMTTYPE_Normal = 0,
  ELMTTYPE_Fire,
  ELMTTYPE_BlueFlame,
  ELMTTYPE_Thunder,
  ELMTTYPE_Max
};

struct AttackInfo {
  unsigned long long attackTableKey_ = 0;
  ATTACK_TYPE attackType_ = ATTYPE_None;
  ATTACK_ELEMENT_TYPE elementType_ = ELMTTYPE_None;
  EFFECT_KEY effectKey_ = EFKEY_None; 
  float damage_ = 0.0f;
  Vector knockBackForce_ = {0.0f, 0.0f};
  void* searchHandle_ = nullptr;
};

class AttackTable
    : public ActorComponent {
 public:
  AttackTable();
  ~AttackTable();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initailize();

  bool RegistAttackInfo(unsigned long long attackTableKey, ATTACK_TYPE attackType, ATTACK_ELEMENT_TYPE elementType, EFFECT_KEY effectKey, float damage, Vector knockBackForce);

  bool SearchAttackInfo(unsigned long long attackTableKey, AttackInfo** outSearchResult);

  void CalculateDamage();

 private:
  HashTable attackTable_;
};
