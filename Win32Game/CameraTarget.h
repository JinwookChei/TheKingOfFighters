#pragma once

class CameraLimitComponent;
class Player;

class CameraTarget final
    : public Actor {
 public:
  CameraTarget();
  ~CameraTarget();

  void BeginPlay() override;

  bool Initialize(const Vector& backGroundScale, float cameraRange, float cameraHeight);

  void Tick(unsigned long long curTick) override;
    

  void BindPlayer1(Player* player1);

  void BindPlayer2(Player* player2);

 private:
  Vector backGroundScale_;

  float cameraRange_;

  float cameraHeight_;

  Player* pPlayer1_;

  Player* pPlayer2_;

  
};