#pragma once

enum ChangAnimStat
{
    CHAS_None = 0,
    CHAS_Idel,
    CHAS_Hit,
    CHAS_MAX
};

class Chang
    : public Actor {
 public:
  Chang();

  ~Chang();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void InputUpdate();

  void CommendUpdate();

  void CollisionBoundUpdate();

  bool CollisionHitUpdate();

 private:
  ImageRenderer* pRender_;

  CollisionComponent* pHitBoxTop_;

  CollisionComponent* pHitBoxBottom_;

  CollisionComponent* pAttackBox_;

  CollisionComponent* pPushBox_;

  CollisionComponent* pGrabBox_;

  CommendComponent* pCommendComponent_;

  //StateComponent* pStateComponent_;

  ChangAnimStat animState_;

  class BattleComponent* pBattle_;
};