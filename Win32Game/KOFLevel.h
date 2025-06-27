#pragma once

class Mouse;
class BackGround;
class BackGroundMask;
class CameraTarget;
class KOFPlayer;
class UI;

class KOFLevel final
    : public Level {
 public:
  KOFLevel();

  ~KOFLevel();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  void SwapPosition();

  Vector GetBackGroundImageScale() const;

  BackGroundMask* GetBackGroundMask() const;

  void FreezeActors(std::vector<Actor*> actors, bool isInfinite, unsigned long long freezeDuration = 1000);

  void DefreezeActors();

  void CalculateFreeze(unsigned long long deltaTick);

  float GetLevelLeftBoundary() const;

  float GetLevelRightBoundary() const;

  float GetScreenBoundaryWidth() const;

 private:
  const Vector levelLocalScale_{4.5f, 4.5f};

  Vector backGroundImageScale_;

  SoundChannel* channel_;

  CameraTarget* pCamera_;

  Mouse* pMouse_;

  BackGround* pBackGround_;

  BackGroundMask* pBackGroundMask_;

  KOFPlayer* pPlayer1_;

  KOFPlayer* pPlayer2_;

  UI* HUD_;

  Vector player1SpawnPostion_;

  Vector player2SpawnPostion_;

  bool OnFreezeTimer_;

  std::vector<Actor*> freezedActors_;

  bool isFreezeInfinite_;

  unsigned long long freezeDuration_;

  unsigned long long freezeTiemr_;  

  const float levelBoundaryMargin_ = 10.0f;

  float levelLeftBoundary_;

  float levelRightBoundary_;

  float screenBoundaryWidth_;
};