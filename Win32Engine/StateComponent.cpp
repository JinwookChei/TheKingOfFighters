#include "stdafx.h"
#include "StateComponent.h"

StateComponent::StateComponent()
    : state_(PlayerState::PS_None) {
}

StateComponent::~StateComponent() {
}

void StateComponent::BeginPlay() {
}

void StateComponent::Tick(unsigned long long curTick) {
}

int StateComponent::GetState() const {
  return state_;
}

void StateComponent::ChangeState(PlayerState state) {
  if (PlayerState::PS_MAX <= state) {
    return;
  }

  state_ = state;
}
