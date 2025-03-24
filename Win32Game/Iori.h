#pragma once


class Iori
    : public Actor {
 public:
  Iori();

  ~Iori();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

 private:
  ImageRenderer* pRender_;

  class BattleComponent* pBattle_;
};