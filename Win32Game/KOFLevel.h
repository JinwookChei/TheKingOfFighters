#pragma once

//class ActorFreezeManager;
class RestrictionManager;
class Mouse;
class BackGround;
class ScreenMask;
class CameraTarget;
class KOFPlayer;
class UI;
class Notification;

enum GameStatus {
  GAMESTATUS_None = 0,
  GAMESTATUS_GameReady,
  GAMESTATUS_GameInProgress,
  GAMESTATUS_GameEnd
};

class KOFLevel final
    : public Level {
 public:
  KOFLevel();

  ~KOFLevel();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  void SwapPosition();

  //ActorFreezeManager* GetActorFreezeManager() const;

  RestrictionManager* GetRestrictionManager() const;

  CameraTarget* GetCameraTarget() const;

  ScreenMask* GetBackGroundMask() const;

  float GetLevelLeftBoundary() const;

  float GetLevelRightBoundary() const;

  float GetScreenBoundaryWidth() const;

  void InitReadyGame();

  void ReadyGame(unsigned long long deltaTick);

  void InitInProgressGame();

  void InProgressGame(unsigned long long deltaTick);

  void InitEndGame();

  void EndGame(unsigned long long deltaTick);

 private:
  //ActorFreezeManager* pActorFreezeManager_;

  RestrictionManager* pRestrictionManager_;

  SoundChannel backGroundSoundChannel_;

  CameraTarget* pCamera_;

  Mouse* pMouse_;

  BackGround* pBackGround_;

  ScreenMask* pBackGroundMask_;

  ScreenMask* pScreenMask_;

  KOFPlayer* pPlayer1_;

  KOFPlayer* pPlayer2_;

  UI* HUD_;

  UI* systemUI_;

  Notification* readyNotification_;

  Notification* goNotification_;

  Notification* koNotification_;

  GameStatus gameStatus_;

  unsigned long long acuumDeltaTick_;

  Vector player1SpawnPostion_;

  Vector player2SpawnPostion_;

  const float levelBoundaryMargin_ = 10.0f;

  float levelLeftBoundary_;

  float levelRightBoundary_;

  float screenBoundaryWidth_;

  const float groundHeight_ = 1000;
};