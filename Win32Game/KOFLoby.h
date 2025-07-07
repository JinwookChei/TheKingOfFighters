#pragma once

class KOFLobyLevel final
    : public Level {
 public:
  KOFLobyLevel();
  ~KOFLobyLevel();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTime) override;
};