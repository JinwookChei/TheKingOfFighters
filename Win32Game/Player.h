#pragma once
#include <vector>

class MovementComponent;
class CommandComponent;
class ProjectileComponent;

class Player
    : public Actor {
 public:
  Player();

  ~Player();

  virtual void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  virtual void Initialize(const Vector& position, bool useCameraPosition, bool flip);

  virtual void InputUpdate(unsigned long long curTick);

  virtual void CommendUpdate();

  virtual void CollisionBoundUpdate();

  virtual bool CollisionHitUpdate();

  virtual Vector CharacterScale() const;

  virtual void SetCharacterScale(const Vector& scale);

  virtual void Flip(bool flip);

  // Command Skill
  virtual void CommandSkill_1() {};

  virtual void CommandSkill_2() {};

  virtual void CommandSkill_3() {};

  virtual void CommandSkill_4() {};

  virtual void CommandSkill_5() {};

 protected:

  ImageRenderer* pRender_;

  MovementComponent* pMovementComponent_;

  CollisionComponent* pHitBoxTop_;

  CollisionComponent* pHitBoxBottom_;

  CollisionComponent* pAttackBox_;

  CollisionComponent* pPushBox_;

  CollisionComponent* pGrabBox_;

  CommandComponent* pCommandComponent_;

  ProjectileComponent* pProjectileComponent_;

  int animState_;

  Vector characterScale_;

  int isFlip_;
  
};