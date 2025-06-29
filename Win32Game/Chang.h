#pragma once

class Chang
    : public KOFPlayer {
 public:
  Chang();

  ~Chang();

  void BeginPlay() override;

  void Initialize(const Vector& position, bool useCameraPosition, bool flip, KOFPlayer* opponentPlayer) override;

  //void Tick(unsigned long long curTick) override;

  void CompareInputBitset() override;

 private:
};