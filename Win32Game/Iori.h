#pragma once

enum IORI_ANIM_STATE {
  IOAS_108ShikiYamiBarai = PAS_MAX + 1,
  IOAS_GaishikiMutan_1,
  IOAS_GaishikiMutan_2,
  IOAS_Shinigami,
  IOAS_HyakushikiOniyaki,
  IOAS_127ShikiAoiHana_1,
  IOAS_127ShikiAoiHana_2,
  IOAS_127ShikiAoiHana_3,
  IOAS_UltimateCasting,
  IOAS_1211ShikiYaOtome,

};

enum IORI_SKILL {
  IOSK_NONE = -1,
  IOSK_108ShikiYamiBarai = 0,
  IOSK_GaishikiMutan,
  IOSK_Shinigami,
  IOSK_HyakushikiOniyaki,
  IOSK_127ShikiAoiHana,
  IOSK_1211ShikiYaOtome,
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

  void Initialize(const Vector& position, bool useCameraPosition, bool flip, KOFPlayer* opponentPlayer) override;

  void Tick(unsigned long long curTick) override;

  void UpdateInput(unsigned long long curTick) override;

  void CompareInputBitset(unsigned long long curTick) override;

  void UpdateCommand() override;

  // Command Skills
  void Command_1();

  void Command_2();

  void Command_3();

  void Command_4();

  void Command_5();

  void Command_6();


  // Skills  
  void GaishikiMutan();

  void ShikiYamiBarai108();

  void Shinigami();

  void HyakushikiOniyaki();

  void ShikiAoiHana127();

  void ShikiYaOtome1211();

  // Sprite
  ImageRenderer* spriteRenderer_[10];

 private:
  //bool mongtanTemp_ = false;
};