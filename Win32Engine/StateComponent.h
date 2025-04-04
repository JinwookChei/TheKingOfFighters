#pragma once
#include "ActorComponent.h"


//enum PlayerState
//{
//    PS_None = -1,
//    PS_Idle = 0,
//    PS_Hit,
//    PS_Attack,
//    PS_MAX
//};


class StateComponent
    : public ActorComponent {
 public:
  StateComponent();
  ~StateComponent();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  int GetState() const;

  void ChangeState(int state);

 private:
  //int state_;
};
