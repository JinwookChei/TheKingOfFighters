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
class KOFPlayer;

class Chang
    : public KOFPlayer {
 public:
  Chang();

  ~Chang();

  void BeginPlay() override;

  void Initialize(const Vector& position, bool useCameraPosition, bool flip) override;

  void Tick(unsigned long long curTick) override;

  void HitEvent(float damage, const Vector& knockBackForce);

  void InputUpdate(unsigned long long curTick) override;

  void CommendUpdate() override;

  void SkillUpdate();

 private:
  unsigned int prevImageIndex;
};