#pragma once

//enum ChangAnimState {
//  CHAS_None = 0,
//  CHAS_Idle,
//  CHAS_HitTop,
//  CHAS_HitBottom,
//  CHAS_MAX
//};

class CommandComponent;
class ProjectileComponent;
class Player;

class Chang
    : public Player {
 public:
  Chang();

  ~Chang();

  void BeginPlay() override;

  void Initialize(const Vector& position, bool useCameraPosition, bool flip) override;

  void Tick(unsigned long long curTick) override;

  void InputUpdate(unsigned long long curTick) override;

  void CommendUpdate() override;

  void SkillUpdate();

  void CollisionBoundUpdate() override;

  bool CollisionHitUpdate() override;

  // Command Skills
  void CommandSkill_1() override;

 private:
  unsigned int prevImageIndex;
};