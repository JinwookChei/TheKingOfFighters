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
    : public Player {
 public:
  Iori();

  ~Iori();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void InputUpdate() override;

  void CommendUpdate() override;

  void SkillUpdate();

  void CollisionBoundUpdate() override;

  bool CollisionHitUpdate() override;

  void Flip() override;


  // Command Skills
  void CommandSkill_1() override;

 private:
  unsigned int prevImageIndex;

};