#pragma once

class CameraLimitComponent final
    : public SceneComponent {
 public:
  CameraLimitComponent();
  ~CameraLimitComponent();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;
};
