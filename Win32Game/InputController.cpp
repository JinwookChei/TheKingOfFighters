#include "stdafx.h"
#include "KOFPlayer.h"
#include "StateComponent.h"
#include "CommandComponent.h"
#include "InputController.h"

InputController::InputController()
    : playerKeySet_(),
      pOwnerPlayer_(nullptr),
      pOwnerCommand_(nullptr) {
}

InputController::~InputController() {
}

void InputController::BeginPlay() {
}

void InputController::Tick(unsigned long long deltaTick) {
  // UpdateCommand();

  // ResetInputBitSet();

  // UpdateInput();
}

bool InputController::Initialize(KOFPlayer* pOwnerPlayer, CommandComponent* pOwnerCommandComponent) {
  if (nullptr == pOwnerPlayer) {
    return false;
  }
  if (nullptr == pOwnerCommandComponent) {
    return false;
  }

  pOwnerPlayer_ = pOwnerPlayer;

  pOwnerCommand_ = pOwnerCommandComponent;

  if (true == pOwnerPlayer_->IsPlayer1()) {
    playerKeySet_ = {'A', 'S', 'Z', 'X', VK_UP, VK_RIGHT, VK_DOWN, VK_LEFT};  // D C B A UP RIGHT DONW LEFT
    // playerKeySet_ = {'1', '2', '3', '4', VK_UP, VK_RIGHT, VK_DOWN, VK_LEFT};  // D C B A UP RIGHT DONW LEFT
  } else {
    playerKeySet_ = {'E', 'R', 'D', 'F', 'I', 'L', 'K', 'J'};  // D C B A UP RIGHT DONW LEFT
    // playerKeySet_ = {'1', '2', '3', '4', 'S', 'C', 'X', 'Z'};  // D C B A UP RIGHT DONW LEFT
  }

  ResetInputBitSet();
  return true;
}

void InputController::UpdateInput() {
  // InputBitSet :
  // Left : 10000000
  // Down : 01000000
  // Right: 00100000
  // Up :   00010000
  // A  :   00001000
  // B  :   00000100
  // C  :   00000010
  // D  :   00000001

  bool anyKeyActive = false;
  for (int key : playerKeySet_) {
    if (InputManager::Instance()->IsPress(key) ||
        InputManager::Instance()->IsDown(key) ||
        InputManager::Instance()->IsUp(key)) {
      anyKeyActive = true;
      break;
    }
  }

  if (false == anyKeyActive) {
    return;
  }

  // LEFT
  if (InputManager::Instance()->IsPress(playerKeySet_[7])) {
    if (pOwnerPlayer_->PlayerOnLeft()) {
      inputPressBitSet_.set(KEY_Left);
    } else {
      inputPressBitSet_.set(KEY_Right);
    }
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[7])) {
    if (pOwnerPlayer_->PlayerOnLeft()) {
      inputDownBitSet_.set(KEY_Left);
    } else {
      inputDownBitSet_.set(KEY_Right);
    }
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[7])) {
    if (pOwnerPlayer_->PlayerOnLeft()) {
      inputUpBitSet_.set(KEY_Left);
    } else {
      inputUpBitSet_.set(KEY_Right);
    }
  }
  // DOWN
  if (InputManager::Instance()->IsPress(playerKeySet_[6])) {
    inputPressBitSet_.set(KEY_Down);
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[6])) {
    inputDownBitSet_.set(KEY_Down);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[6])) {
    inputUpBitSet_.set(KEY_Down);
  }
  // RIGHT
  if (InputManager::Instance()->IsPress(playerKeySet_[5])) {
    if (pOwnerPlayer_->PlayerOnLeft()) {
      inputPressBitSet_.set(KEY_Right);
    } else {
      inputPressBitSet_.set(KEY_Left);
    }
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[5])) {
    if (pOwnerPlayer_->PlayerOnLeft()) {
      inputDownBitSet_.set(KEY_Right);
    } else {
      inputDownBitSet_.set(KEY_Left);
    }
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[5])) {
    if (pOwnerPlayer_->PlayerOnLeft()) {
      inputUpBitSet_.set(KEY_Right);
    } else {
      inputUpBitSet_.set(KEY_Left);
    }
  }
  // UP
  if (InputManager::Instance()->IsPress(playerKeySet_[4])) {
    inputPressBitSet_.set(KEY_Up);
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[4])) {
    inputDownBitSet_.set(KEY_Up);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[4])) {
    inputUpBitSet_.set(KEY_Up);
  }
  // A
  if (InputManager::Instance()->IsPress(playerKeySet_[3])) {
    inputPressBitSet_.set(KEY_A);
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[3])) {
    inputDownBitSet_.set(KEY_A);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[3])) {
    inputUpBitSet_.set(KEY_A);
  }
  // B
  if (InputManager::Instance()->IsPress(playerKeySet_[2])) {
    inputPressBitSet_.set(KEY_B);
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[2])) {
    inputDownBitSet_.set(KEY_B);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[2])) {
    inputUpBitSet_.set(KEY_B);
  }
  // C
  if (InputManager::Instance()->IsPress(playerKeySet_[1])) {
    inputPressBitSet_.set(KEY_C);
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[1])) {
    inputDownBitSet_.set(KEY_C);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[1])) {
    inputUpBitSet_.set(KEY_C);
  }
  // D
  if (InputManager::Instance()->IsPress(playerKeySet_[0])) {
    inputPressBitSet_.set(KEY_D);
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[0])) {
    inputDownBitSet_.set(KEY_D);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[0])) {
    inputUpBitSet_.set(KEY_D);
  }
}

void InputController::UpdateCommand() {
  if (InputManager::Instance()->IsDown(playerKeySet_[7])) {
    if (pOwnerPlayer_->PlayerOnLeft()) {
      pOwnerCommand_->JumpNode(CK_Left);
    } else {
      pOwnerCommand_->JumpNode(CK_Right);
    }
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[6])) {
    pOwnerCommand_->JumpNode(CK_Down);
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[5])) {
    if (pOwnerPlayer_->PlayerOnLeft()) {
      pOwnerCommand_->JumpNode(CK_Right);
    } else {
      pOwnerCommand_->JumpNode(CK_Left);
    }
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[4])) {
    pOwnerCommand_->JumpNode(CK_Up);
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[3])) {
    pOwnerCommand_->JumpNode(CK_A);
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[2])) {
    pOwnerCommand_->JumpNode(CK_B);
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[1])) {
    pOwnerCommand_->JumpNode(CK_C);
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[0])) {
    pOwnerCommand_->JumpNode(CK_D);
  }
}

void InputController::ResetInputBitSet() {
  inputPressBitSet_.reset();
  inputDownBitSet_.reset();
  inputUpBitSet_.reset();
}

bool InputController::IsEqualInputBitSet(KEY_STATE keyState, std::initializer_list<KEY_TYPE> targetKeys) const {
  std::bitset<8> compareTarget;
  for (const KEY_TYPE& key : targetKeys) {
    compareTarget.set(key);
  }

  switch (keyState) {
    case KEY_STATE_Press:
      return inputPressBitSet_ == compareTarget;
      break;
    case KEY_STATE_Down:
      return inputDownBitSet_ == compareTarget;
      break;
    case KEY_STATE_Up:
      return inputUpBitSet_ == compareTarget;
      break;
    default:
      break;
  }

  return false;
}

bool InputController::IsContainInputBitSet(KEY_STATE keyState, std::initializer_list<KEY_TYPE> targetKeys) const {
  std::bitset<8> compareTarget;
  for (const KEY_TYPE& key : targetKeys) {
    compareTarget.set(key);
  }

  switch (keyState) {
    case KEY_STATE_Press:
      return (inputPressBitSet_ & compareTarget) == compareTarget;
      break;
    case KEY_STATE_Down:
      return (inputDownBitSet_ & compareTarget) == compareTarget;
      break;
    case KEY_STATE_Up:
      return (inputUpBitSet_ & compareTarget) == compareTarget;
      break;
    default:
      break;
  }

  return false;
}


bool InputController::IsNoKeyInput() const {
  if (false == IsEqualInputBitSet(KEY_STATE_Press, {})) {
    return false;
  }
  if (false == IsEqualInputBitSet(KEY_STATE_Down, {})) {
    return false;
  }
  if (false == IsEqualInputBitSet(KEY_STATE_Up, {})) {
    return false;
  }
  return true;
}
