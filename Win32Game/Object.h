#pragma once

class Object final
    : public Actor {
 public:
  Object();

  ~Object();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void MoveOffset(Vector addPosition);

  ImageRenderer* GetImageRenderer() const;

 private:
  ImageRenderer* imageRender_;

  Vector moveOffSet_;
};