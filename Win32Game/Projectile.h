#pragma once

struct ProjectileInfo {
  unsigned long long projectileTag_ = 0;

  unsigned long long imageIndex_ = 0;

  std::vector<unsigned int> indices_;

  std::vector<unsigned long long> intervals_;

  bool loop_ = false;

  Color8Bit transColor_;

  Vector velocity_ = {0.0f, 0.0f};

  Vector position_ = {0.0f, 0.0f};

  Vector range_ = {0.0f, 0.0f};

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

  ProjectileInfo GetProjectileInfo() const;

  void SetProjectileInfo(const ProjectileInfo& projectileInfo);

  void CollisionUpdate();

 private:
  Actor* owner_;

  ImageRenderer* pRender_;

  CollisionComponent* pCollisionBox_;

  ProjectileInfo projectileInfo_;

  Vector accumulRange_;

  long long curTime_;

  int curFrame_;

  bool isFirstTick_;
};
