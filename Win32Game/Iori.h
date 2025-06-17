#pragma once

enum IoriAnimState {
  IOAS_MONGTAN_1 = PAS_MAX + 1,
  IOAS_MONGTAN_2,
};

enum IoriSkill {
  IOSK_NONE = -1,
  IOSK_MONGTAN = 0,
  IOSK_MAX
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

  void MongTan();

  // Sprite
  ImageRenderer* spriteRenderer_[10];

 private:
  unsigned int prevImageIndex_;

  //bool mongtan_ = false;

  bool mongtanTemp_ = false;

};