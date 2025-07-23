#include "stdafx.h"
#include "SkillHandler.h"



SkillHandler::SkillHandler()
    : pOwnerPlayer_(nullptr),
      pOwnerSkillComponent_(nullptr),
      pOwnerRenderer_(nullptr),
      pOwnerMovementComponent_(nullptr),
      pOwnerStateComponent_(nullptr),
      pOwnerAttackCollision_(nullptr),
      pOwnerCommandComponent_(nullptr),
      pOwnerProjectileComponent_(nullptr),
      pOwnerMPComponent_(nullptr) {
}

SkillHandler::~SkillHandler() {
}

bool SkillHandler::Initialize(KOFPlayer* ownerPlayer,
                              SkillComponent* ownerSkillComponent,
                              ImageRenderer* ownerRenderer,
                              MovementComponent* ownerMovementComponent,
                              StateComponent* ownerStateComponent,
                              CollisionComponent* ownerAttackCollision,
                              CommandComponent* ownerCommandComponent,
                              ProjectileComponent* ownerProjectileComponent,
                              MPComponent* ownerMPComponent) {
  if (nullptr == ownerPlayer) {
    return false;
  }
  if (nullptr == ownerSkillComponent) {
    return false;
  }
  if (nullptr == ownerRenderer) {
    return false;
  }
  if (nullptr == ownerMovementComponent) {
    return false;
  }
  if (nullptr == ownerStateComponent) {
    return false;
  }
  if (nullptr == ownerAttackCollision) {
    return false;
  }
  if (nullptr == ownerCommandComponent) {
    return false;
  }
  if (nullptr == ownerProjectileComponent) {
    return false;
  }
  if (nullptr == ownerMPComponent) {
    return false;
  }

  pOwnerPlayer_ = ownerPlayer;

  pOwnerSkillComponent_ = ownerSkillComponent;

  pOwnerRenderer_ = ownerRenderer;

  pOwnerMovementComponent_ = ownerMovementComponent;

  pOwnerStateComponent_ = ownerStateComponent;

  pOwnerAttackCollision_ = ownerAttackCollision;

  pOwnerCommandComponent_ = ownerCommandComponent;

  pOwnerProjectileComponent_ = ownerProjectileComponent;

  pOwnerMPComponent_ = ownerMPComponent;
  
  return true;
}
