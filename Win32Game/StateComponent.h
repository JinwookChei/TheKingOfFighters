#pragma once


struct State {
  unsigned long long stateTag_ = 0;

  bool canMove_ = true;

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

  bool RegistState(unsigned long long stateTag, bool canMove);

  void ChangeState(unsigned long long stateTag);

  State GetCurState() const;

 private:
  State curState_;

  HashTable stateTable_;
};