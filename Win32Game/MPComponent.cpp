#include "stdafx.h"
#include "MPComponent.h"

MPComponent::MPComponent()
    : maxMP_(100),
      MP_(0) {
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

void MPComponent::ChargeMP(float mp) {
  MP_ += mp;
}
