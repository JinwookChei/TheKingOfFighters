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
  pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_108ShikiYamiBarai);
  pOwnerSkillComponent_->ActivateSkill(IORI_SKILL_108ShikiYamiBarai);
}

void IoriCommandHandler::Command_2() {
  pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_BackStep);
  pOwnerMovementComponent_->BackStep((pOwnerPlayer_->FacingRight()));
}

void IoriCommandHandler::Command_3() {
  pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_Run);
}

void IoriCommandHandler::Command_4() {
  pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_HyakushikiOniyaki);
  pOwnerSkillComponent_->ActivateSkill(IORI_SKILL_HyakushikiOniyaki);
}

void IoriCommandHandler::Command_5() {
  pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_127ShikiAoiHana_1);
  pOwnerSkillComponent_->ActivateSkill(IORI_SKILL_127ShikiAoiHana);
}

void IoriCommandHandler::Command_6() {
  if (0 >= pOwnerMPComponent_->SkillPoint()) {
    return;
  }

  Level* pLevel = pOwnerPlayer_->GetLevel();
  if (nullptr == pLevel) {
    return;
  }

  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }

  ScreenMask* pBackGroundMask = pKOFLevel->GetBackGroundMask();
  if (nullptr == pBackGroundMask) {
    return;
  }

  pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_UltimateCasting);
  pOwnerSkillComponent_->ActivateSkill(IORI_SKILL_1211ShikiYaOtome);
  pOwnerMPComponent_->ReduceSkillPoint();
  const Vector& ownerPosition = pOwnerPlayer_->GetPosition();
  KOFPlayer* oppoenetPlayer = pOwnerPlayer_->GetOpponentPlayer();

  EffectManager::Instance()->SpawnEffect(pKOFLevel, EFTYPE_Casting_1, ownerPosition + Vector{0.0f, -250.0f});
  EffectManager::Instance()->SpawnEffect(pKOFLevel, EFTYPE_Casting_2, ownerPosition + Vector{0.0f, -250.0f});
  pKOFLevel->FreezeActors({oppoenetPlayer}, true);
  pBackGroundMask->FadeOut(IMGTYPE_BlackBoardImage, 50.0f);
}

void IoriCommandHandler::Command_7() {
  if (0 >= pOwnerMPComponent_->SkillPoint()) {
    return;
  }

  SkillInfo* pCurSkillInfo = pOwnerSkillComponent_->GetCurrentActiveSkillInfo();
  if (nullptr == pCurSkillInfo) {
    return;
  }

  if (IORI_SKILL_1211ShikiYaOtome == pCurSkillInfo->skillTag_) {
    pOwnerSkillComponent_->SetMiscTemp(true);
  }
}