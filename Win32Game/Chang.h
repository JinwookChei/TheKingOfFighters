#pragma once

class Chang
    : public KOFPlayer {
 public:
  Chang();

  ~Chang();

  void BeginPlay() override;

  void Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) override;

  void CompareInputBitset() override;

 private:
};