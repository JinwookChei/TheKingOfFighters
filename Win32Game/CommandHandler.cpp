#include "stdafx.h"
#include "CommandHandler.h"

CommandHandler::CommandHandler()
    : pOwnerPlayer_(nullptr),
      pOwnerCommandComponent_(nullptr),
      pOwnerMovementComponent_(nullptr),
      pOwnerSkillComponent_(nullptr),
      pOwnerMPComponent_ (nullptr){
}

CommandHandler::~CommandHandler() {
}

bool CommandHandler::Initialize(
    KOFPlayer* ownerPlayer,
    CommandComponent* commandComponent,
    MovementComponent* movementComponent,
    SkillComponent* skillComponent,
    MPComponent* mpComponent) {
  if (nullptr == ownerPlayer) {
    return false;
  }

  if (nullptr == commandComponent) {
    return false;
  }

  if (nullptr == movementComponent) {
    return false;
  }

  if (nullptr == skillComponent) {
    return false;
  }

  if (nullptr == mpComponent) {
    return false;
  }

  pOwnerPlayer_ = ownerPlayer;

  pOwnerCommandComponent_ = commandComponent;

  pOwnerMovementComponent_ = movementComponent;

  pOwnerSkillComponent_ = skillComponent;

  pOwnerMPComponent_ = mpComponent;

  return true;
}
