#pragma once

class CameraTarget final
    : public Actor {
 public:
  CameraTarget();
  ~CameraTarget();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  bool Initialize(float cameraMinHeight, float cameraMaxHeight, float cameraMinWidth, float cameraMaxWidth);

  void OnCameraShake(unsigned long long duration);

  void OffCameraShake();

  float GetCameraMinHeight() const;

  float GetCameraMaxHeight() const;

  float GetCameraMinWidth() const;

  float GetCameraMaxWidth() const;

 private:
  bool onCameraShake_;

  unsigned long long cameraShakeDuration_;

  unsigned long long cameraShakeTimer_;

  Vector preShakePosition_;

  float cameraMinHeight_;

  float cameraMaxHeight_;

  float cameraMinWidth_;

  float cameraMaxWidth_;
};