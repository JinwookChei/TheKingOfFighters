#pragma once

class Mouse;
class BackGround;
class BlackBoard;
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

  BlackBoard* GetBlackBoard() const; 

  void FreezeActors(std::vector<Actor*> actors, unsigned long long freezeDuration);

  void DefreezeActors();

  void CalculateFreeze(unsigned long long deltaTick);

 private:
  const Vector levelLocalScale_{4.5f, 4.5f};
  
  Vector backGroundImageScale_;

  SoundChannel* channel_;

  CameraTarget* pCamera_;

  Mouse* pMouse_;

  BackGround* pBackGround_;

  BlackBoard* pBlackBoard_;

  KOFPlayer* pPlayer1_;

  KOFPlayer* pPlayer2_;

  UI* HUD_;

  Vector player1SpawnPostion_;

  Vector player2SpawnPostion_;

  bool OnFreezeTimer_;

  std::vector<Actor*> freezedActors_;

  unsigned long long freezeDuration_;

  unsigned long long freezeTiemr_;
};