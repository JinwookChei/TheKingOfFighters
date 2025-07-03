#pragma once

class Iori
    : public KOFPlayer {
 public:
  Iori();

  ~Iori();

  void BeginPlay() override;

  void Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) override;

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

  void HyakushikiOniyaki();

  void ShikiAoiHana127();

  void ShikiYaOtome1211();
};