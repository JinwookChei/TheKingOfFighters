#pragma once

struct DamageInfo {
  unsigned long long damageInfoTag = 0;
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

  bool RegistDamageInfo(unsigned long long damageInfoTag, float damage, Vector knockBackForce);

  bool SearchDamageInfo(unsigned long long damageInfoTag, DamageInfo** outSearchResult);

  void CalculateDamage();

 private:

  HashTable damageTable_;
};
