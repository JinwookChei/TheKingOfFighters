#pragma once
#include "KOFPlayer.h"
#include "SkillComponent.h"
#include "StateComponent.h"
#include "ProjectileComponent.h"
#include "MovementComponent.h"
#include "CommandComponent.h"
#include "MPComponent.h"

class SkillHandler
    : public ActorComponent {
 public:
  SkillHandler();
  ~SkillHandler() override;

  bool Initialize(KOFPlayer* ownerPlayer,
                  SkillComponent* ownerSkillComponent,
                  ImageRenderer* ownerRenderer,
                  MovementComponent* ownerMovementComponent,
                  StateComponent* ownerStateComponent,
                  CollisionComponent* ownerAttackCollision,
                  CommandComponent* ownerCommandComponent,
                  ProjectileComponent* ownerProjectileComponent,
                  MPComponent* ownerMPComponent);

  virtual bool RegistSkills() = 0;

 protected:
  KOFPlayer* pOwnerPlayer_;

  SkillComponent* pOwnerSkillComponent_;

  ImageRenderer* pOwnerRenderer_;

  MovementComponent* pOwnerMovementComponent_;

  StateComponent* pOwnerStateComponent_;

  CollisionComponent* pOwnerAttackCollision_;

  CommandComponent* pOwnerCommandComponent_;

  ProjectileComponent* pOwnerProjectileComponent_;

  MPComponent* pOwnerMPComponent_;
};
