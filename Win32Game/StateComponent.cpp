#include "stdafx.h"
#include "StateComponent.h"

StateComponent::StateComponent() {
}

StateComponent::~StateComponent() {
  for (HashTableIterator iter = stateTable_.begin(); iter != stateTable_.end();) {
    State* pDel = (State*)*iter;

    iter = stateTable_.erase(iter);

    delete pDel;
  }

  stateTable_.Cleanup();
}

bool StateComponent::Initialize() {
  return stateTable_.Initialize(8, 8);
}

void StateComponent::BeginPlay() {
}

void StateComponent::Tick(unsigned long long deltaTick) {
}

bool StateComponent::RegistState(unsigned long long stateTag, std::initializer_list<PLAYER_STATE> playerStateList, bool canInput) {
  State* pFind = nullptr;

  if (0 != stateTable_.Select((void**)&pFind, 1, &stateTag, 8)) {
    return false;
  }

  State* pState = new State;
  pState->stateTag_ = stateTag;
  pState->canInput_ = canInput;

  std::bitset<PS_Max> temp;
  for (auto state : playerStateList) {
    temp.set(state);
  }
  pState->playerStateBitset_ = temp;

  pState->searchHandle_ = stateTable_.Insert(pState, &pState->stateTag_, 8);

  return nullptr != pState->searchHandle_;
}

void StateComponent::ChangeState(unsigned long long stateTag) {
  State* pState = nullptr;
  if (0 == stateTable_.Select((void**)&pState, 1, &stateTag, 8)) {
    return;
  }

  curState_.stateTag_ = pState->stateTag_;
  curState_.playerStateBitset_ = pState->playerStateBitset_;
  curState_.canInput_ = pState->canInput_;
  curState_.searchHandle_ = pState->searchHandle_;
}

void StateComponent::AddState(std::initializer_list<PLAYER_STATE> playerStateList) {
  for (auto state : playerStateList) {
    curState_.playerStateBitset_.set(state);
  }
}

State StateComponent::GetCurState() const {
  return curState_;
}

unsigned long long StateComponent::GetCurAnimState() const {
  return curState_.stateTag_;
}

bool StateComponent::EqualPlayerState(std::initializer_list<PLAYER_STATE> playerStateList) {
  std::bitset<PS_Max> temp;
  for (auto state : playerStateList) {
    temp.set(state);
  }
  return curState_.playerStateBitset_ == temp;
}

bool StateComponent::ContainPlayerState(std::initializer_list<PLAYER_STATE> playerStateList) {
  for (auto state : playerStateList) {
    if (curState_.playerStateBitset_.test(state)) {
      return true;
    }
  }
  return false;
}

// PLAYERSTATE StateComponent::GetPlayerState() const {
//   return curState_.playerState_;
// }

bool StateComponent::CanInput() const {
  return curState_.canInput_;
}
