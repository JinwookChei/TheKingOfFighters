#pragma once
#include <functional>


enum AI_BEHABIOR_STATE : unsigned long long {
  AI_BEHABIOR_Idle = 0ULL,
  AI_BEHABIOR_MoveFront,
  AI_BEHABIOR_MoveBack,
  AI_BEHABIOR_Max
};

struct AIBehabiorInfo {
  AI_BEHABIOR_STATE behabiorTag_ = AI_BEHABIOR_Idle;

  unsigned long long behabiorDuration_ = 0;

  unsigned long long coolTime_ = 0;

  unsigned long long coolTimer_ = 0;

  bool isCoolTimeActive_ = false;

  bool currentRunning_ = false;

  std::function<void()> behabior_ = nullptr;

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

  template<typename T>
  bool RegistBehabior(AI_BEHABIOR_STATE behabiorTag, unsigned long long behabiorDuration, unsigned long long coolTime,  void (T::*funcPtr)(), T* owner) {
    AIBehabiorInfo* pFind;
    if (0 != behabiorTable_.Select((void**)&pFind, 1, &behabiorTag, 8)) {
      return false;
    }

    AIBehabiorInfo* pInfo = new AIBehabiorInfo;
    pInfo->behabiorTag_ = behabiorTag;
    pInfo->behabiorDuration_ = behabiorDuration;
    pInfo->coolTime_ = coolTime;
    pInfo->coolTimer_ = 0;
    pInfo->isCoolTimeActive_ = false;
    pInfo->behabior_ = std::bind(funcPtr, owner);
    pInfo->searchHandle_ = behabiorTable_.Insert(pInfo, &pInfo->behabiorTag_, 8);

    return nullptr != pInfo->searchHandle_;
  }

  bool SearchBehabior(AI_BEHABIOR_STATE behabiorTag, AIBehabiorInfo** outBehabiorInfo);

  void ChangeBehabiorState(AI_BEHABIOR_STATE behabiorTag);

  void DecideBehabior(unsigned long long deltaTick);

  void UpdateCoolTime(unsigned long long deltaTick);

  void UpdateBehabior();

  AI_BEHABIOR_STATE GetCurBehabior() const;
  
 private:
  HashTable behabiorTable_;

  AIBehabiorInfo* curBehabiorInfo_ = nullptr;

  unsigned long long behabiorTimer_ = 0;
};
