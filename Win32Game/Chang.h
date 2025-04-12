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
class Player;

class Chang
    : public Player {
 public:
  Chang();

  ~Chang();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void InputUpdate() override;

  void CommendUpdate() override;

  void CollisionBoundUpdate() override;

  bool CollisionHitUpdate() override;

  void Flip() override;
};