#pragma once

struct State {
  unsigned long long stateTag_ = 0;

  bool canMove_ = true;

  bool canChangeAnimState_ = true;

  void* searchHandle_ = nullptr;
};

class StateComponent
    : public ActorComponent
{
 public:
  StateComponent();

  ~StateComponent();

  bool Initialize();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool RegistState(unsigned long long stateTag, bool canMove, bool canChangeAnimState);

  void ChangeState(unsigned long long stateTag);

  void ResetState();

  State GetCurState() const;

  unsigned long long GetCurAnimState() const;

  bool CanMove() const;

  bool CanChangeAnimState() const;

 private:
  State curState_;

  HashTable stateTable_;
};