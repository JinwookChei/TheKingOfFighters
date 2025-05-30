#pragma once

enum IoriAnimState {
  IOAS_MONGTAN_1 = PAS_MAX + 1,
  IOAS_MONGTAN_2,
};

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

  void CompareInputBitset(unsigned long long curTick) override;

  void CommandUpdate() override;

  virtual void TriggerEventAtAnimationIndex() override;

  // Command Skills
  void CommandSkill_1();

  void CommandSkill_2();

  void CommandSkill_3();

  // Sprite
  ImageRenderer* spriteRenderer_[10];

 private:
  unsigned int prevImageIndex;

};