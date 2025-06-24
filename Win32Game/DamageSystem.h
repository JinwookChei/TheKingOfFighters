#pragma once

enum ATTACK_TYPE {
  ATTYPE_None = -1,
  ATTYPE_NormalAttack = 0,
  ATTYPE_LowAttack,
  ATTYPE_HighAttack,
  ATTYPE_StrongAttack,
  ATTYPE_FastHighAttack,
  ATTYPE_FastRowAttack,
  ATTYPE_Max
};

enum ELEMENT_TYPE {
  ELMTTYPE_None = -1,
  ELMTTYPE_Normal = 0,
  ELMTTYPE_Fire,
  ELMTTYPE_BlueFire,
  ELMTTYPE_Thunder,
  ELMTTYPE_Max
};

struct DamageInfo {
  unsigned long long damageInfoTag_ = 0;
  ATTACK_TYPE attackType_ = ATTYPE_None;
  ELEMENT_TYPE elementType_ = ELMTTYPE_None;
  float damage_ = 0.0f;
  Vector knockBackForce_ = {0.0f, 0.0f};
  void* searchHandle_ = nullptr;
};

class DamageSystem
    : public ActorComponent {
 public:
  DamageSystem();
  ~DamageSystem();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initailize();

  bool RegistDamageInfo(unsigned long long damageInfoTag, ATTACK_TYPE attackType, ELEMENT_TYPE elementType, float damage, Vector knockBackForce);

  bool SearchDamageInfo(unsigned long long damageInfoTag, DamageInfo** outSearchResult);

  void CalculateDamage();

 private:
  HashTable damageTable_;
};
