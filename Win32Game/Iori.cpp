#include "stdafx.h"
#include "KOFPlayer.h"
#include "KOFLevel.h"
#include "CameraTarget.h"
#include "ScreenMask.h"
#include "MovementComponent.h"
#include "SoundTable.h"
#include "AttackTable.h"
#include "SkillComponent.h"
#include "CommandComponent.h"
#include "ProjectileComponent.h"
#include "HealthComponent.h"
#include "MPComponent.h"
#include "StateComponent.h"
#include "GhostEffect.h"
#include "CollisionBox.h"
#include "Iori.h"

#include "AnimationHandler.h"
#include "IoriAnimationHandler.h"
#include "CommandHandler.h"
#include "IoriCommandHandler.h"
#include "SkillHandler.h"
#include "IoriSkillHandler.h"

#include "InputController.h"
#include "SkillTest.h"
Iori::Iori() {
}

Iori::~Iori() {
}

void Iori::BeginPlay() {
}

void Iori::Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) {
  KOFPlayer::Initialize(isPlayer1, position, useCameraPosition, opponentPlayer);

  // CHARACTER SETTING
  IImage* pImage = ImgManager::GetIntance()->GetImg(IMGTYPE_IoriImage);
  if (nullptr == pImage) {
    return;
  }
  SetCharacterScale(pImage->GetScale(7) * pRender_->GetLocalScale());

  // ANIM
  pAnimationHandler_ = CreateComponent<IoriAnimationHandler>();
  if (nullptr == pAnimationHandler_) {
    return;
  }
  if (false == pAnimationHandler_->Initialize(this, pRender_, pStateComponent_, pMovementComponent_)) {
    return;
  }

  if (false == pAnimationHandler_->RegistAnimations()) {
    return;
  }

  UpdateAnimState(PLAYER_ANIMTYPE_StartPos);

  // SOUND
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_JumpUp, SOUNDTYPE_COMMON_Jump01);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Run, SOUNDTYPE_COMMON_FootStep);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_108ShikiYamiBarai, SOUNDTYPE_IORI_108ShikiYamiBarai);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Dash, SOUNDTYPE_IORI_Dash);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_RollingBack, SOUNDTYPE_IORI_Dash);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyKick_CloseRange, SOUNDTYPE_IORI_Kiai_Heavy01);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightKick_CloseRange, SOUNDTYPE_IORI_Kiai_Light01);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, SOUNDTYPE_IORI_Kiai_Heavy02);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightPunch_CloseRange, SOUNDTYPE_IORI_Kiai_Light02);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyKick_LongRange, SOUNDTYPE_IORI_Kiai_Heavy03);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightKick_LongRange, SOUNDTYPE_IORI_Kiai_Light03);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyPunch_LongRange, SOUNDTYPE_IORI_Kiai_Heavy01);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightPunch_LongRange, SOUNDTYPE_IORI_Kiai_Light01);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyKick_Seat, SOUNDTYPE_IORI_Kiai_Heavy02);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightKick_Seat, SOUNDTYPE_IORI_Kiai_Light02);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyPunch_Seat, SOUNDTYPE_IORI_Kiai_Heavy03);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightPunch_Seat, SOUNDTYPE_IORI_Kiai_Light03);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyKick_Jump, SOUNDTYPE_IORI_Kiai_Heavy01);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightKick_Jump, SOUNDTYPE_IORI_Kiai_Light01);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyPunch_Jump, SOUNDTYPE_IORI_Kiai_Heavy02);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Hit_High, SOUNDTYPE_None);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Hit_Low, SOUNDTYPE_None);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Hit_Strong, SOUNDTYPE_None);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Hit_Seat, SOUNDTYPE_None);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Hit_JumpUp, SOUNDTYPE_None);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_NeckGrab, SOUNDTYPE_COMMON_Hit01);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_UltimateCasting, SOUNDTYPE_IORI_1211ShikiYaOtome01);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_GaishikiMutan_1, SOUNDTYPE_IORI_Kiai_Light01);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_GaishikiMutan_2, SOUNDTYPE_IORI_Kiai_Light02);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Shinigami, SOUNDTYPE_IORI_Kiai_Light02);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_HyakushikiOniyaki, SOUNDTYPE_IORI_HyakushikiOniyaki);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_1211ShikiYaOtome_4, SOUNDTYPE_IORI_1211ShikiYaOtome02);
  // pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_1211ShikiYaOtome_9, SOUNDTYPE_IORI_1211ShikiYaOtome03);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_HyakushikiOniyaki, SOUNDTYPE_IORI_HyakushikiOniyaki);
  // pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Ura306shikiShika_1, SOUNDTYPE_IORI_HyakushikiOniyaki);
  // pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Ura306shikiShika_2, SOUNDTYPE_IORI_HyakushikiOniyaki);
  // pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Ura306shikiShika_3, SOUNDTYPE_IORI_HyakushikiOniyaki);

  // STATE
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_StartPos, {PS_None}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Idle, {PS_Idle}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatDown, {PS_Seat}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Seat, {PS_Seat}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatUp, {PS_Seat}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_FrontWalk, {PS_Move}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackWalk, {PS_Move}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackStep, {PS_Move}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Run, {PS_Run}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_RunEnd, {PS_Run}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_JumpUp, {PS_Jump}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_JumpDown, {PS_Jump}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_JumpLand, {PS_Jump}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Dash, {PS_Dash}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_RollingBack, {PS_Rolling}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Guard, {PS_Guard}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_GuardEnd, {PS_Idle}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Guard_Seat, {PS_Guard, PS_Seat}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_GuardEnd_Seat, {PS_Seat}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_CloseRange, {PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_CloseRange, {PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, {PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_CloseRange, {PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_LongRange, {PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_LongRange, {PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_LongRange, {PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_LongRange, {PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_Seat, {PS_Seat, PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_Seat, {PS_Seat, PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_Seat, {PS_Seat, PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_Seat, {PS_Seat, PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_Jump, {PS_Jump, PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_Jump, {PS_Jump, PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_Jump, {PS_Jump, PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_Jump, {PS_Jump, PS_Attack, PS_EnableClampOffset}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_High, {PS_Hit}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_Low, {PS_Hit}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_Strong, {PS_Hit}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_AirborneUp, {PS_Hit}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_AirborneDown, {PS_Hit}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_AirborneLand, {PS_Hit}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_AirborneGetUp, {PS_None}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_Seat, {PS_Hit, PS_Seat}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_JumpUp, {PS_Hit}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_JumpDown, {PS_Hit}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_NeckGrab, {PS_Hit}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_108ShikiYamiBarai, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_1, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_2, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_Shinigami, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_HyakushikiOniyaki, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_1, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_2, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_3, {PS_Attack}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_UltimateCasting, {PS_SkillCasting}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_1, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_2, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_3, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_4, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_5, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_6, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_7, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_8, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_9, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_Ura306shikiShika_1, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_Ura306shikiShika_2, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_Ura306shikiShika_3, {PS_Attack}, false);

  // ATTACK INFO
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, true, 10.0f, {1.5f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, -5.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Shinigami, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 15.0f, {2.0f, -8.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_3, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_1, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_2, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_3, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_4, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_5, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_6, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_7, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_8, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_9, ATTYPE_StrongAttack, ELMTTYPE_BlueFlame, EFTYPE_Iori_Explosion, false, 10.0f, {3.0f, -4.5f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_1, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_2, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, true, 5.0f, {0.0f, -7.0f}, 120.0f);
  // pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_3, ATTYPE_StrongAttack, ELMTTYPE_BlueFlame, EFTYPE_Hit_2, false, 10.0f, {1.5f, -10.0f}, 140.0f);

  // COMMAND
  pCommandHandler_ = CreateComponent<IoriCommandHandler>();
  if (nullptr == pCommandHandler_) {
    return;
  }
  if (false == pCommandHandler_->Initialize(this, pCommandComponent_, pMovementComponent_, pSkillComponent_, pMPComponent_)) {
    return;
  }
  if (false == pCommandHandler_->RegistCommands()) {
    return;
  }

  // SKILL
  pSkillHandler_ = CreateComponent<IoriSkillHandler>();
  if (nullptr == pSkillHandler_) {
    return;
  }
  if (false == pSkillHandler_->Initialize(this, pSkillComponent_, pRender_, pAnimationHandler_, pMovementComponent_, pStateComponent_, pAttackBox_, pCommandComponent_, pProjectileComponent_, pMPComponent_)) {
    return;
  }
  if (false == pSkillHandler_->RegistSkills()) {
    return;
  }

  // TODP : SKILL TEST
  // SKILL 1
  SkillFrameAction SK1_ActionA;
  SK1_ActionA.actionType_ = SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue;
  SK1_ActionA.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_CheckInputDownA);
  SkillFrameAction SK1_ActionB;
  SK1_ActionB.actionType_ = SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue;
  SK1_ActionB.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_CheckInputDownC);
  SkillFrame SK1_FrameA;
  SK1_FrameA.startIndex_ = 101;
  SK1_FrameA.endIndex_ = 104;
  SK1_FrameA.actions.push_back(SK1_ActionA);
  SK1_FrameA.actions.push_back(SK1_ActionB);
  SkillFrameAction SK1_ActionC;
  SK1_ActionC.actionType_ = SKILL_FRAME_ACTION_UpdateSkillState;
  SK1_ActionC.actionParams_.changeStateIndex_ = 1;
  SK1_ActionC.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_IsStateMiscFlagTrue);
  SK1_ActionC.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_HasAttackCollition);
  SkillFrame SK1_FrameB;
  SK1_FrameB.startIndex_ = 105;
  SK1_FrameB.endIndex_ = 105;
  SK1_FrameB.actions.push_back(SK1_ActionC);
  SkillState SK1_A;
  SK1_A.animState_ = IORI_ANIMTYPE_GaishikiMutan_1;
  SK1_A.frames_.push_back(SK1_FrameA);
  SK1_A.frames_.push_back(SK1_FrameB);
  SkillState SK1_B;
  SK1_B.animState_ = IORI_ANIMTYPE_GaishikiMutan_2;
  Skill Skill_1;
  Skill_1.skillTag_ = SKILL_TYPE::SKILL_1;
  Skill_1.castCondition_ = SKILL_CAST_COND_None;
  Skill_1.skillStates_.push_back(SK1_A);
  Skill_1.skillStates_.push_back(SK1_B);
  skillTest_->RegistSkill(Skill_1);

  // SKILL 2
  SkillFrameAction SK2_ActionA;
  SK2_ActionA.actionType_ = SKILL_FRAME_ACTION_SpawnEffect;
  SK2_ActionA.actionParams_.effectType_ = EFTYPE_Iori_Casting_YamiBarai;
  SK2_ActionA.actionParams_.spawnEffectPos_ = {40.0f, -280.0f};
  SK2_ActionA.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_None);
  SkillFrame SK2_FrameA;
  SK2_FrameA.startIndex_ = 225;
  SK2_FrameA.endIndex_ = 225;
  SK2_FrameA.actions.push_back(SK2_ActionA);
  SkillFrameAction SK2_ActionB;
  SK2_ActionB.actionType_ = SKILL_FRAME_ACTION_FireProjectile;
  SK2_ActionB.actionParams_.projectileType_ = IORI_PROJECTILE_YamiBarai;
  SK2_ActionB.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_None);
  SkillFrame SK2_FrameB;
  SK2_FrameB.startIndex_ = 226;
  SK2_FrameB.endIndex_ = 226;
  SK2_FrameB.actions.push_back(SK2_ActionB);
  SkillState SK2_StateA;
  SK2_StateA.animState_ = IORI_ANIMTYPE_108ShikiYamiBarai;
  SK2_StateA.frames_.push_back(SK2_FrameA);
  SK2_StateA.frames_.push_back(SK2_FrameB);
  Skill skill_2;
  skill_2.skillTag_ = SKILL_2;
  skill_2.castCondition_ = SKILL_CAST_COND_None;
  skill_2.skillStates_.push_back(SK2_StateA);
  skillTest_->RegistSkill(skill_2);

  // SKILL 3
  SkillFrameAction SK3_ActionA;
  SK3_ActionA.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_None);
  SK3_ActionA.actionType_ = SKILL_FRAME_ACTION_MovementDash;
  SK3_ActionA.actionParams_.dashDuration_ = 150.0f;
  SK3_ActionA.actionParams_.dashDistance_ = 150.0f;
  SkillFrame SK3_FrameA;
  SK3_FrameA.startIndex_ = 276;
  SK3_FrameA.endIndex_ = 276;
  SK3_FrameA.actions.push_back(SK3_ActionA);
  SkillFrameAction SK3_ActionB;
  SK3_ActionB.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_None);
  SK3_ActionB.actionParams_.jumpForce_ = {0.4f, -4.5f};
  SK3_ActionB.actionType_ = SKILL_FRAME_ACTION_MovementJump;
  SkillFrameAction SK3_ActionC;
  SK3_ActionC.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_None);
  SK3_ActionC.actionParams_.projectileType_ = IORI_PROJECTILE_HyakushikiOniyaki_Low;
  SK3_ActionC.actionType_ = SKILL_FRAME_ACTION_FireProjectile;
  SkillFrame SK3_FrameB;
  SK3_FrameB.startIndex_ = 281;
  SK3_FrameB.endIndex_ = 281;
  SK3_FrameB.actions.push_back(SK3_ActionB);
  SK3_FrameB.actions.push_back(SK3_ActionC);
  SkillFrameAction SK3_ActionD;
  SK3_ActionD.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_None);
  SK3_ActionD.actionParams_.projectileType_ = IORI_PROJECTILE_HyakushikiOniyaki_High;
  SK3_ActionD.actionType_ = SKILL_FRAME_ACTION_FireProjectile;
  SkillFrame SK3_FrameC;
  SK3_FrameC.startIndex_ = 284;
  SK3_FrameC.endIndex_ = 284;
  SK3_FrameC.actions.push_back(SK3_ActionD);
  SkillState SK3_State;
  SK3_State.animState_ = IORI_ANIMTYPE_HyakushikiOniyaki;
  SK3_State.frames_.push_back(SK3_FrameA);
  SK3_State.frames_.push_back(SK3_FrameB);
  SK3_State.frames_.push_back(SK3_FrameC);
  Skill Skill_3;
  Skill_3.skillTag_ = SKILL_3;
  Skill_3.castCondition_ = SKILL_CAST_COND_None;
  Skill_3.skillStates_.push_back(SK3_State);
  skillTest_->RegistSkill(Skill_3);

  // SKILL 4
  SkillFrameAction SK4_ActionA;
  SK4_ActionA.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_None);
  SK4_ActionA.actionType_ = SKILL_FRAME_ACTION_MovementDash;
  SK4_ActionA.actionParams_.dashDuration_ = 150.0f;
  SK4_ActionA.actionParams_.dashDistance_ = 80.0f;
  SkillFrame SK4_FrameA;
  SK4_FrameA.startIndex_ = 257;
  SK4_FrameA.endIndex_ = 257;
  SK4_FrameA.actions.push_back(SK4_ActionA);
  SkillFrameAction SK4_ActionB;
  SK4_ActionB.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_CheckInputDownA);
  SK4_ActionB.actionType_ = SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue;
  SkillFrameAction SK4_ActionC;
  SK4_ActionC.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_CheckInputDownC);
  SK4_ActionC.actionType_ = SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue;
  SkillFrame SK4_FrameB;
  SK4_FrameB.startIndex_ = 257;
  SK4_FrameB.endIndex_ = 260;
  SK4_FrameB.actions.push_back(SK4_ActionB);
  SK4_FrameB.actions.push_back(SK4_ActionC);
  SkillFrameAction SK4_ActionD;
  SK4_ActionD.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_HasAttackCollition);
  SK4_ActionD.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_IsStateMiscFlagTrue);
  SK4_ActionD.actionParams_.changeStateIndex_ = 1;
  SK4_ActionD.actionType_ = SKILL_FRAME_ACTION_UpdateSkillState;
  SkillFrame SK4_FrameC;
  SK4_FrameC.startIndex_ = 260;
  SK4_FrameC.endIndex_ = 260;
  SK4_FrameC.actions.push_back(SK4_ActionD);
  SkillState SK4_StateA;
  SK4_StateA.animState_ = IORI_ANIMTYPE_127ShikiAoiHana_1;
  SK4_StateA.frames_.push_back(SK4_FrameA);
  SK4_StateA.frames_.push_back(SK4_FrameB);
  SK4_StateA.frames_.push_back(SK4_FrameC);
  SkillFrameAction SK4_ActionH;
  SK4_ActionH.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_None);
  SK4_ActionH.actionParams_.dashDuration_ = 150.0f;
  SK4_ActionH.actionParams_.dashDistance_ = 80.0f;
  SK4_ActionH.actionType_ = SKILL_FRAME_ACTION_MovementDash;
  SkillFrame SK4_FrameF;
  SK4_FrameF.startIndex_ = 262;
  SK4_FrameF.endIndex_ = 262;
  SK4_FrameF.actions.push_back(SK4_ActionH);
  SkillFrameAction SK4_ActionE;
  SK4_ActionE.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_CheckInputDownA);
  SK4_ActionE.actionType_ = SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue;
  SkillFrameAction SK4_ActionF;
  SK4_ActionF.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_CheckInputDownC);
  SK4_ActionF.actionType_ = SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue;
  SkillFrame SK4_FrameD;
  SK4_FrameD.startIndex_ = 264;
  SK4_FrameD.endIndex_ = 267;
  SK4_FrameD.actions.push_back(SK4_ActionE);
  SK4_FrameD.actions.push_back(SK4_ActionF);
  SkillFrameAction SK4_ActionG;
  SK4_ActionG.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_HasAttackCollition);
  SK4_ActionG.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_IsStateMiscFlagTrue);
  SK4_ActionG.actionParams_.changeStateIndex_ = 2;
  SK4_ActionG.actionType_ = SKILL_FRAME_ACTION_UpdateSkillState;
  SkillFrame Sk4_FrameE;
  Sk4_FrameE.startIndex_ = 267;
  Sk4_FrameE.endIndex_ = 267;
  Sk4_FrameE.actions.push_back(SK4_ActionG);
  SkillState SK4_StateB;
  SK4_StateB.animState_ = IORI_ANIMTYPE_127ShikiAoiHana_2;
  SK4_StateB.frames_.push_back(SK4_FrameF);
  SK4_StateB.frames_.push_back(SK4_FrameD);
  SK4_StateB.frames_.push_back(Sk4_FrameE);
  SkillFrameAction SK4_ActionI;
  SK4_ActionI.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_None);
  SK4_ActionI.actionType_ = SKILL_FRAME_ACTION_MovementJump;
  SK4_ActionI.actionParams_.jumpForce_ = {0.3f, -3.0f};
  SkillFrame Sk4_FrameG;
  Sk4_FrameG.startIndex_ = 269;
  Sk4_FrameG.endIndex_ = 269;
  Sk4_FrameG.actions.push_back(SK4_ActionI);
  SkillState Sk4_StateC;
  Sk4_StateC.animState_ = IORI_ANIMTYPE_127ShikiAoiHana_3;
  Sk4_StateC.frames_.push_back(Sk4_FrameG);
  Skill Skill_4;
  Skill_4.skillTag_ = SKILL_4;
  Skill_4.castCondition_ = SKILL_CAST_COND_None;
  Skill_4.skillStates_.push_back(SK4_StateA);
  Skill_4.skillStates_.push_back(SK4_StateB);
  Skill_4.skillStates_.push_back(Sk4_StateC);
  skillTest_->RegistSkill(Skill_4);

  // SKILL 5
  SkillFrameAction SK5_ActionA;
  SK5_ActionA.actionConditions_.push_back(SKILL_FRAME_ACTION_COND_None);
  SK5_ActionA.actionType_ = SKILL_FRAME_ACTION_UpdateSkillState;
  SK5_ActionA.actionParams_.changeStateIndex_ = 1;
  SkillFrame SK5_FrameA;
  SK5_FrameA.startIndex_ = 344;
  SK5_FrameA.endIndex_ = 344;
  SK5_FrameA.actions.push_back(SK5_ActionA);
  SkillState SK5_StateA;
  SK5_StateA.animState_ = PLAYER_ANIMTYPE_UltimateCasting;
  SK5_StateA.frames_.push_back(SK5_FrameA);

  SkillFrame SK5_FrameB;
  SK5_FrameB.startIndex_ = 70;
  SK5_FrameB.endIndex_ = 70;
  // SK5_FrameB.events.push_back();

  SkillState SK5_StateB;
  SK5_StateB.animState_ = IORI_ANIMTYPE_1211ShikiYaOtome_1;
  SK5_StateB.frames_.push_back(SK5_FrameA);

  Skill Skill_5;
  Skill_5.skillTag_ = SKILL_5;
  Skill_5.castCondition_ = SKILL_CAST_COND_HasSkillPoint;
}

void Iori::CompareInputBitset() {
  if (pStateComponent_->EqualPlayerState({PS_Jump})) {
    // A | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_A})) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_Jump);
      return;
    }
    // B | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_B})) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightKick_Jump);
      return;
    }
    // C | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_C})) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_Jump);
      return;
    }
    // D | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_D})) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_Jump);
      return;
    }
    return;
  }

  if (pStateComponent_->ContainPlayerState({PS_Seat})) {
    // LEFT | PRESS
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_Left})) {
      if (pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
        UpdateAnimState(PLAYER_ANIMTYPE_Guard_Seat);
        return;
      }
    }
    // A | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_A})) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_Seat);
      return;
    }
    // B | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_B})) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightKick_Seat);
      return;
    }
    // C | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_C})) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_Seat);
      return;
    }
    // D | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_D})) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_Seat);
      return;
    }
    // DOWN | PRESS
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_Down})) {
      UpdateAnimState(PLAYER_ANIMTYPE_Seat, ANIMMOD_NONE, false);
      return;
    }
    UpdateAnimState(PLAYER_ANIMTYPE_SeatUp);
    return;
  }

  if (pStateComponent_->ContainPlayerState({PS_Run})) {
    if (false == pInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_Right})) {
      UpdateAnimState(PLAYER_ANIMTYPE_RunEnd);
      return;
    }
  }

  // IDLE
  if (true == pInputController_->IsNoKeyInput()) {
    UpdateAnimState(PLAYER_ANIMTYPE_Idle);
    return;
  } else {
    // LEFT | PRESS Contain
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_Left})) {
      if (pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
        UpdateAnimState(PLAYER_ANIMTYPE_Guard);
        return;
      }
    }
    // RIGHT | PRESS
    if (true == pInputController_->IsEqualInputBitSet(KEY_STATE_Press, {KEY_Right})) {
      if (true == pStateComponent_->ContainPlayerState({PS_Run})) {
        pMovementComponent_->Run(FacingRight());
        return;
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_FrontWalk);
        pMovementComponent_->Walk(FacingRight());
        return;
      }
    }
    // LEFT | PRESS Equal
    if (true == pInputController_->IsEqualInputBitSet(KEY_STATE_Press, {KEY_Left})) {
      UpdateAnimState(PLAYER_ANIMTYPE_BackWalk);
      pMovementComponent_->WalkBack(FacingRight());
      return;
    }
    // DOWN | PRESS
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_Down})) {
      UpdateAnimState(PLAYER_ANIMTYPE_SeatDown);
      return;
    }

    // RIGHT UP | PRESS
    if (true == pInputController_->IsEqualInputBitSet(KEY_STATE_Press, {KEY_Right, KEY_Up})) {
      if (true == pStateComponent_->ContainPlayerState({PS_Run})) {
        UpdateAnimState(PLAYER_ANIMTYPE_JumpUp);
        pMovementComponent_->JumpForward(FacingRight(), true);
        pGhostEffect_->On();
        return;
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_JumpUp);
        pMovementComponent_->JumpForward(FacingRight(), false);
        return;
      }
    }

    // LEFT UP | PRESS
    if (true == pInputController_->IsEqualInputBitSet(KEY_STATE_Press, {KEY_Left, KEY_Up})) {
      UpdateAnimState(PLAYER_ANIMTYPE_JumpUp);
      pMovementComponent_->JumpForward(!FacingRight(), false);
      return;
    }

    // UP | PRESS
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_Up})) {
      UpdateAnimState(PLAYER_ANIMTYPE_JumpUp);
      pMovementComponent_->Jump();
      return;
    }

    // A B LEFT | PRESS
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_Left, KEY_A}) &&
        true == pInputController_->IsEqualInputBitSet(KEY_STATE_Down, {KEY_Left, KEY_B})) {
      UpdateAnimState((PLAYER_ANIMTYPE_RollingBack));
      pMovementComponent_->Dash(!FacingRight(), 300.0f, 400.0f);
      pGhostEffect_->On();
      return;
    }

    // A B | PRESS
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_A, KEY_B})) {
      UpdateAnimState((PLAYER_ANIMTYPE_Dash));
      pMovementComponent_->Dash(FacingRight(), 300.0f, 500.0f);
      pGhostEffect_->On();
      return;
    }

    // RIGHT | PRESS - A | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_Right}) &&
        (true == pInputController_->IsEqualInputBitSet(KEY_STATE_Down, {KEY_A}) ||
         true == pInputController_->IsEqualInputBitSet(KEY_STATE_Down, {KEY_C}))) {
      // UpdateAnimState(IORI_ANIMTYPE_GaishikiMutan_1);
      // pSkillComponent_->ActivateSkill(IORI_SKILL_GaishikiMutan);
      return;
    }

    // RIGHT | PRESS - B | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_Right}) &&
        true == pInputController_->IsEqualInputBitSet(KEY_STATE_Down, {KEY_B})) {
      // UpdateAnimState(IORI_ANIMTYPE_Shinigami);
      // pSkillComponent_->ActivateSkill(IORI_SKILL_Shinigami);
      return;
    }

    // A | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_A})) {
      // if (GetCloseDistance() > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
      //   UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_CloseRange);
      // } else {
      //   UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_LongRange);
      // }

       //skillTest_->ExecuteSkill(SKILL_TYPE::SKILL_1);
      //skillTest_->ExecuteSkill(SKILL_TYPE::SKILL_2);
       //skillTest_->ExecuteSkill(SKILL_TYPE::SKILL_3);
      skillTest_->ExecuteSkill(SKILL_TYPE::SKILL_4);
      //skillTest_->ExecuteSkill(SKILL_5);
      return;
    }

    // B | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_B})) {
      if (GetCloseDistance() > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
        UpdateAnimState(PLAYER_ANIMTYPE_LightKick_CloseRange);
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_LightKick_LongRange);
      }
      return;
    }

    // C | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_C})) {
      if (GetCloseDistance() > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
        UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_CloseRange);
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_LongRange);
      }
      return;
    }

    // D | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_D})) {
      if (GetCloseDistance() > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
        UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_CloseRange);
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_LongRange);
      }
      return;
    }

    // UpdateAnimState(PLAYER_ANIMTYPE_Idle);
    return;
  }
}
