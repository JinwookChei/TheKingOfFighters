#pragma once

struct AttackInfo;
class ProjectileComponent;

struct ProjectileInfo {
  unsigned long long projectileTag_ = 0;

  unsigned long long imageIndex_ = 0;

  AttackInfo* pAttackInfo_ = nullptr;

  std::vector<unsigned int> indices_;

  std::vector<unsigned long long> intervals_;

  bool loop_ = false;

  Color8Bit transColor_;

  Vector velocity_ = {0.0f, 0.0f};

  Vector position_ = {0.0f, 0.0f};

  Vector range_ = {0.0f, 0.0f};

  bool isDestroyOnCollision_ = false;

  void* searchHandle_ = nullptr;
};

class Projectile
    : public Actor {
 public:
  Projectile();
  ~Projectile();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  bool Initialize();

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

 private:
  Actor* pOwner_;

  ProjectileComponent* pOwnerProjectileComponent_;

  ImageRenderer* pRender_;

  CollisionComponent* pCollisionBox_;

  ProjectileInfo projectileInfo_;

  LINK_ITEM projectileLink_;

  Vector accumulRange_;

  long long curTime_;

  int curFrame_;

  bool isFirstTick_;
};
