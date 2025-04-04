#pragma once

enum IoriAnim {
  IORIANIM_None = 0,
  IORIANIM_IDle,
  IORIANIM_Seat,
  IORIANIM_Walk,
  IORIANIM_BackWalk,
  IORIANIM_Kick,
  IORIANIM_SUperKick
};

class Iori
    : public Actor {
 public:
  Iori();

  ~Iori();

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