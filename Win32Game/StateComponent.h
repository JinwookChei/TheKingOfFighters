#pragma once
enum PLAYERSTATE {
  PS_None = -1,
  PS_Idle = 0,
  PS_Move,
  PS_Jump,
  PS_Seat,
  PS_Attack,
  PS_Hit,
  PS_Guard,
  PS_Max
};

struct State {
  unsigned long long stateTag_ = 0;

  PLAYERSTATE playerState_ = PS_None;

  bool canInput_ = true;

  bool canChangeAnimState_ = true;

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

  bool RegistState(unsigned long long stateTag, PLAYERSTATE playerState, bool canInput, bool canChangeAnimState);

  void ChangeState(unsigned long long stateTag);

  State GetCurState() const;

  unsigned long long GetCurAnimState() const;

  PLAYERSTATE GetPlayerState() const; 

  bool CanInput() const;

  bool CanChangeAnimState() const;

 private:
  State curState_;

  HashTable stateTable_;
};