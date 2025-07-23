#pragma once
#include "AttackTable.h"

class ProjectileComponent;

class Projectile
    : public Actor {
 public:
  Projectile();
  ~Projectile() override;

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  virtual bool Initialize();

  Actor* GetOwner() const;

  void SetOwner(Actor* owner);

  ProjectileComponent* GetOwnerProjectileComponent() const;

  void SetOwnerProjectileComponent(ProjectileComponent* ownerProjectileComponent);

  LINK_ITEM* GetProjectileLink();

  void UpdateCollisionBoundScale();

  void UpdateAttack();

  bool CheckAttackCollision(CollisionComponent** outTargetCollision);

  void Destroy();

  int MiscValue() const;

  void SetMiscValue(int miscValue);

 protected:
  Actor* pOwner_;

  ProjectileComponent* pOwnerProjectileComponent_;

  ImageRenderer* pRender_;

  CollisionComponent* pCollisionBox_;

  LINK_ITEM projectileLink_;

  AttackInfo attackInfo_;

  Vector spawnPosition_;

  bool isDestroyOnCollision_;

  int miscValue_;
};
