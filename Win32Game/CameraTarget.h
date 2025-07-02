#pragma once

class CameraTarget final
    : public Actor {
 public:
  CameraTarget();
  ~CameraTarget();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  bool Initialize(float cameraMinHeight, float cameraMaxHeight, float cameraMinWidth, float cameraMaxWidth);

  float GetCameraMinHeight() const;

  float GetCameraMaxHeight() const;

  float GetCameraMinWidth() const;

  float GetCameraMaxWidth() const;

 private:
  float cameraMinHeight_;

  float cameraMaxHeight_;

  float cameraMinWidth_;

  float cameraMaxWidth_;
};