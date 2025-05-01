#pragma once

class CameraLimitComponent;
class Player;

class CameraTarget final
    : public Actor {
 public:
  CameraTarget();
  ~CameraTarget();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  float GetCameraHeight() const;

 private:

  const float cameraHeight_ = 600.0f;
};