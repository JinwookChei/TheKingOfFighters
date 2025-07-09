#pragma once
enum AI_BEHABIOR_STATE : unsigned long long {
  AI_BEHABIOR_Idle = 0ULL,
  AI_BEHABIOR_MoveFront,
  AI_BEHABIOR_Max
};

struct AIBehabiorInfo {
  AI_BEHABIOR_STATE behabiorTag_ = AI_BEHABIOR_Idle;

  unsigned long long behabiorDuration_ = 0;

  void* searchHandle_ = nullptr;
};

class AIBehaviorStateMachine
    : public ActorComponent {
 public:
  AIBehaviorStateMachine();

  ~AIBehaviorStateMachine();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize(); 

  bool RegistBehabior(AI_BEHABIOR_STATE behabiorTag, unsigned long long behabiorDuration);

  bool SearchBehabior(AI_BEHABIOR_STATE behabiorTag, AIBehabiorInfo** outBehabiorInfo);

  void ChangeBehabiorState(AI_BEHABIOR_STATE behabiorTag);

  void DecideBehabior(unsigned long long deltaTick);

  AI_BEHABIOR_STATE GetCurBehabior() const;
  
 private:
  HashTable behabiorTable_;

  AIBehabiorInfo* curBehabiorInfo_ = nullptr;

  unsigned long long behabiorTimer_ = 0;
};
