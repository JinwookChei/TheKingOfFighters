#pragma once

class CameraTarget;
class Player;

class KOFLevel final
    : public Level {
 public:
  KOFLevel();

  ~KOFLevel();
  
  void BeginPlay() override;

  void Tick(unsigned long long dletaTick) override;

  void SwapPosition();

 private:
  CameraTarget* cameraTarget;

  Player* player1_;

  Player* player2_;

};