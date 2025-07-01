#pragma once
#include <bitset>
#include <initializer_list>

enum PLAYER_STATE {
  PS_None = 0,
  PS_Idle,
  PS_Move,
  PS_Run,
  PS_Jump,
  PS_Dash,
  PS_Rolling,
  PS_Seat,
  PS_Attack,
  PS_Hit,
  PS_Guard,
  PS_SkillCasting,
  PS_Max
};

struct State {
  unsigned long long stateTag_ = 0;

  std::bitset<PS_Max> playerStateBitset_;

  bool canInput_ = true;

  void* searchHandle_ = nullptr;
};

class StateComponent
    : public ActorComponent {
 public:
  StateComponent();

  ~StateComponent();

  bool Initialize();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool RegistState(unsigned long long stateTag, std::initializer_list<PLAYER_STATE> playerStateList, bool canInput);

  void ChangeState(unsigned long long stateTag);

  State GetCurState() const;

  unsigned long long GetCurAnimState() const;

  bool EqualPlayerState(std::initializer_list<PLAYER_STATE> playerStateList);

  bool ContainPlayerState(std::initializer_list<PLAYER_STATE> playerStateList);

  bool CanInput() const;

 private:
  State curState_;

  HashTable stateTable_;
};