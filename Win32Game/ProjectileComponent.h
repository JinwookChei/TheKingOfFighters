#pragma once

class ProjectileComponent
    : public ActorComponent {
 public:
  ProjectileComponent();
  ~ProjectileComponent();

  void BeginPlay() override;

  bool Initialize(Level* level);

  void FireProjectile(unsigned long long projectileTag, bool isFacingRight);

  int GetActiveProjectilesCount();

  void UnLinkDestroyedProjectile(LINK_ITEM* linkItem);

  bool RegistProjectileInfo(
      unsigned long long projectileTag,
      unsigned long long imageIndex,
      AttackInfo* pAttackInfo,
      unsigned int startIndex,
      unsigned int endIndex,
      unsigned long long interval,
      bool loop,
      const Color8Bit& transColor,
      const Vector& velocity,
      const Vector& position,
      const Vector& range,
      bool isDestroyOnCollision);

  bool RegistProjectileInfo(
      unsigned long long projectileTag,
      unsigned long long imageIndex,
      AttackInfo* pAttackInfo,
      const std::vector<unsigned int>& indices,
      unsigned long long interval,
      bool loop,
      const Color8Bit& transColor,
      const Vector& velocity,
      const Vector& position,
      const Vector& range,
      bool isDestroyOnCollision);
  
  bool RegistProjectileInfo(
      unsigned long long projectileTag,
      unsigned long long imageIndex,
      AttackInfo* pAttackInfo,
      std::vector<unsigned int> indices,
      std::vector<unsigned long long> intervals,
      bool loop,
      Color8Bit transColor,
      const Vector& velocity,
      const Vector& position,
      const Vector& range,
      bool isDestroyOnCollision);

 private:
  Level* level_;

  HashTable projectileTable_;

  LINK_ITEM* activeProjectilesHead_;

  LINK_ITEM* activeProjectilesTail_;
  
};
