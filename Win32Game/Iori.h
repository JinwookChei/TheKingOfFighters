#pragma once


class Iori
    : public Actor {
 public:
  Iori();

  ~Iori();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void CollisionUpdate(); 

 private:
  ImageRenderer* pRender_;

  CollisionComponent* hitBoxTop_;

  CollisionComponent* hitBoxBottom_;

  CollisionComponent* attackBox_;

  CollisionComponent* pushBox_;

  CollisionComponent* grabBox_;


  class BattleComponent* pBattle_;
};