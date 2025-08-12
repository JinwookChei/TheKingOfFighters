#include "stdafx.h"
#include "CommandHandler.h"
#include "IoriCommandHandler.h"
#include "KOFLevel.h"
#include "ScreenMask.h"


IoriCommandHandler::IoriCommandHandler() {
}

IoriCommandHandler::~IoriCommandHandler() {
}

bool IoriCommandHandler::RegistCommands() {
  if (nullptr == pOwnerCommandComponent_) {
    return false;
  }

  pOwnerCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_A}, &IoriCommandHandler::Command_1, this);
  pOwnerCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_B}, &IoriCommandHandler::Command_1, this);
  pOwnerCommandComponent_->RegistCommand({CK_Left, CK_Left}, &IoriCommandHandler::Command_2, this);
  pOwnerCommandComponent_->RegistCommand({CK_Right, CK_Right}, &IoriCommandHandler::Command_3, this);
  pOwnerCommandComponent_->RegistCommand({CK_Right, CK_Down, CK_Right, CK_A}, &IoriCommandHandler::Command_4, this);
  pOwnerCommandComponent_->RegistCommand({CK_Right, CK_Down, CK_Right, CK_C}, &IoriCommandHandler::Command_4, this);
  pOwnerCommandComponent_->RegistCommand({CK_Down, CK_Left, CK_A}, &IoriCommandHandler::Command_5, this);
  pOwnerCommandComponent_->RegistCommand({CK_Down, CK_Left, CK_C}, &IoriCommandHandler::Command_5, this);
  pOwnerCommandComponent_->RegistCommand({CK_Down, CK_Right, CK_Down, CK_Left, CK_A}, &IoriCommandHandler::Command_6, this);
  pOwnerCommandComponent_->RegistCommand({CK_Down, CK_Right, CK_Down, CK_Left, CK_C}, &IoriCommandHandler::Command_6, this);
  pOwnerCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_Left, CK_Down, CK_Right, CK_A}, &IoriCommandHandler::Command_7, this);
  pOwnerCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_Left, CK_Down, CK_Right, CK_C}, &IoriCommandHandler::Command_7, this);

  return true;
}

void IoriCommandHandler::Command_1() {
  pOwnerSkillComponent_->ExecuteSkill(SKILL_1);
}

void IoriCommandHandler::Command_2() {
  pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_BackStep);
  pOwnerMovementComponent_->BackStep((pOwnerPlayer_->FacingRight()));
}

void IoriCommandHandler::Command_3() {
  pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_Run);
}

void IoriCommandHandler::Command_4() {
  pOwnerSkillComponent_->ExecuteSkill(SKILL_2);
}

void IoriCommandHandler::Command_5() {
  pOwnerSkillComponent_->ExecuteSkill(SKILL_3);
}

void IoriCommandHandler::Command_6() {
  pOwnerSkillComponent_->ExecuteSkill(SKILL_5);
}

void IoriCommandHandler::Command_7() {
  if (0 >= pOwnerMPComponent_->SkillPoint()) {
    return;
  }

  /*SkillInfo* pCurSkillInfo = pOwnerSkillComponent_->GetCurrentActiveSkillInfo();
  if (nullptr == pCurSkillInfo) {
    return;
  }

  if (IORI_SKILL_1211ShikiYaOtome == pCurSkillInfo->skillTag_) {
    pOwnerSkillComponent_->SetMiscTemp(true);
  }*/
}