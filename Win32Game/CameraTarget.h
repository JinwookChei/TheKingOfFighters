#pragma once

class CameraLimitComponent;
class Player;

class CameraTarget final
    : public Actor {
 public:
  CameraTarget();
  ~CameraTarget();

  void BeginPlay() override;

  bool Initialize(const Vector& backGroundScale, float cameraRange, float cameraHeight, Player* player1, Player* player2);

  void Tick(unsigned long long curTick) override;

 private:
  Vector backGroundScale_;

  float cameraRange_;

  float cameraHeight_;

  Player* pPlayer1_;

  Player* pPlayer2_;

  Vector player1StartPosition_;

  Vector player2StartPosition_;

  
};