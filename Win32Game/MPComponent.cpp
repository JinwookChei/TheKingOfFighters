#include "stdafx.h"
#include "MPComponent.h"

MPComponent::MPComponent()
    : maxMP_(100),
      MP_(0),
      maxSkillPoint_(3),
      skillPoint_(0) {
}

MPComponent::~MPComponent() {
}

void MPComponent::BeginPlay() {
}

void MPComponent::Tick(unsigned long long deltaTick) {
}

bool MPComponent::Initialize(float maxMP) {
  maxMP_ = maxMP;
  MP_ = 0;

  return true;
}

float MPComponent::MP() const {
  return MP_;
}

float MPComponent::MaxMP() const {
  return maxMP_;
}

int MPComponent::SkillPoint() const {
  return skillPoint_;
}

int MPComponent::MaxSkillPoint() const {
  return maxSkillPoint_;
}

void MPComponent::ChargeMP(float mp) {
  if (skillPoint_ == maxSkillPoint_) {
    MP_ = 0;
    return;
  }

  MP_ += mp;
  if (MP_ >= maxMP_ && skillPoint_ < maxSkillPoint_) {
    ++skillPoint_;
    MP_ = 0;
  }
}

void MPComponent::ReduceSkillPoint() {
  --skillPoint_;

  if (skillPoint_ < 0) {
    skillPoint_ = 0;
  }
}
