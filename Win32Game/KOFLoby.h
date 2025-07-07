#pragma once

class BackGroundMask;


class KOFLobyLevel final
    : public Level {
 public:
  KOFLobyLevel();
  ~KOFLobyLevel();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTime) override;

  void LoadKOFImages();

  void StartGame();


private:
  bool onStartGame_;

  Mouse* pMouse_;

  BackGroundMask* pBackGroundMask_;

  UI* pressEnter_;

  float pressEntetBlinkPeriod;

  float pressEnterBlinkTime;
};