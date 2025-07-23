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

 private:
  Level* level_;

  LINK_ITEM* activeProjectilesHead_;

  LINK_ITEM* activeProjectilesTail_;
  
};
