#include "stdafx.h"
#include "SkillDUMMY.h"

SkillDummy::SkillDummy()
    : onSkillActive_(false),
      miscTemp_(false),
      activeSkillInfo_(nullptr) {
}

SkillDummy::~SkillDummy() {
  for (HashTableIterator iter = skillTable_.begin(); iter != skillTable_.end();) {
    SkillInfo* pDel = (SkillInfo*)*iter;
    iter = skillTable_.erase(iter);

    delete pDel;
  }

  skillTable_.Cleanup();
}

void SkillDummy::BeginPlay() {
}

void SkillDummy::Tick(unsigned long long deltaTick) {
}

bool SkillDummy::Initialize() {
  return skillTable_.Initialize(8, 8);
}

void SkillDummy::ActivateSkill(unsigned long long skillTag) {
  SkillInfo* pInfo;
  if (0 == skillTable_.Select((void**)&pInfo, 1, &skillTag, 8)) {
    return;
  }

  onSkillActive_ = true;
  miscTemp_ = false;
  activeSkillInfo_ = pInfo;
}

void SkillDummy::DeactivateSkill() {
  onSkillActive_ = false;
  miscTemp_ = false;
  activeSkillInfo_ = nullptr;
}

void SkillDummy::UpdateActiveSkill() const {
  if (true == onSkillActive_ && nullptr != activeSkillInfo_->skill_) {
    activeSkillInfo_->skill_();
  }
}

bool SkillDummy::GetMiscTemp() const {
  return miscTemp_;
}

void SkillDummy::SetMiscTemp(bool temp) {
  miscTemp_ = temp;
}

SkillInfo* SkillDummy::GetCurrentActiveSkillInfo() {
  return activeSkillInfo_;
}
