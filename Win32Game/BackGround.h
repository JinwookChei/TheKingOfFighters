#pragma once


class BackGround
    : public Actor {
 public:
  BackGround();

  ~BackGround();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

 private:
  ImageRenderer* pRender_;

};