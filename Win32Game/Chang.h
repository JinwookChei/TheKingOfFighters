#pragma once

class Chang
    : public Actor {
 public:
  Chang();

  ~Chang();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

 private:
  ImageRenderer* pRender_;

  class BattleComponent* pBattle_;
};