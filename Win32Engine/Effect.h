#pragma once
#include "Actor.h"

class Effect
    : public Actor {
 public:
  Effect();

  ~Effect();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;
    
  Vector GetVelocity() const;

  void SetVelocity(Vector velocity);

 protected:

 private:
  ImageRenderer* pRender_;

  CollisionComponent* pCollision_;

  Vector velocity_;

  Vector reach_;


};
