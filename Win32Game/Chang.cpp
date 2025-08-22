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
#include "RestrictionComponent.h"
#include "RestrictionManager.h"
#include "GhostEffect.h"
#include "CollisionBox.h"
#include "Chang.h"
#include "AnimationStateMachine.h"
#include "InputController.h"

Chang::Chang() {
}

Chang::~Chang() {
}

void Chang::BeginPlay() {
}

//void Chang::Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) {
//  KOFPlayer::Initialize(isPlayer1, position, useCameraPosition, opponentPlayer);
//
//  // CHARACTER SETTING
//  IImage* pImage = ImgManager::GetIntance()->GetImg(IMGTYPE_IoriImage);
//  if (nullptr == pImage) {
//    return;
//  }
//  SetCharacterScale(pImage->GetScale(7) * pRender_->GetLocalScale());
//
//  // ANIM
//  pAnimationHandler_ = CreateComponent<IoriAnimationHandler>();
//  if (nullptr == pAnimationHandler_) {
//    return;
//  }
//  if (false == pAnimationHandler_->Initialize(this, pRender_, pStateComponent_, pMovementComponent_, pRestrictionComponent_)) {
//    return;
//  }
//
//  if (false == pAnimationHandler_->RegistAnimations()) {
//    return;
//  }
//
//  // SOUND
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_JumpUp, SOUNDTYPE_COMMON_Jump01);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Run, SOUNDTYPE_COMMON_FootStep);
//  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_108ShikiYamiBarai, SOUNDTYPE_IORI_108ShikiYamiBarai);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Dash, SOUNDTYPE_IORI_Dash);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_RollingBack, SOUNDTYPE_IORI_Dash);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyKick_CloseRange, SOUNDTYPE_IORI_Kiai_Heavy01);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightKick_CloseRange, SOUNDTYPE_IORI_Kiai_Light01);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, SOUNDTYPE_IORI_Kiai_Heavy02);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightPunch_CloseRange, SOUNDTYPE_IORI_Kiai_Light02);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyKick_LongRange, SOUNDTYPE_IORI_Kiai_Heavy03);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightKick_LongRange, SOUNDTYPE_IORI_Kiai_Light03);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyPunch_LongRange, SOUNDTYPE_IORI_Kiai_Heavy01);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightPunch_LongRange, SOUNDTYPE_IORI_Kiai_Light01);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyKick_Seat, SOUNDTYPE_IORI_Kiai_Heavy02);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightKick_Seat, SOUNDTYPE_IORI_Kiai_Light02);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyPunch_Seat, SOUNDTYPE_IORI_Kiai_Heavy03);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightPunch_Seat, SOUNDTYPE_IORI_Kiai_Light03);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyKick_Jump, SOUNDTYPE_IORI_Kiai_Heavy01);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_LightKick_Jump, SOUNDTYPE_IORI_Kiai_Light01);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HeavyPunch_Jump, SOUNDTYPE_IORI_Kiai_Heavy02);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Hit_High, SOUNDTYPE_None);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Hit_Low, SOUNDTYPE_None);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Hit_Strong, SOUNDTYPE_None);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Hit_Seat, SOUNDTYPE_None);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Hit_JumpUp, SOUNDTYPE_None);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_NeckGrabbed, SOUNDTYPE_COMMON_Hit01);
//  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_UltimateCasting, SOUNDTYPE_IORI_1211ShikiYaOtome01);
//  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_GaishikiMutan_1, SOUNDTYPE_IORI_Kiai_Light01);
//  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_GaishikiMutan_2, SOUNDTYPE_IORI_Kiai_Light02);
//  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Shinigami, SOUNDTYPE_IORI_Kiai_Light02);
//  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_HyakushikiOniyaki, SOUNDTYPE_IORI_HyakushikiOniyaki);
//  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_1211ShikiYaOtome_4, SOUNDTYPE_IORI_1211ShikiYaOtome02);
//  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_1211ShikiYaOtome_9, SOUNDTYPE_IORI_1211ShikiYaOtome03);
//  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_HyakushikiOniyaki, SOUNDTYPE_IORI_HyakushikiOniyaki);
//  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Ura306shikiShika_1, SOUNDTYPE_IORI_HyakushikiOniyaki);
//  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Ura306shikiShika_2, SOUNDTYPE_IORI_HyakushikiOniyaki);
//  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Ura306shikiShika_3, SOUNDTYPE_IORI_HyakushikiOniyaki);
//
//  // STATE
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_StartPos, {PS_None});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Idle, {PS_Idle});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatDown, {PS_Seat});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Seat, {PS_Seat});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatUp, {PS_Seat});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_FrontWalk, {PS_Move});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackWalk, {PS_Move});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackStep, {PS_Move});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Run, {PS_Run});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_RunEnd, {PS_Run});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_JumpUp, {PS_Jump});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_JumpDown, {PS_Jump});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_JumpLand, {PS_Jump});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Dash, {PS_Dash});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_RollingBack, {PS_Rolling});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Guard, {PS_Guard});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_GuardEnd, {PS_Idle});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Guard_Seat, {PS_Guard, PS_Seat});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_GuardEnd_Seat, {PS_Seat});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_CloseRange, {PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_CloseRange, {PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, {PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_CloseRange, {PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_LongRange, {PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_LongRange, {PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_LongRange, {PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_LongRange, {PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_Seat, {PS_Seat, PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_Seat, {PS_Seat, PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_Seat, {PS_Seat, PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_Seat, {PS_Seat, PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_Jump, {PS_Jump, PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_Jump, {PS_Jump, PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_Jump, {PS_Jump, PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_Jump, {PS_Jump, PS_Attack, PS_EnableClampOffset});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_High, {PS_Hit});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_Low, {PS_Hit});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_Strong, {PS_Hit});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_AirborneUp, {PS_Hit});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_AirborneDown, {PS_Hit});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_AirborneLand, {PS_Hit});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_AirborneGetUp, {PS_None});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_Seat, {PS_Hit, PS_Seat});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_JumpUp, {PS_Hit});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_JumpDown, {PS_Hit});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_NeckGrabbed, {PS_Hit});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_KOKnockBackUp, {PS_Hit});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_KOKnockBackDown, {PS_Hit});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_KOKnockBackLand, {PS_Hit});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_108ShikiYamiBarai, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_1, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_2, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_Shinigami, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_HyakushikiOniyaki, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_1, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_2, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_3, {PS_Attack});
//  pStateComponent_->RegistState(PLAYER_ANIMTYPE_UltimateCasting, {PS_SkillCasting});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_1, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_2, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_3, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_4, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_5, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_6, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_7, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_8, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_9, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_Ura306shikiShika_1, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_Ura306shikiShika_2, {PS_Attack});
//  pStateComponent_->RegistState(IORI_ANIMTYPE_Ura306shikiShika_3, {PS_Attack});
//
//  // RESTRICTION
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_StartPos, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Idle, {});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_SeatDown, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Seat, {});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_SeatUp, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_FrontWalk, {});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_BackWalk, {});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_BackStep, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Run, {});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_RunEnd, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_JumpUp, {PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_JumpDown, {PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_JumpLand, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Dash, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_RollingBack, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Guard, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_GuardEnd, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Guard_Seat, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_GuardEnd_Seat, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyKick_CloseRange, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightKick_CloseRange, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightPunch_CloseRange, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyKick_LongRange, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightKick_LongRange, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyPunch_LongRange, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightPunch_LongRange, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyKick_Seat, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightKick_Seat, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyPunch_Seat, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightPunch_Seat, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyKick_Jump, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightKick_Jump, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyPunch_Jump, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightPunch_Jump, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_High, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_Low, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_Strong, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_AirborneUp, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_AirborneDown, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_AirborneLand, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_AirborneGetUp, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_Seat, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_JumpUp, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_JumpDown, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_NeckGrabbed, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_KOKnockBackUp, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_KOKnockBackDown, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_KOKnockBackLand, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_108ShikiYamiBarai, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_GaishikiMutan_1, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_GaishikiMutan_2, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_Shinigami, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_HyakushikiOniyaki, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_127ShikiAoiHana_1, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_127ShikiAoiHana_2, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_127ShikiAoiHana_3, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_UltimateCasting, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_1, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_2, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_3, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_4, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_5, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_6, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_7, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_8, {PR_LockInput});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_9, {PR_LockInput});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_Ura306shikiShika_1, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_Ura306shikiShika_2, {PR_LockInput, PR_LockExecuteCommand});
//  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_Ura306shikiShika_3, {PR_LockInput, PR_LockExecuteCommand});
//
//  // ATTACK INFO
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
//  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, true, 10.0f, {1.5f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, 0.0f}, 200);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, -5.0f}, 200);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Shinigami, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 15.0f, {2.0f, -8.0f}, 200);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.0f, 0.0f}, 200);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.0f, 0.0f}, 200);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_3, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, 0.0f}, 200);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_1, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 200);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_2, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_3, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_4, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_5, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_6, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_7, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_8, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_9, ATTYPE_StrongAttack, ELMTTYPE_BlueFlame, EFTYPE_Iori_Explosion, false, 5.0f, {3.0f, -4.5f}, 150);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_1, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
//  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_2, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, true, 5.0f, {0.0f, -7.0f}, 100);
//  // pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_3, ATTYPE_StrongAttack, ELMTTYPE_BlueFlame, EFTYPE_Hit_2, false, 10.0f, {1.5f, -10.0f}, 140.0f);
//
//  // COMMAND
//  //pCommandHandler_ = CreateComponent<IoriCommandHandler>();
//  //if (nullptr == pCommandHandler_) {
//  //  return;
//  //}
//  //if (false == pCommandHandler_->Initialize(this, pCommandComponent_, pMovementComponent_, pSkillComponent_, pMPComponent_)) {
//  //  return;
//  //}
//  //if (false == pCommandHandler_->RegistCommands()) {
//  //  return;
//  //}
//}

void Chang::CompareInputBitset() {
}
