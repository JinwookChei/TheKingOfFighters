#pragma once

enum IORI_ANIM_STATE {
  IOAS_108ShikiYamiBarai = PAS_MAX + 1,
  IOAS_GaishikiMutan_1,
  IOAS_GaishikiMutan_2,
};

enum IORI_SKILL {
  IOSK_NONE = -1,
  IOSK_108ShikiYamiBarai = 0,
  IOSK_GaishikiMutan,
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

  // Command Skills
  void Command_1();

  void Command_2();

  void Command_3();

  // Skills  
  void GaishikiMutan();

  void ShikiYamiBarai108();

  // Sprite
  ImageRenderer* spriteRenderer_[10];

 private:
  //bool mongtanTemp_ = false;
};