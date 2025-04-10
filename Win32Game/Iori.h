#pragma once

enum IoriAnimState {
  IOAS_None = 0,
  IOAS_IDle,
  IOAS_Seat,
  IOAS_Walk,
  IOAS_BackWalk,
  IOAS_Kick,
  IOAS_SUperKick
};


class CommandComponent;
class ProjectileComponent;

class Iori
    : public Actor {
 public:
  Iori();

  ~Iori();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void InputUpdate();

  //void AnimUpdate();

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

  IoriAnimState animState_;

  int isFlip_;
};