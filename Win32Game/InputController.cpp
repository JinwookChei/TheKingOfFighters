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
  //UpdateCommand();

  //ResetInputBitSet();

  //UpdateInput();
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
      inputPressBitSet_.set(7);
    } else {
      inputPressBitSet_.set(5);
    }
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[7])) {
    if (pOwnerPlayer_->PlayerOnLeft()) {
      inputDownBitSet_.set(7);
    } else {
      inputDownBitSet_.set(5);
    }
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[7])) {
    if (pOwnerPlayer_->PlayerOnLeft()) {
      inputUpBitSet_.set(7);
    } else {
      inputUpBitSet_.set(5);
    }
  }
  // DOWN
  if (InputManager::Instance()->IsPress(playerKeySet_[6])) {
    inputPressBitSet_.set(6);
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[6])) {
    inputDownBitSet_.set(6);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[6])) {
    inputUpBitSet_.set(6);
  }
  // RIGHT
  if (InputManager::Instance()->IsPress(playerKeySet_[5])) {
    if (pOwnerPlayer_->PlayerOnLeft()) {
      inputPressBitSet_.set(5);
    } else {
      inputPressBitSet_.set(7);
    }
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[5])) {
    if (pOwnerPlayer_->PlayerOnLeft()) {
      inputDownBitSet_.set(5);
    } else {
      inputDownBitSet_.set(7);
    }
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[5])) {
    if (pOwnerPlayer_->PlayerOnLeft()) {
      inputUpBitSet_.set(5);
    } else {
      inputUpBitSet_.set(7);
    }
  }
  // UP
  if (InputManager::Instance()->IsPress(playerKeySet_[4])) {
    inputPressBitSet_.set(4);
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[4])) {
    inputDownBitSet_.set(4);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[4])) {
    inputUpBitSet_.set(4);
  }
  // A
  if (InputManager::Instance()->IsPress(playerKeySet_[3])) {
    inputPressBitSet_.set(3);
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[3])) {
    inputDownBitSet_.set(3);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[3])) {
    inputUpBitSet_.set(3);
  }
  // B
  if (InputManager::Instance()->IsPress(playerKeySet_[2])) {
    inputPressBitSet_.set(2);
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[2])) {
    inputDownBitSet_.set(2);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[2])) {
    inputUpBitSet_.set(2);
  }
  // C
  if (InputManager::Instance()->IsPress(playerKeySet_[1])) {
    inputPressBitSet_.set(1);
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[1])) {
    inputDownBitSet_.set(1);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[1])) {
    inputUpBitSet_.set(1);
  }
  // D
  if (InputManager::Instance()->IsPress(playerKeySet_[0])) {
    inputPressBitSet_.set(0);
  }
  if (InputManager::Instance()->IsDown(playerKeySet_[0])) {
    inputDownBitSet_.set(0);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[0])) {
    inputUpBitSet_.set(0);
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

// void InputController::CompareInputBitset() {
//   if (pOwnerStateComponent_->EqualPlayerState({PS_Jump})) {
//     // A | DOWN
//     if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00001000"))) {
//       pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_Jump);
//       return;
//     }
//     // B | DOWN
//     if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000100"))) {
//       pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_LightKick_Jump);
//       return;
//     }
//     // C | DOWN
//     if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000010"))) {
//       pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_Jump);
//       return;
//     }
//     // D | DOWN
//     if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000001"))) {
//       pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_Jump);
//       return;
//     }
//     return;
//   }
//
//   if (pOwnerStateComponent_->ContainPlayerState({PS_Seat})) {
//     // LEFT | PRESS
//     if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("10000000"))) {
//       if (pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
//         pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_Guard_Seat);
//         return;
//       }
//     }
//     // A | DOWN
//     if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00001000"))) {
//       pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_Seat);
//       return;
//     }
//     // B | DOWN
//     if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000100"))) {
//       pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_LightKick_Seat);
//       return;
//     }
//     // C | DOWN
//     if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000010"))) {
//       pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_Seat);
//       return;
//     }
//     // D | DOWN
//     if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000001"))) {
//       pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_Seat);
//       return;
//     }
//     // DOWN | PRESS
//     if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01000000"))) {
//       pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_Seat, ANIMMOD_NONE, false);
//       return;
//     }
//     pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_SeatUp);
//     return;
//   }
//
//   if (pOwnerStateComponent_->ContainPlayerState({PS_Run})) {
//     if (false == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00100000"))) {
//       pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_RunEnd);
//       return;
//     }
//   }
//
//   // IDLE
//   if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00000000")) &&
//       true == IsEqualInputBitSet(inputDownBitSet_, std::bitset<8>("00000000")) &&
//       true == IsEqualInputBitSet(inputUpBitSet_, std::bitset<8>("00000000"))) {
//     pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_Idle);
//     return;
//   } else {
//     // LEFT | PRESS Contain
//     if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("10000000"))) {
//       if (pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
//         UpdateAnimState(PLAYER_ANIMTYPE_Guard);
//         return;
//       }
//     }
//     // RIGHT | PRESS
//     if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00100000"))) {
//       if (true == pStateComponent_->ContainPlayerState({PS_Run})) {
//         pMovementComponent_->Run(FacingRight());
//         return;
//       } else {
//         UpdateAnimState(PLAYER_ANIMTYPE_FrontWalk);
//         pMovementComponent_->Walk(FacingRight());
//         return;
//       }
//     }
//     // LEFT | PRESS Equal
//     if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("10000000"))) {
//       UpdateAnimState(PLAYER_ANIMTYPE_BackWalk);
//       pMovementComponent_->WalkBack(FacingRight());
//       return;
//     }
//     // DOWN | PRESS
//     if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01000000"))) {
//       UpdateAnimState(PLAYER_ANIMTYPE_SeatDown);
//       return;
//     }
//
//     // RIGHT UP | PRESS
//     if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00110000"))) {
//       if (true == pStateComponent_->ContainPlayerState({PS_Run})) {
//         UpdateAnimState(PLAYER_ANIMTYPE_JumpUp);
//         pMovementComponent_->JumpForward(FacingRight(), true);
//         pGhostEffect_->On();
//         return;
//       } else {
//         UpdateAnimState(PLAYER_ANIMTYPE_JumpUp);
//         pMovementComponent_->JumpForward(FacingRight(), false);
//         return;
//       }
//     }
//
//     // LEFT UP | PRESS
//     if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("10010000"))) {
//       UpdateAnimState(PLAYER_ANIMTYPE_JumpUp);
//       pMovementComponent_->JumpForward(!FacingRight(), false);
//       return;
//     }
//
//     // UP | PRESS
//     if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00010000"))) {
//       UpdateAnimState(PLAYER_ANIMTYPE_JumpUp);
//       pMovementComponent_->Jump();
//       return;
//     }
//
//     // A B LEFT | PRESS
//     if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("10000000")) &&
//         true == IsEqualInputBitSet(inputDownBitSet_, std::bitset<8>("00001100"))) {
//       UpdateAnimState((PLAYER_ANIMTYPE_RollingBack));
//       pMovementComponent_->Dash(!FacingRight(), 300.0f, 400.0f);
//       pGhostEffect_->On();
//       return;
//     }
//
//     // A B | PRESS
//     if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00001100"))) {
//       UpdateAnimState((PLAYER_ANIMTYPE_Dash));
//       pMovementComponent_->Dash(FacingRight(), 300.0f, 500.0f);
//       pGhostEffect_->On();
//       return;
//     }
//
//     // RIGHT | PRESS - A | DOWN
//     if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00100000")) &&
//         (true == IsEqualInputBitSet(inputDownBitSet_, std::bitset<8>("00001000")) ||
//          true == IsEqualInputBitSet(inputDownBitSet_, std::bitset<8>("00000010")))) {
//       UpdateAnimState(IORI_ANIMTYPE_GaishikiMutan_1);
//       pSkillComponent_->ActivateSkill(IORI_SKILL_GaishikiMutan);
//       return;
//     }
//
//     // RIGHT | PRESS - B | DOWN
//     if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00100000")) && true == IsEqualInputBitSet(inputDownBitSet_, std::bitset<8>("00000100"))) {
//       UpdateAnimState(IORI_ANIMTYPE_Shinigami);
//       pSkillComponent_->ActivateSkill(IORI_SKILL_Shinigami);
//       return;
//     }
//
//     // A | DOWN
//     if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00001000"))) {
//       if (GetCloseDistance() > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
//         UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_CloseRange);
//       } else {
//         UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_LongRange);
//       }
//       return;
//     }
//
//     // B | DOWN
//     if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000100"))) {
//       if (GetCloseDistance() > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
//         UpdateAnimState(PLAYER_ANIMTYPE_LightKick_CloseRange);
//       } else {
//         UpdateAnimState(PLAYER_ANIMTYPE_LightKick_LongRange);
//       }
//       return;
//     }
//
//     // C | DOWN
//     if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000010"))) {
//       if (GetCloseDistance() > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
//         UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_CloseRange);
//       } else {
//         UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_LongRange);
//       }
//       return;
//     }
//
//     // D | DOWN
//     if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000001"))) {
//       // if (GetCloseDistance() > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
//       //   UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_CloseRange);
//       // } else {
//       //   UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_LongRange);
//       // }
//       skillTest_->ActiveSkill(SkillType::TEST);
//       return;
//     }
//
//     // UpdateAnimState(PLAYER_ANIMTYPE_Idle);
//     return;
//   }
// }

bool InputController::IsEqualInputBitSet(TEMPKEYTYPE keytype, const std::bitset<8>& compareTarget) const {
  switch (keytype) {
    case INPUT_PRESS:
      return inputPressBitSet_ == compareTarget;
      break;
    case INPUT_DOWN:
      return inputDownBitSet_ == compareTarget;
      break;
    case INPUT_UP:
      return inputUpBitSet_ == compareTarget;
      break;
    default:
      break;
  }

  return false;
}

bool InputController::IsContainInputBitSet(TEMPKEYTYPE keytype, const std::bitset<8>& compareTarget) const {
  switch (keytype) {
    case INPUT_PRESS:
      return (inputPressBitSet_ & compareTarget) == compareTarget;
      break;
    case INPUT_DOWN:
      return (inputDownBitSet_ & compareTarget) == compareTarget;
      break;
    case INPUT_UP:
      return (inputUpBitSet_ & compareTarget) == compareTarget;
      break;
    default:
      break;
  }
  
  return false;
}

bool InputController::IsNoKeyInput() const {
  if (false == IsEqualInputBitSet(INPUT_PRESS, std::bitset<8>("00000000"))) {
    return false;
  }
  if (false == IsEqualInputBitSet(INPUT_DOWN, std::bitset<8>("00000000"))) {
    return false;
  }
  if (false == IsEqualInputBitSet(INPUT_UP, std::bitset<8>("00000000"))) {
    return false;
  }
  return true;
}
