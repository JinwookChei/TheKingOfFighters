#pragma once
#include <functional>
#include "KOFPlayer.h"

struct SkillInfo {
  unsigned long long skillTag_ = 0;
  std::function<void()> skill_ = nullptr;
  void* searchHandle_ = nullptr;
};

class SkillComponent
    : public ActorComponent {
 public:
  SkillComponent();

  ~SkillComponent();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize();

  template <typename T>
  bool RegistSkill(unsigned long long skillTag, void (T::*funcPtr)(), T* owner) {
    if (nullptr == funcPtr || nullptr == owner) {
      return false;
    }

    SkillInfo* pFind;
    if (0 != skillTable_.Select((void**)&pFind, 1, &skillTag, 8)) {
      return false;
    }

    SkillInfo* pInfo = new SkillInfo;
    pInfo->skillTag_ = skillTag;
    pInfo->skill_ = std::bind(funcPtr, owner);
    pInfo->searchHandle_ = skillTable_.Insert(pInfo, &pInfo->skillTag_, 8);

    return nullptr != pInfo->searchHandle_;
  }

  void ActivateSkill(unsigned long long skillTag);

  void DeactivateSkill();

  void UpdateActiveSkill() const;

  bool GetMiscTemp() const;

  void SetMiscTemp(bool temp);

 private:
  HashTable skillTable_;

  bool isSkillActive_;

  bool miscTemp_;

  SkillInfo* activeSkillInfo_;
};
