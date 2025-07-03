#pragma once

struct AttackInfo;
class ProjectileComponent;


struct ProjectileInfo {

  unsigned long long projectileTag_ = 0;

  AttackInfo* pAttackInfo_ = nullptr;

  Vector spawnPosition_ = {0.0f, 0.0f};

  bool isDestroyOnCollision_ = false;

  int miscValue_ = 0;

  void* searchHandle_ = nullptr;
};

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

  ProjectileInfo GetProjectileInfo() const;

  void SetProjectileInfo(const ProjectileInfo& projectileInfo);

  LINK_ITEM* GetProjectileLink();

  void UpdateCollisionBoundScale();

  void UpdateAttack();

  bool CheckAttackCollision(CollisionComponent** outTargetCollision);

  void Destroy();

 protected:
  Actor* pOwner_;

  ProjectileComponent* pOwnerProjectileComponent_;

  ImageRenderer* pRender_;

  CollisionComponent* pCollisionBox_;

  ProjectileInfo projectileInfo_;

  LINK_ITEM projectileLink_;
};
