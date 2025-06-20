#pragma once

class BlackBoard
    : public Actor {
 public:
  BlackBoard();

  ~BlackBoard();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

 private:
  ImageRenderer* pRender_;
};