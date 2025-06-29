#pragma once


enum IORI_ANIM_TYPE : unsigned long long {
  IORI_ANIMTYPE_108ShikiYamiBarai = PLAYER_ANIMTYPE_Max + 1ULL,
  IORI_ANIMTYPE_GaishikiMutan_1,
  IORI_ANIMTYPE_GaishikiMutan_2,
  IORI_ANIMTYPE_Shinigami,
  IORI_ANIMTYPE_HyakushikiOniyaki,
  IORI_ANIMTYPE_127ShikiAoiHana_1,
  IORI_ANIMTYPE_127ShikiAoiHana_2,
  IORI_ANIMTYPE_127ShikiAoiHana_3,
  IORI_ANIMTYPE_UltimateCasting,
  IORI_ANIMTYPE_1211ShikiYaOtome_1,
  IORI_ANIMTYPE_1211ShikiYaOtome_2,
  IORI_ANIMTYPE_1211ShikiYaOtome_3,
  IORI_ANIMTYPE_1211ShikiYaOtome_4,
  IORI_ANIMTYPE_1211ShikiYaOtome_5,
  IORI_ANIMTYPE_1211ShikiYaOtome_6,
  IORI_ANIMTYPE_1211ShikiYaOtome_7,
  IORI_ANIMTYPE_1211ShikiYaOtome_8,
  IORI_ANIMTYPE_1211ShikiYaOtome_9
};

enum IORI_SKILL {
  IORI_SKILL_None = -1,
  IORI_SKILL_108ShikiYamiBarai = 0,
  IORI_SKILL_GaishikiMutan,
  IORI_SKILL_Shinigami,
  IORI_SKILL_HyakushikiOniyaki,
  IORI_SKILL_127ShikiAoiHana,
  IORI_SKILL_1211ShikiYaOtome,
  IORI_SKILL_Max
};

enum IORI_PROJECTILE {
  IORI_PROJECTILE_108ShikiYamiBarai = 0,
  IORI_PROJECTILE_HyakushikiOniyaki_Low,
  IORI_PROJECTILE_HyakushikiOniyaki_High
};


class Iori
    : public KOFPlayer {
 public:
  Iori();

  ~Iori();

  void BeginPlay() override;

  void Initialize(const Vector& position, bool useCameraPosition, bool flip, KOFPlayer* opponentPlayer) override;

  //void Tick(unsigned long long curTick) override;

  void CompareInputBitset() override;

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
};