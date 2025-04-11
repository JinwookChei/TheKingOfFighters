#pragma once
#include <vector>

class CommandComponent;
class ProjectileComponent;

class Player
    : public Actor {
 public:
  Player();

  ~Player();

  virtual void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  virtual void InputUpdate();

  virtual void CommendUpdate();

  virtual void CollisionBoundUpdate();

  virtual bool CollisionHitUpdate();

  virtual void Flip();

  // Command Skill
  virtual void CommandSkill_1() {};

  virtual void CommandSkill_2() {};

  virtual void CommandSkill_3() {};

  virtual void CommandSkill_4() {};

  virtual void CommandSkill_5() {};

 protected:
  ImageRenderer* pRender_;

  CollisionComponent* pHitBoxTop_;

  CollisionComponent* pHitBoxBottom_;

  CollisionComponent* pAttackBox_;

  CollisionComponent* pPushBox_;

  CollisionComponent* pGrabBox_;

  CommandComponent* pCommandComponent_;

  ProjectileComponent* pProjectileComponent_;

  int animState_;

  int isFlip_;
};