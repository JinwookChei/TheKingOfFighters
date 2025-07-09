#pragma once

class ScreenMask;


class KOFLobyLevel final
    : public Level {
 public:
  KOFLobyLevel();
  ~KOFLobyLevel();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTime) override;

  //void LoadKOFImages();

  void StartGame();


private:
  bool onStartGame_;

  Mouse* pMouse_;

  ScreenMask* pScreenMask_;

  UI* pressEnter_;

  float pressEntetBlinkPeriod;

  float pressEnterBlinkTime;
};