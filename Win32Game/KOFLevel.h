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

  void Tick(unsigned long long dletaTick) override;

  void SwapPosition();

  Vector GetBackGroundImageScale() const;

  BlackBoard* GetBlackBoard() const; 

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
};