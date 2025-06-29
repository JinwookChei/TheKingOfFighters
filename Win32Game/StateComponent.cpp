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

bool StateComponent::RegistState(unsigned long long stateTag, PLAYERSTATE playerState, bool canInput/*, bool canChangeAnimState*/) {
  State* pFind = nullptr;

  if (0 != stateTable_.Select((void**)&pFind, 1, &stateTag, 8)) {
    return false;
  }

  State* pState = new State;
  pState->stateTag_ = stateTag;
  pState->playerState_ = playerState;
  pState->canInput_ = canInput;
  //pState->canChangeAnimState_ = canChangeAnimState;
  pState->searchHandle_ = stateTable_.Insert(pState, &pState->stateTag_, 8);

  return nullptr != pState->searchHandle_;
}

void StateComponent::ChangeState(unsigned long long stateTag) {
  State* pState = nullptr;
  if (0 == stateTable_.Select((void**)&pState, 1, &stateTag, 8)) {
    return;
  }

  curState_.stateTag_ = pState->stateTag_;
  curState_.playerState_ = pState->playerState_;
  curState_.canInput_ = pState->canInput_;
  //curState_.canChangeAnimState_ = pState->canChangeAnimState_;
  curState_.searchHandle_ = pState->searchHandle_;
}

State StateComponent::GetCurState() const {
  return curState_;
}

unsigned long long StateComponent::GetCurAnimState() const {
  return curState_.stateTag_;
}

PLAYERSTATE StateComponent::GetPlayerState() const {
  return curState_.playerState_;
}

bool StateComponent::CanInput() const {
  return curState_.canInput_;
}

//bool StateComponent::CanChangeAnimState() const {
//  return curState_.canChangeAnimState_;
//}
