#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent()
    : isSkillActive_(false),
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

  isSkillActive_ = true;
  activeSkillInfo_ = pInfo;
}

void SkillComponent::DeactivateSkill() {
  isSkillActive_ = false;
  miscTemp_ = false;
}

void SkillComponent::UpdateActiveSkill() const {
  if (true == isSkillActive_ && nullptr != activeSkillInfo_->skill_) {
    activeSkillInfo_->skill_();
  }
}

bool SkillComponent::GetMiscTemp() const {
  return miscTemp_;
}

void SkillComponent::SetMiscTemp(bool temp) {
  miscTemp_ = temp;
}
