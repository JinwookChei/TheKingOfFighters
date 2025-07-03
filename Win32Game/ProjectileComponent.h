#pragma once

class ProjectileComponent
    : public ActorComponent {
 public:
  ProjectileComponent();
  ~ProjectileComponent();

  void BeginPlay() override;

  bool Initialize(Level* level);

  void FireProjectile(unsigned long long projectileTag);

  int GetActiveProjectilesCount();

  void UnLinkDestroyedProjectile(LINK_ITEM* linkItem);
  
  bool RegistProjectileInfo(unsigned long long projectileTag, AttackInfo* pAttackInfo, const Vector& spawnPosition, bool isDestroyOnCollision, int miscValue = 0);

 private:
  Level* level_;

  HashTable projectileTable_;

  LINK_ITEM* activeProjectilesHead_;

  LINK_ITEM* activeProjectilesTail_;
  
};
