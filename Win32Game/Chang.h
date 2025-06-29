#pragma once

class Chang
    : public KOFPlayer {
 public:
  Chang();

  ~Chang();

  void BeginPlay() override;

  void Initialize(const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) override;

  void CompareInputBitset() override;

 private:
};