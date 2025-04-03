#pragma once

class Chang
    : public Actor {
 public:
  Chang();

  ~Chang();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void RenderUpdate();

  void CommendUpdate();

  void CollisionUpdate(); 

 private:
  ImageRenderer* pRender_;

    CollisionComponent* pHitBoxTop_;

  CollisionComponent* pHitBoxBottom_;

  CollisionComponent* pAttackBox_;

  CollisionComponent* pPushBox_;

  CollisionComponent* pGrabBox_;

  CommendComponent* pCommendComponent_;

  class BattleComponent* pBattle_;
};