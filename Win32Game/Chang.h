#pragma once

enum ChangAnimState {
  CHAS_None = 0,
  CHAS_Idle,
  CHAS_HitTop,
  CHAS_HitBottom,
  CHAS_MAX
};

class CommandComponent;
class ProjectileComponent;

class Chang
    : public Actor {
 public:
  Chang();

  ~Chang();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void InputUpdate();

  // void AnimUpdate();

  void CommendUpdate();

  void CollisionBoundUpdate();

  bool CollisionHitUpdate();

  void Flip();

 private:
  ImageRenderer* pRender_;

  CollisionComponent* pHitBoxTop_;

  CollisionComponent* pHitBoxBottom_;

  CollisionComponent* pAttackBox_;

  CollisionComponent* pPushBox_;

  CollisionComponent* pGrabBox_;

  CommandComponent* pCommandComponent_;

  ProjectileComponent* pProjectileComponent_;

  ChangAnimState animState_;

  int isFlip_;
};