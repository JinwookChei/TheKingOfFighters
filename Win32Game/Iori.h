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
  IORI_ANIMTYPE_1211ShikiYaOtome_0,
  IORI_ANIMTYPE_1211ShikiYaOtome_1,
  IORI_ANIMTYPE_1211ShikiYaOtome_2,
  IORI_ANIMTYPE_1211ShikiYaOtome_3,
  IORI_ANIMTYPE_1211ShikiYaOtome_4,
  IORI_ANIMTYPE_1211ShikiYaOtome_5,
  IORI_ANIMTYPE_1211ShikiYaOtome_6,
  IORI_ANIMTYPE_1211ShikiYaOtome_7,
  IORI_ANIMTYPE_1211ShikiYaOtome_8,
  IORI_ANIMTYPE_1211ShikiYaOtome_9,
  IORI_ANIMTYPE_Ura306shikiShika_1,
  IORI_ANIMTYPE_Ura306shikiShika_2,
  IORI_ANIMTYPE_Ura306shikiShika_3
};

class Iori
    : public KOFPlayer {
 public:
  Iori();

  ~Iori() override;

  void BeginPlay() override;

  void Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) override;

  void CompareInputBitset() override;

};