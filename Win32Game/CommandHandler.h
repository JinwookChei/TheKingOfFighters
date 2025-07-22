#pragma once
#include "KOFPlayer.h"
#include "CommandComponent.h"
#include "MovementComponent.h"
#include "SkillComponent.h"
#include "MPComponent.h"

class CommandHandler
    : public ActorComponent {
 public:
  CommandHandler();

  ~CommandHandler() override;

  bool Initialize(
      KOFPlayer* ownerPlayer,
      CommandComponent* commandComponent,
      MovementComponent* movementComponent,
      SkillComponent* skillComponent,
      MPComponent* mpComponent);

  virtual bool RegistCommands() = 0;

 protected:
  KOFPlayer* pOwnerPlayer_;

  CommandComponent* pOwnerCommandComponent_;

  MovementComponent* pOwnerMovementComponent_;

  SkillComponent* pOwnerSkillComponent_;

  MPComponent* pOwnerMPComponent_;
};