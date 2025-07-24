#pragma once


class Iori
    : public KOFPlayer {
 public:
  Iori();

  ~Iori();

  void BeginPlay() override;

  void Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) override;

  void CompareInputBitset() override;

};