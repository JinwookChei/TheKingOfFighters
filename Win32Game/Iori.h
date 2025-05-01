#pragma once

//enum IoriAnimState {
//  IOAS_None = 0,
//  IOAS_IDle,
//  IOAS_Seat,
//  IOAS_Walk,
//  IOAS_BackWalk,
//  IOAS_Jump,
//  IOAS_Kick,
//  IOAS_SUperKick
//};


class CommandComponent;
class ProjectileComponent;

class Iori
    : public KOFPlayer {
 public:
  Iori();

  ~Iori();

  void BeginPlay() override;

  void Initialize(const Vector& position, bool useCameraPosition, bool flip) override;

  void Tick(unsigned long long curTick) override;

  void InputUpdate(unsigned long long curTick) override;

  void CommendUpdate() override;

  void SkillUpdate();

  void CollisionBoundUpdate() override;

  bool CollisionHitUpdate() override;

  // Command Skills
  void CommandSkill_1();

  void CommandSkill_2();

  void CommandSkill_3();

 private:
  unsigned int prevImageIndex;

};