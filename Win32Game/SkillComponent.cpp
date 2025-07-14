#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent()
    : onSkillActive_(false),
      miscTemp_(false),
      activeSkillInfo_(nullptr) {
}

SkillComponent::~SkillComponent() {
  for (HashTableIterator iter = skillTable_.begin(); iter != skillTable_.end();) {
    SkillInfo* pDel = (SkillInfo*)*iter;
    iter = skillTable_.erase(iter);

    delete pDel;
  }

  skillTable_.Cleanup();
}

void SkillComponent::BeginPlay() {
}

void SkillComponent::Tick(unsigned long long deltaTick) {
}

bool SkillComponent::Initialize() {
  return skillTable_.Initialize(8, 8);
}

void SkillComponent::ActivateSkill(unsigned long long skillTag) {
  SkillInfo* pInfo;
  if (0 == skillTable_.Select((void**)&pInfo, 1, &skillTag, 8)) {
    return;
  }

  onSkillActive_ = true;
  miscTemp_ = false;
  activeSkillInfo_ = pInfo;
}

void SkillComponent::DeactivateSkill() {
  onSkillActive_ = false;
  miscTemp_ = false;
  activeSkillInfo_ = nullptr;
}

void SkillComponent::UpdateActiveSkill() const {
  if (true == onSkillActive_ && nullptr != activeSkillInfo_->skill_) {
    activeSkillInfo_->skill_();
  }
}

bool SkillComponent::GetMiscTemp() const {
  return miscTemp_;
}

void SkillComponent::SetMiscTemp(bool temp) {
  miscTemp_ = temp;
}

SkillInfo* SkillComponent::GetCurrentActiveSkillInfo() {
  return activeSkillInfo_;
}
