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
  if (false == pAnimationHandler_->Initialize(this, pRender_, pStateComponent_, pMovementComponent_, pRestrictionComponent_)) {
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
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_NeckGrabbed, SOUNDTYPE_COMMON_Hit01);
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
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_StartPos, {PS_None});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Idle, {PS_Idle});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatDown, {PS_Seat});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Seat, {PS_Seat});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatUp, {PS_Seat});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_FrontWalk, {PS_Move});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackWalk, {PS_Move});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackStep, {PS_Move});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Run, {PS_Run});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_RunEnd, {PS_Run});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_JumpUp, {PS_Jump});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_JumpDown, {PS_Jump});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_JumpLand, {PS_Jump});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Dash, {PS_Dash});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_RollingBack, {PS_Rolling});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Guard, {PS_Guard});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_GuardEnd, {PS_Idle});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Guard_Seat, {PS_Guard, PS_Seat});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_GuardEnd_Seat, {PS_Seat});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_CloseRange, {PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_CloseRange, {PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, {PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_CloseRange, {PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_LongRange, {PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_LongRange, {PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_LongRange, {PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_LongRange, {PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_Seat, {PS_Seat, PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_Seat, {PS_Seat, PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_Seat, {PS_Seat, PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_Seat, {PS_Seat, PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_Jump, {PS_Jump, PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_Jump, {PS_Jump, PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_Jump, {PS_Jump, PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_Jump, {PS_Jump, PS_Attack, PS_EnableClampOffset});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_High, {PS_Hit});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_Low, {PS_Hit});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_Strong, {PS_Hit});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_AirborneUp, {PS_Hit});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_AirborneDown, {PS_Hit});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_AirborneLand, {PS_Hit});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_AirborneGetUp, {PS_None});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_Seat, {PS_Hit, PS_Seat});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_JumpUp, {PS_Hit});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_JumpDown, {PS_Hit});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_NeckGrabbed, {PS_Hit});
  pStateComponent_->RegistState(IORI_ANIMTYPE_108ShikiYamiBarai, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_1, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_2, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_Shinigami, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_HyakushikiOniyaki, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_1, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_2, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_3, {PS_Attack});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_UltimateCasting, {PS_SkillCasting});
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_1, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_2, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_3, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_4, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_5, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_6, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_7, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_8, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_9, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_Ura306shikiShika_1, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_Ura306shikiShika_2, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_Ura306shikiShika_3, {PS_Attack});

  // RESTRICTION
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_StartPos, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Idle, {});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_SeatDown, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Seat, {});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_SeatUp, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_FrontWalk, {});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_BackWalk, {});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_BackStep, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Run, {});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_RunEnd, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_JumpUp, {});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_JumpDown, {});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_JumpLand, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Dash, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_RollingBack, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Guard, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_GuardEnd, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Guard_Seat, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_GuardEnd_Seat, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyKick_CloseRange, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightKick_CloseRange, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightPunch_CloseRange, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyKick_LongRange, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightKick_LongRange, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyPunch_LongRange, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightPunch_LongRange, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyKick_Seat, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightKick_Seat, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyPunch_Seat, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightPunch_Seat, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyKick_Jump, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightKick_Jump, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyPunch_Jump, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightPunch_Jump, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_High, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_Low, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_Strong, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_AirborneUp, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_AirborneDown, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_AirborneLand, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_AirborneGetUp, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_Seat, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_JumpUp, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_JumpDown, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_NeckGrabbed, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_108ShikiYamiBarai, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_GaishikiMutan_1, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_GaishikiMutan_2, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_Shinigami, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_HyakushikiOniyaki, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_127ShikiAoiHana_1, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_127ShikiAoiHana_2, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_127ShikiAoiHana_3, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_UltimateCasting, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_1, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_2, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_3, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_4, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_5, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_6, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_7, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_8, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_9, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_Ura306shikiShika_1, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_Ura306shikiShika_2, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_Ura306shikiShika_3, {PR_LockInput});

  // ATTACK INFO
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 200);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, true, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, 0.0f}, 200);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, -5.0f}, 200);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Shinigami, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 15.0f, {2.0f, -8.0f}, 200);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.0f, 0.0f}, 200);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.0f, 0.0f}, 200);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_3, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, 0.0f}, 200);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_1, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 200);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_2, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_3, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_4, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_5, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_6, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_7, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_8, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_9, ATTYPE_StrongAttack, ELMTTYPE_BlueFlame, EFTYPE_Iori_Explosion, false, 10.0f, {3.0f, -4.5f}, 200);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_1, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_2, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, true, 5.0f, {0.0f, -7.0f}, 100);
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

  // TODP : SKILL TEST
  // SKILL 0
  SkillFrameActionData SK0_ST0_FR0_AC0_Data0;
  SK0_ST0_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue;
  SK0_ST0_FR0_AC0_Data0.actionParams_;
  SkillFrameActionConditionData SK0_ST0_FR0_AC0_Cond0;
  SK0_ST0_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_CheckInputDownA;
  SkillFrameAction SK0_ST0_FR0_Action0;
  SK0_ST0_FR0_Action0.actionDatas_.push_back(SK0_ST0_FR0_AC0_Data0);
  SK0_ST0_FR0_Action0.conditionDatas_.push_back(SK0_ST0_FR0_AC0_Cond0);
  SkillFrameActionData SK0_ST0_FR0_AC1_Data;
  SK0_ST0_FR0_AC1_Data.actionType_ = SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue;
  SK0_ST0_FR0_AC1_Data.actionParams_;
  SkillFrameActionConditionData SK0_ST0_FR0_AC1_Cond0;
  SK0_ST0_FR0_AC1_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_CheckInputDownC;
  SkillFrameAction SK0_ST0_FR0_Action1;
  SK0_ST0_FR0_Action1.actionDatas_.push_back(SK0_ST0_FR0_AC1_Data);
  SK0_ST0_FR0_Action1.conditionDatas_.push_back(SK0_ST0_FR0_AC1_Cond0);
  SkillFrame SK0_ST0_Frame0;
  SK0_ST0_Frame0.startIndex_ = 101;
  SK0_ST0_Frame0.endIndex_ = 104;
  SK0_ST0_Frame0.actions_.push_back(SK0_ST0_FR0_Action0);
  SK0_ST0_Frame0.actions_.push_back(SK0_ST0_FR0_Action1);
  SkillFrameActionData SK0_ST0_FR1_AC0_Data0;
  SK0_ST0_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK0_ST0_FR1_AC0_Data0.actionParams_.changeStateIndex_ = 1;
  SkillFrameActionConditionData SK0_ST0_FR1_AC0_Cond0;
  SK0_ST0_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_IsStateMiscFlagTrue;
  SkillFrameActionConditionData SK0_ST0_FR1_AC0_Cond1;
  SK0_ST0_FR1_AC0_Cond1.conditionType_ = SKILL_FRAME_ACTION_COND_HasAttackCollition;
  SkillFrameAction SK0_ST0_FR1_Action0;
  SK0_ST0_FR1_Action0.actionDatas_.push_back(SK0_ST0_FR1_AC0_Data0);
  SK0_ST0_FR1_Action0.conditionDatas_.push_back(SK0_ST0_FR1_AC0_Cond0);
  SK0_ST0_FR1_Action0.conditionDatas_.push_back(SK0_ST0_FR1_AC0_Cond1);
  SkillFrame SK0_ST0_Frame1;
  SK0_ST0_Frame1.startIndex_ = 105;
  SK0_ST0_Frame1.endIndex_ = 105;
  SK0_ST0_Frame1.actions_.push_back(SK0_ST0_FR1_Action0);
  SkillState SK0_State0;
  SK0_State0.animState_ = IORI_ANIMTYPE_GaishikiMutan_1;
  SK0_State0.frames_.push_back(SK0_ST0_Frame0);
  SK0_State0.frames_.push_back(SK0_ST0_Frame1);
  SkillState SK0_State1;
  SK0_State1.animState_ = IORI_ANIMTYPE_GaishikiMutan_2;
  Skill Skill_0;
  Skill_0.skillTag_ = SKILL_TYPE::SKILL_0;
  Skill_0.castCondition_ = SKILL_CAST_COND_None;
  Skill_0.skillStates_.push_back(SK0_State0);
  Skill_0.skillStates_.push_back(SK0_State1);
  pSkillComponent_->RegistSkill(Skill_0);

  // SKILL 1
  SkillFrameActionData SK1_ST0_FR0_AC0_Data0;
  SK1_ST0_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_SpawnEffect;
  SK1_ST0_FR0_AC0_Data0.actionParams_.effectType_ = EFTYPE_Iori_Casting_YamiBarai;
  SK1_ST0_FR0_AC0_Data0.actionParams_.spawnEffectPos_ = {40.0f, -280.0f};
  SkillFrameActionConditionData SK1_ST0_FR0_AC0_Cond0;
  SK1_ST0_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK1_ST0_FR0_Action0;
  SK1_ST0_FR0_Action0.actionDatas_.push_back(SK1_ST0_FR0_AC0_Data0);
  SK1_ST0_FR0_Action0.conditionDatas_.push_back(SK1_ST0_FR0_AC0_Cond0);
  SkillFrame SK1_ST0_Frame0;
  SK1_ST0_Frame0.startIndex_ = 225;
  SK1_ST0_Frame0.endIndex_ = 225;
  SK1_ST0_Frame0.actions_.push_back(SK1_ST0_FR0_Action0);
  SkillFrameActionData SK1_ST0_FR1_AC0_Data0;
  SK1_ST0_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_FireProjectile;
  SK1_ST0_FR1_AC0_Data0.actionParams_.projectileType_ = IORI_PROJECTILE_YamiBarai;
  SkillFrameActionConditionData SK1_ST0_FR1_AC0_Cond0;
  SK1_ST0_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK1_ST0_FR1_Action0;
  SK1_ST0_FR1_Action0.actionDatas_.push_back(SK1_ST0_FR1_AC0_Data0);
  SK1_ST0_FR1_Action0.conditionDatas_.push_back(SK1_ST0_FR1_AC0_Cond0);
  SkillFrame SK1_ST0_Frame1;
  SK1_ST0_Frame1.startIndex_ = 226;
  SK1_ST0_Frame1.endIndex_ = 226;
  SK1_ST0_Frame1.actions_.push_back(SK1_ST0_FR1_Action0);
  SkillState SK1_State0;
  SK1_State0.animState_ = IORI_ANIMTYPE_108ShikiYamiBarai;
  SK1_State0.frames_.push_back(SK1_ST0_Frame0);
  SK1_State0.frames_.push_back(SK1_ST0_Frame1);
  Skill skill_1;
  skill_1.skillTag_ = SKILL_1;
  skill_1.castCondition_ = SKILL_CAST_COND_None;
  skill_1.skillStates_.push_back(SK1_State0);
  pSkillComponent_->RegistSkill(skill_1);

  // SKILL 2
  SkillFrameActionData SK2_ST0_FR0_AC0_Data0;
  SK2_ST0_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_MovementDash;
  SK2_ST0_FR0_AC0_Data0.actionParams_.dashDuration_ = 150.0f;
  SK2_ST0_FR0_AC0_Data0.actionParams_.dashDistance_ = 150.0f;
  SkillFrameActionConditionData SK2_ST0_FR0_AC0_Cond0;
  SK2_ST0_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK2_ST0_FR0_Action0;
  SK2_ST0_FR0_Action0.actionDatas_.push_back(SK2_ST0_FR0_AC0_Data0);
  SK2_ST0_FR0_Action0.conditionDatas_.push_back(SK2_ST0_FR0_AC0_Cond0);
  SkillFrame SK2_ST0_Frame0;
  SK2_ST0_Frame0.startIndex_ = 276;
  SK2_ST0_Frame0.endIndex_ = 276;
  SK2_ST0_Frame0.actions_.push_back(SK2_ST0_FR0_Action0);
  SkillFrameActionData SK2_ST0_FR1_AC0_Data0;
  SK2_ST0_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_MovementJump;
  SK2_ST0_FR1_AC0_Data0.actionParams_.jumpForce_ = {0.4f, -4.5f};
  SkillFrameActionConditionData SK2_ST0_FR1_AC0_Cond0;
  SK2_ST0_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK2_ST0_FR1_Action0;
  SK2_ST0_FR1_Action0.actionDatas_.push_back(SK2_ST0_FR1_AC0_Data0);
  SK2_ST0_FR1_Action0.conditionDatas_.push_back(SK2_ST0_FR1_AC0_Cond0);
  SkillFrameActionData SK2_ST0_FR1_AC1_Data0;
  SK2_ST0_FR1_AC1_Data0.actionType_ = SKILL_FRAME_ACTION_FireProjectile;
  SK2_ST0_FR1_AC1_Data0.actionParams_.projectileType_ = IORI_PROJECTILE_HyakushikiOniyaki_Low;
  SkillFrameActionConditionData SK2_ST0_FR1_AC1_Cond0;
  SK2_ST0_FR1_AC1_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK2_ST0_FR1_Action1;
  SK2_ST0_FR1_Action1.actionDatas_.push_back(SK2_ST0_FR1_AC1_Data0);
  SK2_ST0_FR1_Action1.conditionDatas_.push_back(SK2_ST0_FR1_AC1_Cond0);
  SkillFrame SK2_ST0_Frame1;
  SK2_ST0_Frame1.startIndex_ = 281;
  SK2_ST0_Frame1.endIndex_ = 281;
  SK2_ST0_Frame1.actions_.push_back(SK2_ST0_FR1_Action0);
  SK2_ST0_Frame1.actions_.push_back(SK2_ST0_FR1_Action1);
  SkillFrameActionData SK2_ST0_FR2_AC0_Data0;
  SK2_ST0_FR2_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_FireProjectile;
  SK2_ST0_FR2_AC0_Data0.actionParams_.projectileType_ = IORI_PROJECTILE_HyakushikiOniyaki_High;
  SkillFrameActionConditionData SK2_ST0_FR2_AC0_Cond0;
  SK2_ST0_FR2_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK2_ST0_FR2_Action0;
  SK2_ST0_FR2_Action0.actionDatas_.push_back(SK2_ST0_FR2_AC0_Data0);
  SK2_ST0_FR2_Action0.conditionDatas_.push_back(SK2_ST0_FR2_AC0_Cond0);
  SkillFrame SK2_ST0_Frame2;
  SK2_ST0_Frame2.startIndex_ = 284;
  SK2_ST0_Frame2.endIndex_ = 284;
  SK2_ST0_Frame2.actions_.push_back(SK2_ST0_FR2_Action0);
  SkillState SK2_State0;
  SK2_State0.animState_ = IORI_ANIMTYPE_HyakushikiOniyaki;
  SK2_State0.frames_.push_back(SK2_ST0_Frame0);
  SK2_State0.frames_.push_back(SK2_ST0_Frame1);
  SK2_State0.frames_.push_back(SK2_ST0_Frame2);
  Skill Skill_2;
  Skill_2.skillTag_ = SKILL_2;
  Skill_2.castCondition_ = SKILL_CAST_COND_None;
  Skill_2.skillStates_.push_back(SK2_State0);
  pSkillComponent_->RegistSkill(Skill_2);

  // SKILL 3
  SkillFrameActionData SK3_ST0_FR0_AC0_Data0;
  SK3_ST0_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_MovementDash;
  SK3_ST0_FR0_AC0_Data0.actionParams_.dashDuration_ = 150.0f;
  SK3_ST0_FR0_AC0_Data0.actionParams_.dashDistance_ = 80.0f;
  SkillFrameActionConditionData SK3_ST0_FR0_AC0_Cond0;
  SK3_ST0_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK3_ST0_FR0_Action0;
  SK3_ST0_FR0_Action0.actionDatas_.push_back(SK3_ST0_FR0_AC0_Data0);
  SK3_ST0_FR0_Action0.conditionDatas_.push_back(SK3_ST0_FR0_AC0_Cond0);
  SkillFrame SK3_ST0_Frame0;
  SK3_ST0_Frame0.startIndex_ = 257;
  SK3_ST0_Frame0.endIndex_ = 257;
  SK3_ST0_Frame0.actions_.push_back(SK3_ST0_FR0_Action0);
  SkillFrameActionData SK3_ST0_FR1_AC0_Data0;
  SK3_ST0_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue;
  SK3_ST0_FR1_AC0_Data0.actionParams_;
  SkillFrameActionConditionData SK3_ST0_FR1_AC0_Cond0;
  SK3_ST0_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_CheckInputDownA;
  SkillFrameAction SK3_ST0_FR1_Action0;
  SK3_ST0_FR1_Action0.actionDatas_.push_back(SK3_ST0_FR1_AC0_Data0);
  SK3_ST0_FR1_Action0.conditionDatas_.push_back(SK3_ST0_FR1_AC0_Cond0);
  SkillFrameActionData SK3_ST0_FR1_AC1_Data0;
  SK3_ST0_FR1_AC1_Data0.actionType_ = SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue;
  SK3_ST0_FR1_AC1_Data0.actionParams_;
  SkillFrameActionConditionData SK3_ST0_FR1_AC1_Cond0;
  SK3_ST0_FR1_AC1_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_CheckInputDownC;
  SkillFrameAction SK3_ST0_FR1_Action1;
  SK3_ST0_FR1_Action1.actionDatas_.push_back(SK3_ST0_FR1_AC1_Data0);
  SK3_ST0_FR1_Action1.conditionDatas_.push_back(SK3_ST0_FR1_AC1_Cond0);
  SkillFrame SK3_ST0_Frame1;
  SK3_ST0_Frame1.startIndex_ = 257;
  SK3_ST0_Frame1.endIndex_ = 260;
  SK3_ST0_Frame1.actions_.push_back(SK3_ST0_FR1_Action0);
  SK3_ST0_Frame1.actions_.push_back(SK3_ST0_FR1_Action1);
  SkillFrameActionData SK3_ST0_FR2_AC0_Data0;
  SK3_ST0_FR2_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK3_ST0_FR2_AC0_Data0.actionParams_.changeStateIndex_ = 1;
  SkillFrameActionConditionData SK3_ST0_FR2_AC0_Cond0;
  SK3_ST0_FR2_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_HasAttackCollition;
  SkillFrameActionConditionData SK3_ST0_FR2_AC0_Cond1;
  SK3_ST0_FR2_AC0_Cond1.conditionType_ = SKILL_FRAME_ACTION_COND_IsStateMiscFlagTrue;
  SkillFrameAction SK3_ST0_FR2_Action0;
  SK3_ST0_FR2_Action0.actionDatas_.push_back(SK3_ST0_FR2_AC0_Data0);
  SK3_ST0_FR2_Action0.conditionDatas_.push_back(SK3_ST0_FR2_AC0_Cond0);
  SK3_ST0_FR2_Action0.conditionDatas_.push_back(SK3_ST0_FR2_AC0_Cond1);
  SkillFrame SK3_ST0_Frame2;
  SK3_ST0_Frame2.startIndex_ = 260;
  SK3_ST0_Frame2.endIndex_ = 260;
  SK3_ST0_Frame2.actions_.push_back(SK3_ST0_FR2_Action0);
  SkillState SK3_State0;
  SK3_State0.animState_ = IORI_ANIMTYPE_127ShikiAoiHana_1;
  SK3_State0.frames_.push_back(SK3_ST0_Frame0);
  SK3_State0.frames_.push_back(SK3_ST0_Frame1);
  SK3_State0.frames_.push_back(SK3_ST0_Frame2);
  SkillFrameActionData SK3_ST1_FR0_AC0_Data0;
  SK3_ST1_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_MovementDash;
  SK3_ST1_FR0_AC0_Data0.actionParams_.dashDuration_ = 150.0f;
  SK3_ST1_FR0_AC0_Data0.actionParams_.dashDistance_ = 80.0f;
  SkillFrameActionConditionData SK3_ST1_FR0_AC0_Cond0;
  SK3_ST1_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK3_ST1_FR0_Action0;
  SK3_ST1_FR0_Action0.actionDatas_.push_back(SK3_ST1_FR0_AC0_Data0);
  SK3_ST1_FR0_Action0.conditionDatas_.push_back(SK3_ST1_FR0_AC0_Cond0);
  SkillFrame SK3_ST1_Frame0;
  SK3_ST1_Frame0.startIndex_ = 262;
  SK3_ST1_Frame0.endIndex_ = 262;
  SK3_ST1_Frame0.actions_.push_back(SK3_ST1_FR0_Action0);
  SkillFrameActionData SK3_ST1_FR1_AC0_Data0;
  SK3_ST1_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue;
  SK3_ST1_FR1_AC0_Data0.actionParams_;
  SkillFrameActionConditionData SK3_ST1_FR1_AC0_Cond0;
  SK3_ST1_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_CheckInputDownA;
  SkillFrameAction SK3_ST1_FR1_Action0;
  SK3_ST1_FR1_Action0.actionDatas_.push_back(SK3_ST1_FR1_AC0_Data0);
  SK3_ST1_FR1_Action0.conditionDatas_.push_back(SK3_ST1_FR1_AC0_Cond0);
  SkillFrameActionData SK3_ST1_FR1_AC1_Data0;
  SK3_ST1_FR1_AC1_Data0.actionType_ = SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue;
  SK3_ST1_FR1_AC1_Data0.actionParams_;
  SkillFrameActionConditionData SK3_ST1_FR1_AC1_Cond0;
  SK3_ST1_FR1_AC1_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_CheckInputDownC;
  SkillFrameAction SK3_ST1_FR1_Action1;
  SK3_ST1_FR1_Action1.actionDatas_.push_back(SK3_ST1_FR1_AC1_Data0);
  SK3_ST1_FR1_Action1.conditionDatas_.push_back(SK3_ST1_FR1_AC1_Cond0);
  SkillFrame SK3_ST1_Frame1;
  SK3_ST1_Frame1.startIndex_ = 264;
  SK3_ST1_Frame1.endIndex_ = 267;
  SK3_ST1_Frame1.actions_.push_back(SK3_ST1_FR1_Action0);
  SK3_ST1_Frame1.actions_.push_back(SK3_ST1_FR1_Action1);
  SkillFrameActionData SK3_ST1_FR2_AC0_Data0;
  SK3_ST1_FR2_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK3_ST1_FR2_AC0_Data0.actionParams_.changeStateIndex_ = 2;
  SkillFrameActionConditionData SK3_ST1_FR2_AC0_Cond0;
  SK3_ST1_FR2_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_HasAttackCollition;
  SkillFrameActionConditionData SK3_ST1_FR2_AC0_Cond1;
  SK3_ST1_FR2_AC0_Cond1.conditionType_ = SKILL_FRAME_ACTION_COND_IsStateMiscFlagTrue;
  SkillFrameAction SK3_ST1_FR2_Action0;
  SK3_ST1_FR2_Action0.actionDatas_.push_back(SK3_ST1_FR2_AC0_Data0);
  SK3_ST1_FR2_Action0.conditionDatas_.push_back(SK3_ST1_FR2_AC0_Cond0);
  SK3_ST1_FR2_Action0.conditionDatas_.push_back(SK3_ST1_FR2_AC0_Cond1);
  SkillFrame SK3_ST1_Frame2;
  SK3_ST1_Frame2.startIndex_ = 267;
  SK3_ST1_Frame2.endIndex_ = 267;
  SK3_ST1_Frame2.actions_.push_back(SK3_ST1_FR2_Action0);
  SkillState SK3_State1;
  SK3_State1.animState_ = IORI_ANIMTYPE_127ShikiAoiHana_2;
  SK3_State1.frames_.push_back(SK3_ST1_Frame0);
  SK3_State1.frames_.push_back(SK3_ST1_Frame1);
  SK3_State1.frames_.push_back(SK3_ST1_Frame2);
  SkillFrameActionData SK3_ST2_FR0_AC0_Data0;
  SK3_ST2_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_MovementJump;
  SK3_ST2_FR0_AC0_Data0.actionParams_.jumpForce_ = {0.3f, -3.0f};
  SkillFrameActionConditionData SK3_ST2_FR0_AC0_Cond0;
  SK3_ST2_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK3_ST2_FR0_Action0;
  SK3_ST2_FR0_Action0.actionDatas_.push_back(SK3_ST2_FR0_AC0_Data0);
  SK3_ST2_FR0_Action0.conditionDatas_.push_back(SK3_ST2_FR0_AC0_Cond0);
  SkillFrame SK3_ST2_Frame0;
  SK3_ST2_Frame0.startIndex_ = 269;
  SK3_ST2_Frame0.endIndex_ = 269;
  SK3_ST2_Frame0.actions_.push_back(SK3_ST2_FR0_Action0);
  SkillState SK3_State2;
  SK3_State2.animState_ = IORI_ANIMTYPE_127ShikiAoiHana_3;
  SK3_State2.frames_.push_back(SK3_ST2_Frame0);
  Skill Skill_3;
  Skill_3.skillTag_ = SKILL_3;
  Skill_3.castCondition_ = SKILL_CAST_COND_None;
  Skill_3.skillStates_.push_back(SK3_State0);
  Skill_3.skillStates_.push_back(SK3_State1);
  Skill_3.skillStates_.push_back(SK3_State2);
  pSkillComponent_->RegistSkill(Skill_3);


  // SKILL 4
  SkillFrameActionData SK4_ST0_FR0_AC0_Data0;
  SK4_ST0_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_MovementJump;
  SK4_ST0_FR0_AC0_Data0.actionParams_.jumpForce_ = {1.7f, -2.3f};
  SkillFrameActionConditionData SK4_ST0_FR0_AC0_Cond0;
  SK4_ST0_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK4_ST0_FR0_Action0;
  SK4_ST0_FR0_Action0.conditionDatas_.push_back(SK4_ST0_FR0_AC0_Cond0);
  SK4_ST0_FR0_Action0.actionDatas_.push_back(SK4_ST0_FR0_AC0_Data0);
  SkillFrame SK4_ST0_Frame0;
  SK4_ST0_Frame0.startIndex_ = 145;
  SK4_ST0_Frame0.endIndex_ = 145;
  SK4_ST0_Frame0.actions_.push_back(SK4_ST0_FR0_Action0);
  SkillState SK4_State0;
  SK4_State0.animState_ = IORI_ANIMTYPE_Shinigami;
  SK4_State0.frames_.push_back(SK4_ST0_Frame0);
  Skill skill_4;
  skill_4.skillTag_ = SKILL_4;
  skill_4.castCondition_ = SKILL_CAST_COND_None;
  skill_4.skillStates_.push_back(SK4_State0);
  pSkillComponent_->RegistSkill(skill_4);


  // SKILL 5
  SkillFrameActionData SK5_ST0_FR0_AC0_Data0;
  SK5_ST0_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_SpawnEffect;
  SK5_ST0_FR0_AC0_Data0.actionParams_.effectType_ = EFTYPE_Casting_1;
  SK5_ST0_FR0_AC0_Data0.actionParams_.spawnEffectPos_ = {0.0f, -500.0f};
  SkillFrameActionConditionData SK5_ST0_FR0_AC0_Cond0;
  SK5_ST0_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST0_FR0_Action0;
  SK5_ST0_FR0_Action0.actionDatas_.push_back(SK5_ST0_FR0_AC0_Data0);
  SK5_ST0_FR0_Action0.conditionDatas_.push_back(SK5_ST0_FR0_AC0_Cond0);
  SkillFrameActionData SK5_ST0_FR0_AC1_Data0;
  SK5_ST0_FR0_AC1_Data0.actionType_ = SKILL_FRAME_ACTION_SpawnEffect;
  SK5_ST0_FR0_AC1_Data0.actionParams_.effectType_ = EFTYPE_Casting_2;
  SK5_ST0_FR0_AC1_Data0.actionParams_.spawnEffectPos_ = {0.0f, -500.0f};
  SkillFrameActionConditionData SK5_ST0_FR0_AC1_Cond0;
  SK5_ST0_FR0_AC1_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST0_FR0_Action1;
  SK5_ST0_FR0_Action1.actionDatas_.push_back(SK5_ST0_FR0_AC1_Data0);
  SK5_ST0_FR0_Action1.conditionDatas_.push_back(SK5_ST0_FR0_AC1_Cond0);
  SkillFrameActionData SK5_ST0_FR0_AC2_Data0;
  SK5_ST0_FR0_AC2_Data0.actionType_ = SKILL_FRAME_ACTION_FreezeOpponentPlayer;
  SK5_ST0_FR0_AC2_Data0.actionParams_.isInfiniteFreeze_ = true;
  SkillFrameActionConditionData SK5_ST0_FR0_AC2_Cond0;
  SK5_ST0_FR0_AC2_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST0_FR0_Action2;
  SK5_ST0_FR0_Action2.actionDatas_.push_back(SK5_ST0_FR0_AC2_Data0);
  SK5_ST0_FR0_Action2.conditionDatas_.push_back(SK5_ST0_FR0_AC2_Cond0);
  SkillFrameActionData SK5_ST0_FR0_AC3_Data0;
  SK5_ST0_FR0_AC3_Data0.actionType_ = SKILL_FRAME_ACTION_FadeOut;
  SK5_ST0_FR0_AC3_Data0.actionParams_.fadeDuration_ = 50;
  SK5_ST0_FR0_AC3_Data0.actionParams_.fadeImageType_ = IMGTYPE_BlackBoardImage;
  SkillFrameActionConditionData SK5_ST0_FR0_AC3_Cond0;
  SK5_ST0_FR0_AC3_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SK5_ST0_FR0_AC3_Cond0.conditionParams_;
  SkillFrameAction SK5_ST0_FR0_Action3;
  SK5_ST0_FR0_Action3.conditionDatas_.push_back(SK5_ST0_FR0_AC3_Cond0);
  SK5_ST0_FR0_Action3.actionDatas_.push_back(SK5_ST0_FR0_AC3_Data0);
  SkillFrame SK5_ST0_Frame0;
  SK5_ST0_Frame0.startIndex_ = 344;
  SK5_ST0_Frame0.endIndex_ = 344;
  SK5_ST0_Frame0.actions_.push_back(SK5_ST0_FR0_Action0);
  SK5_ST0_Frame0.actions_.push_back(SK5_ST0_FR0_Action1);
  SK5_ST0_Frame0.actions_.push_back(SK5_ST0_FR0_Action2);
  SK5_ST0_Frame0.actions_.push_back(SK5_ST0_FR0_Action3);
  SkillFrameActionData SK5_ST0_FR1_AC0_Data0;
  SK5_ST0_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK5_ST0_FR1_AC0_Data0.actionParams_.changeStateIndex_ = 1;
  SkillFrameActionConditionData SK5_ST0_FR1_AC0_Cond0;
  SK5_ST0_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_AnimationEnd;
  SkillFrameAction SK5_ST0_FR1_Action0;
  SK5_ST0_FR1_Action0.actionDatas_.push_back(SK5_ST0_FR1_AC0_Data0);
  SK5_ST0_FR1_Action0.conditionDatas_.push_back(SK5_ST0_FR1_AC0_Cond0);
  SkillFrame SK5_ST0_Frame1;
  SK5_ST0_Frame1.startIndex_ = 347;
  SK5_ST0_Frame1.endIndex_ = 347;
  SK5_ST0_Frame1.actions_.push_back(SK5_ST0_FR1_Action0);
  SkillState SK5_State0;
  SK5_State0.animState_ = PLAYER_ANIMTYPE_UltimateCasting;
  SK5_State0.frames_.push_back(SK5_ST0_Frame0);
  SK5_State0.frames_.push_back(SK5_ST0_Frame1);
  SkillFrameActionData SK5_ST1_FR0_AC0_Data0;
  SK5_ST1_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_DefreezeOpponentPlayer;
  SK5_ST1_FR0_AC0_Data0.actionParams_;
  SkillFrameActionConditionData SK5_ST1_FR0_AC0_Cond0;
  SK5_ST1_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK5_ST1_FR0_AC0_Data1;
  SK5_ST1_FR0_AC0_Data1.actionType_ = SKILL_FRAME_ACTION_FadeIn;
  SK5_ST1_FR0_AC0_Data1.actionParams_.fadeDuration_ = 50;
  SkillFrameActionConditionData SK5_ST1_FR0_AC0_Cond1;
  SK5_ST1_FR0_AC0_Cond1.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST1_FR0_Action0;
  SK5_ST1_FR0_Action0.actionDatas_.push_back(SK5_ST1_FR0_AC0_Data0);
  SK5_ST1_FR0_Action0.conditionDatas_.push_back(SK5_ST1_FR0_AC0_Cond0);
  SK5_ST1_FR0_Action0.actionDatas_.push_back(SK5_ST1_FR0_AC0_Data1);
  SK5_ST1_FR0_Action0.conditionDatas_.push_back(SK5_ST1_FR0_AC0_Cond1);
  SkillFrame SK5_ST1_Frame0;
  SK5_ST1_Frame0.startIndex_ = 70;
  SK5_ST1_Frame0.endIndex_ = 70;
  SK5_ST1_Frame0.actions_.push_back(SK5_ST1_FR0_Action0);
  SkillFrameActionData SK5_ST1_FR1_AC0_Data0;
  SK5_ST1_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_MovementDash;
  SK5_ST1_FR1_AC0_Data0.actionParams_.dashDuration_ = 250.0f;
  SK5_ST1_FR1_AC0_Data0.actionParams_.dashDistance_ = 1000.0f;
  SkillFrameActionConditionData SK5_ST1_FR1_AC0_Cond0;
  SK5_ST1_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST1_FR1_Action0;
  SK5_ST1_FR1_Action0.actionDatas_.push_back(SK5_ST1_FR1_AC0_Data0);
  SK5_ST1_FR1_Action0.conditionDatas_.push_back(SK5_ST1_FR1_AC0_Cond0);
  SkillFrame SK5_ST1_Frame1;
  SK5_ST1_Frame1.startIndex_ = 72;
  SK5_ST1_Frame1.endIndex_ = 72;
  SK5_ST1_Frame1.actions_.push_back(SK5_ST1_FR1_Action0);
  SkillFrameActionConditionData SK5_ST1_FR2_AC0_Cond0;
  SK5_ST1_FR2_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_HasAttackCollition;
  SkillFrameActionData SK5_ST1_FR2_AC0_Data0;
  SK5_ST1_FR2_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_InflictStunOpponentPlayer;
  SK5_ST1_FR2_AC0_Data0.actionParams_;
  SkillFrameActionData SK5_ST1_FR2_AC0_Data1;
  SK5_ST1_FR2_AC0_Data1.actionType_ = SKILL_FRAME_ACTION_MovementDash;
  SK5_ST1_FR2_AC0_Data1.actionParams_.dashDuration_ = 250.0f;
  SK5_ST1_FR2_AC0_Data1.actionParams_.dashDistance_ = 1000.0f;
  SkillFrameAction SK5_ST1_FR2_Action0;
  SK5_ST1_FR2_Action0.conditionDatas_.push_back(SK5_ST1_FR2_AC0_Cond0);
  SK5_ST1_FR2_Action0.actionDatas_.push_back(SK5_ST1_FR2_AC0_Data0);
  SK5_ST1_FR2_Action0.actionDatas_.push_back(SK5_ST1_FR2_AC0_Data1);
  SkillFrameActionConditionData SK5_ST1_FR2_AC1_Cond0;
  SK5_ST1_FR2_AC1_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_HasAttackCollition;
  SkillFrameActionConditionData SK5_ST1_FR2_AC1_Cond1;
  SK5_ST1_FR2_AC1_Cond1.conditionType_ = SKILL_FRAME_ACTION_COND_IsOpponentWithinDistanceThresHold;
  SK5_ST1_FR2_AC1_Cond1.conditionParams_.opponentDistanceThreshold = 240.0f;
  SkillFrameActionData SK5_ST1_FR2_AC1_Data0;
  SK5_ST1_FR2_AC1_Data0.actionType_ = SKILL_FRAME_ACTION_MovementStopDash;
  SkillFrameActionData SK5_ST1_FR2_AC1_Data1;
  SK5_ST1_FR2_AC1_Data1.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK5_ST1_FR2_AC1_Data1.actionParams_.changeStateIndex_ = 2;
  SkillFrameAction SK5_ST1_FR2_Action1;
  SK5_ST1_FR2_Action1.conditionDatas_.push_back(SK5_ST1_FR2_AC1_Cond0);
  SK5_ST1_FR2_Action1.conditionDatas_.push_back(SK5_ST1_FR2_AC1_Cond1);
  SK5_ST1_FR2_Action1.actionDatas_.push_back(SK5_ST1_FR2_AC1_Data0);
  SK5_ST1_FR2_Action1.actionDatas_.push_back(SK5_ST1_FR2_AC1_Data1);
  SkillFrame SK5_ST1_Frame2;
  SK5_ST1_Frame2.startIndex_ = 70;
  SK5_ST1_Frame2.endIndex_ = 77;
  SK5_ST1_Frame2.actions_.push_back(SK5_ST1_FR2_Action0);
  SK5_ST1_Frame2.actions_.push_back(SK5_ST1_FR2_Action1);
  SkillState SK5_State1;
  SK5_State1.animState_ = IORI_ANIMTYPE_1211ShikiYaOtome_1;
  SK5_State1.frames_.push_back(SK5_ST1_Frame0);
  SK5_State1.frames_.push_back(SK5_ST1_Frame1);
  SK5_State1.frames_.push_back(SK5_ST1_Frame2);

  SkillFrameActionData SK5_ST2_FR0_AC0_Data0;
  SK5_ST2_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_FadeInOut;
  SK5_ST2_FR0_AC0_Data0.actionParams_.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST2_FR0_AC0_Data0.actionParams_.fadeDuration_ = 50;
  SkillFrameActionConditionData SK5_ST2_FR0_AC0_Cond0;
  SK5_ST2_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST2_FR0_Action0;
  SK5_ST2_FR0_Action0.actionDatas_.push_back(SK5_ST2_FR0_AC0_Data0);
  SK5_ST2_FR0_Action0.conditionDatas_.push_back(SK5_ST2_FR0_AC0_Cond0);
  SkillFrame SK5_ST2_Frame0;
  SK5_ST2_Frame0.startIndex_ = 120;
  SK5_ST2_Frame0.endIndex_ = 120;
  SK5_ST2_Frame0.actions_.push_back(SK5_ST2_FR0_Action0);
  SkillFrameActionData SK5_ST2_FR1_AC0_Data0;
  SK5_ST2_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK5_ST2_FR1_AC0_Data0.actionParams_.changeStateIndex_ = 3;
  SkillFrameActionConditionData SK5_ST2_FR1_AC0_Cond0;
  SK5_ST2_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST2_FR1_Action0;
  SK5_ST2_FR1_Action0.conditionDatas_.push_back(SK5_ST2_FR1_AC0_Cond0);
  SK5_ST2_FR1_Action0.actionDatas_.push_back(SK5_ST2_FR1_AC0_Data0);
  SkillFrame SK5_ST2_Frame1;
  SK5_ST2_Frame1.startIndex_ = 122;
  SK5_ST2_Frame1.endIndex_ = 122;
  SK5_ST2_Frame1.actions_.push_back(SK5_ST2_FR1_Action0);
  SkillState SK5_State2;
  SK5_State2.animState_ = IORI_ANIMTYPE_1211ShikiYaOtome_2;
  SK5_State2.frames_.push_back(SK5_ST2_Frame0);
  SK5_State2.frames_.push_back(SK5_ST2_Frame1);
  SkillFrameActionData SK5_ST3_FR0_AC0_Data0;
  SK5_ST3_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_FadeInOut;
  SK5_ST3_FR0_AC0_Data0.actionParams_.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST3_FR0_AC0_Data0.actionParams_.fadeDuration_ = 50;
  SkillFrameActionConditionData SK5_ST3_FR0_AC0_Cond0;
  SK5_ST3_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST3_FR0_Action0;
  SK5_ST3_FR0_Action0.actionDatas_.push_back(SK5_ST3_FR0_AC0_Data0);
  SK5_ST3_FR0_Action0.conditionDatas_.push_back(SK5_ST3_FR0_AC0_Cond0);
  SkillFrame SK5_ST3_Frame0;
  SK5_ST3_Frame0.startIndex_ = 90;
  SK5_ST3_Frame0.endIndex_ = 90;
  SK5_ST3_Frame0.actions_.push_back(SK5_ST3_FR0_Action0);
  SkillFrameActionData SK5_ST3_FR1_AC0_Data0;
  SK5_ST3_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK5_ST3_FR1_AC0_Data0.actionParams_.changeStateIndex_ = 4;
  SkillFrameActionConditionData SK5_ST3_FR1_AC0_Cond0;
  SK5_ST3_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST3_FR1_Action0;
  SK5_ST3_FR1_Action0.conditionDatas_.push_back(SK5_ST3_FR1_AC0_Cond0);
  SK5_ST3_FR1_Action0.actionDatas_.push_back(SK5_ST3_FR1_AC0_Data0);
  SkillFrame SK5_ST3_Frame1;
  SK5_ST3_Frame1.startIndex_ = 92;
  SK5_ST3_Frame1.endIndex_ = 92;
  SK5_ST3_Frame1.actions_.push_back(SK5_ST3_FR1_Action0);
  SkillState SK5_State3;
  SK5_State3.animState_ = IORI_ANIMTYPE_1211ShikiYaOtome_3;
  SK5_State3.frames_.push_back(SK5_ST3_Frame0);
  SK5_State3.frames_.push_back(SK5_ST3_Frame1);

  SkillFrameActionData SK5_ST4_FR0_AC0_Data0;
  SK5_ST4_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_FadeInOut;
  SK5_ST4_FR0_AC0_Data0.actionParams_.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST4_FR0_AC0_Data0.actionParams_.fadeDuration_ = 50;
  SkillFrameActionConditionData SK5_ST4_FR0_AC0_Cond0;
  SK5_ST4_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST4_FR0_Action0;
  SK5_ST4_FR0_Action0.actionDatas_.push_back(SK5_ST4_FR0_AC0_Data0);
  SK5_ST4_FR0_Action0.conditionDatas_.push_back(SK5_ST4_FR0_AC0_Cond0);
  SkillFrame SK5_ST4_Frame0;
  SK5_ST4_Frame0.startIndex_ = 132;
  SK5_ST4_Frame0.endIndex_ = 132;
  SK5_ST4_Frame0.actions_.push_back(SK5_ST4_FR0_Action0);
  SkillFrameActionData SK5_ST4_FR1_AC0_Data0;
  SK5_ST4_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK5_ST4_FR1_AC0_Data0.actionParams_.changeStateIndex_ = 5;
  SkillFrameActionConditionData SK5_ST4_FR1_AC0_Cond0;
  SK5_ST4_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST4_FR1_Action0;
  SK5_ST4_FR1_Action0.conditionDatas_.push_back(SK5_ST4_FR1_AC0_Cond0);
  SK5_ST4_FR1_Action0.actionDatas_.push_back(SK5_ST4_FR1_AC0_Data0);
  SkillFrame SK5_ST4_Frame1;
  SK5_ST4_Frame1.startIndex_ = 135;
  SK5_ST4_Frame1.endIndex_ = 135;
  SK5_ST4_Frame1.actions_.push_back(SK5_ST4_FR1_Action0);
  SkillState SK5_State4;
  SK5_State4.animState_ = IORI_ANIMTYPE_1211ShikiYaOtome_4;
  SK5_State4.frames_.push_back(SK5_ST4_Frame0);
  SK5_State4.frames_.push_back(SK5_ST4_Frame1);

  SkillFrameActionData SK5_ST5_FR0_AC0_Data0;
  SK5_ST5_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_FadeInOut;
  SK5_ST5_FR0_AC0_Data0.actionParams_.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST5_FR0_AC0_Data0.actionParams_.fadeDuration_ = 50;
  SkillFrameActionConditionData SK5_ST5_FR0_AC0_Cond0;
  SK5_ST5_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST5_FR0_Action0;
  SK5_ST5_FR0_Action0.actionDatas_.push_back(SK5_ST5_FR0_AC0_Data0);
  SK5_ST5_FR0_Action0.conditionDatas_.push_back(SK5_ST5_FR0_AC0_Cond0);
  SkillFrame SK5_ST5_Frame0;
  SK5_ST5_Frame0.startIndex_ = 227;
  SK5_ST5_Frame0.endIndex_ = 227;
  SK5_ST5_Frame0.actions_.push_back(SK5_ST5_FR0_Action0);
  SkillFrameActionData SK5_ST5_FR1_AC0_Data0;
  SK5_ST5_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK5_ST5_FR1_AC0_Data0.actionParams_.changeStateIndex_ = 6;
  SkillFrameActionConditionData SK5_ST5_FR1_AC0_Cond0;
  SK5_ST5_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST5_FR1_Action0;
  SK5_ST5_FR1_Action0.conditionDatas_.push_back(SK5_ST5_FR1_AC0_Cond0);
  SK5_ST5_FR1_Action0.actionDatas_.push_back(SK5_ST5_FR1_AC0_Data0);
  SkillFrame SK5_ST5_Frame1;
  SK5_ST5_Frame1.startIndex_ = 229;
  SK5_ST5_Frame1.endIndex_ = 229;
  SK5_ST5_Frame1.actions_.push_back(SK5_ST5_FR1_Action0);
  SkillState SK5_State5;
  SK5_State5.animState_ = IORI_ANIMTYPE_1211ShikiYaOtome_5;
  SK5_State5.frames_.push_back(SK5_ST5_Frame0);
  SK5_State5.frames_.push_back(SK5_ST5_Frame1);

  SkillFrameActionData SK5_ST6_FR0_AC0_Data0;
  SK5_ST6_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_FadeInOut;
  SK5_ST6_FR0_AC0_Data0.actionParams_.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST6_FR0_AC0_Data0.actionParams_.fadeDuration_ = 50;
  SkillFrameActionConditionData SK5_ST6_FR0_AC0_Cond0;
  SK5_ST6_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST6_FR0_Action0;
  SK5_ST6_FR0_Action0.actionDatas_.push_back(SK5_ST6_FR0_AC0_Data0);
  SK5_ST6_FR0_Action0.conditionDatas_.push_back(SK5_ST6_FR0_AC0_Cond0);
  SkillFrame SK5_ST6_Frame0;
  SK5_ST6_Frame0.startIndex_ = 102;
  SK5_ST6_Frame0.endIndex_ = 102;
  SK5_ST6_Frame0.actions_.push_back(SK5_ST6_FR0_Action0);
  SkillFrameActionData SK5_ST6_FR1_AC0_Data0;
  SK5_ST6_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK5_ST6_FR1_AC0_Data0.actionParams_.changeStateIndex_ = 7;
  SkillFrameActionConditionData SK5_ST6_FR1_AC0_Cond0;
  SK5_ST6_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST6_FR1_Action0;
  SK5_ST6_FR1_Action0.conditionDatas_.push_back(SK5_ST6_FR1_AC0_Cond0);
  SK5_ST6_FR1_Action0.actionDatas_.push_back(SK5_ST6_FR1_AC0_Data0);
  SkillFrame SK5_ST6_Frame1;
  SK5_ST6_Frame1.startIndex_ = 107;
  SK5_ST6_Frame1.endIndex_ = 107;
  SK5_ST6_Frame1.actions_.push_back(SK5_ST6_FR1_Action0);
  SkillState SK5_State6;
  SK5_State6.animState_ = IORI_ANIMTYPE_1211ShikiYaOtome_6;
  SK5_State6.frames_.push_back(SK5_ST6_Frame0);
  SK5_State6.frames_.push_back(SK5_ST6_Frame1);

  SkillFrameActionData SK5_ST7_FR0_AC0_Data0;
  SK5_ST7_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_FadeInOut;
  SK5_ST7_FR0_AC0_Data0.actionParams_.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST7_FR0_AC0_Data0.actionParams_.fadeDuration_ = 50;
  SkillFrameActionConditionData SK5_ST7_FR0_AC0_Cond0;
  SK5_ST7_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST7_FR0_Action0;
  SK5_ST7_FR0_Action0.actionDatas_.push_back(SK5_ST7_FR0_AC0_Data0);
  SK5_ST7_FR0_Action0.conditionDatas_.push_back(SK5_ST7_FR0_AC0_Cond0);
  SkillFrame SK5_ST7_Frame0;
  SK5_ST7_Frame0.startIndex_ = 161;
  SK5_ST7_Frame0.endIndex_ = 161;
  SK5_ST7_Frame0.actions_.push_back(SK5_ST7_FR0_Action0);
  SkillFrameActionData SK5_ST7_FR1_AC0_Data0;
  SK5_ST7_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK5_ST7_FR1_AC0_Data0.actionParams_.changeStateIndex_ = 8;
  SkillFrameActionConditionData SK5_ST7_FR1_AC0_Cond0;
  SK5_ST7_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST7_FR1_Action0;
  SK5_ST7_FR1_Action0.conditionDatas_.push_back(SK5_ST7_FR1_AC0_Cond0);
  SK5_ST7_FR1_Action0.actionDatas_.push_back(SK5_ST7_FR1_AC0_Data0);
  SkillFrame SK5_ST7_Frame1;
  SK5_ST7_Frame1.startIndex_ = 163;
  SK5_ST7_Frame1.endIndex_ = 163;
  SK5_ST7_Frame1.actions_.push_back(SK5_ST7_FR1_Action0);
  SkillState SK5_State7;
  SK5_State7.animState_ = IORI_ANIMTYPE_1211ShikiYaOtome_7;
  SK5_State7.frames_.push_back(SK5_ST7_Frame0);
  SK5_State7.frames_.push_back(SK5_ST7_Frame1);
  SkillFrameActionData SK5_ST8_FR0_AC0_Data0;
  SK5_ST8_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_FadeInOut;
  SK5_ST8_FR0_AC0_Data0.actionParams_.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST8_FR0_AC0_Data0.actionParams_.fadeDuration_ = 50;
  SkillFrameActionConditionData SK5_ST8_FR0_AC0_Cond0;
  SK5_ST8_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST8_FR0_Action0;
  SK5_ST8_FR0_Action0.actionDatas_.push_back(SK5_ST8_FR0_AC0_Data0);
  SK5_ST8_FR0_Action0.conditionDatas_.push_back(SK5_ST8_FR0_AC0_Cond0);
  SkillFrame SK5_ST8_Frame0;
  SK5_ST8_Frame0.startIndex_ = 102;
  SK5_ST8_Frame0.endIndex_ = 102;
  SK5_ST8_Frame0.actions_.push_back(SK5_ST8_FR0_Action0);
  SkillFrameActionData SK5_ST8_FR1_AC0_Data0;
  SK5_ST8_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK5_ST8_FR1_AC0_Data0.actionParams_.changeStateIndex_ = 9;
  SkillFrameActionConditionData SK5_ST8_FR1_AC0_Cond0;
  SK5_ST8_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST8_FR1_Action0;
  SK5_ST8_FR1_Action0.conditionDatas_.push_back(SK5_ST8_FR1_AC0_Cond0);
  SK5_ST8_FR1_Action0.actionDatas_.push_back(SK5_ST8_FR1_AC0_Data0);
  SkillFrame SK5_ST8_Frame1;
  SK5_ST8_Frame1.startIndex_ = 107;
  SK5_ST8_Frame1.endIndex_ = 107;
  SK5_ST8_Frame1.actions_.push_back(SK5_ST8_FR1_Action0);
  SkillState SK5_State8;
  SK5_State8.animState_ = IORI_ANIMTYPE_1211ShikiYaOtome_8;
  SK5_State8.frames_.push_back(SK5_ST8_Frame0);
  SK5_State8.frames_.push_back(SK5_ST8_Frame1);
  SkillFrameActionData SK5_ST9_FR0_AC0_Data0;
  SK5_ST9_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_SetPostionOpponentPlayer;
  SK5_ST9_FR0_AC0_Data0.actionParams_.opponentForcedPosition_ = {50.0f, -40.0f};
  SkillFrameActionConditionData SK5_ST9_FR0_AC0_Cond0;
  SK5_ST9_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST9_FR0_Action0;
  SK5_ST9_FR0_Action0.actionDatas_.push_back(SK5_ST9_FR0_AC0_Data0);
  SK5_ST9_FR0_Action0.conditionDatas_.push_back(SK5_ST9_FR0_AC0_Cond0);
  SkillFrame SK5_ST9_Frame0;
  SK5_ST9_Frame0.startIndex_ = 348;
  SK5_ST9_Frame0.endIndex_ = 348;
  SK5_ST9_Frame0.actions_.push_back(SK5_ST9_FR0_Action0);
  SkillFrameActionConditionData SK5_ST9_FR1_AC0_Cond0;
  SK5_ST9_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK5_ST9_FR1_AC0_Data0;
  SK5_ST9_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_SoundPlay;
  SK5_ST9_FR1_AC0_Data0.actionParams_.soundType_ = SOUNDTYPE_IORI_1211ShikiYaOtome03;
  SkillFrameActionData SK5_ST9_FR1_AC0_Data1;
  SK5_ST9_FR1_AC0_Data1.actionType_ = SKILL_FRAME_ACTION_ChangeOpponentAnimState;
  SK5_ST9_FR1_AC0_Data1.actionParams_.opponentAnimState_ = PLAYER_ANIMTYPE_NeckGrabbed;
  SkillFrameAction SK5_ST9_FR1_Action0;
  SK5_ST9_FR1_Action0.conditionDatas_.push_back(SK5_ST9_FR1_AC0_Cond0);
  SK5_ST9_FR1_Action0.actionDatas_.push_back(SK5_ST9_FR1_AC0_Data0);
  SK5_ST9_FR1_Action0.actionDatas_.push_back(SK5_ST9_FR1_AC0_Data1);
  SkillFrame SK5_ST9_Frame1;
  SK5_ST9_Frame1.startIndex_ = 349;
  SK5_ST9_Frame1.endIndex_ = 349;
  SK5_ST9_Frame1.actions_.push_back(SK5_ST9_FR1_Action0);
  SkillFrameActionData SK5_ST9_FR2_AC0_Data0;
  SK5_ST9_FR2_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_FadeInOut;
  SK5_ST9_FR2_AC0_Data0.actionParams_.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST9_FR2_AC0_Data0.actionParams_.fadeDuration_ = 50;
  SkillFrameActionConditionData SK5_ST9_FR2_AC0_Cond0;
  SK5_ST9_FR2_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK5_ST9_FR2_AC0_Data1;
  SK5_ST9_FR2_AC0_Data1.actionType_ = SKILL_FRAME_ACTION_CameraShake;
  SK5_ST9_FR2_AC0_Data1.actionParams_.cameraShakeDuration_ = 400;
  SkillFrameActionConditionData SK5_ST9_FR2_AC0_Cond1;
  SK5_ST9_FR2_AC0_Cond1.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST9_FR2_Action0;
  SK5_ST9_FR2_Action0.conditionDatas_.push_back(SK5_ST9_FR2_AC0_Cond0);
  SK5_ST9_FR2_Action0.conditionDatas_.push_back(SK5_ST9_FR2_AC0_Cond1);
  SK5_ST9_FR2_Action0.actionDatas_.push_back(SK5_ST9_FR2_AC0_Data0);
  SK5_ST9_FR2_Action0.actionDatas_.push_back(SK5_ST9_FR2_AC0_Data1);
  SkillFrame SK5_ST9_Frame2;
  SK5_ST9_Frame2.startIndex_ = 351;
  SK5_ST9_Frame2.endIndex_ = 351;
  SK5_ST9_Frame2.actions_.push_back(SK5_ST9_FR2_Action0);
  SkillFrameActionData SK5_ST9_FR3_AC0_Data0;
  SK5_ST9_FR3_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ReleaseStunOpponentPlayer;
  SK5_ST9_FR3_AC0_Data0.actionParams_;
  SkillFrameActionConditionData SK5_ST9_FR3_AC0_Cond0;
  SK5_ST9_FR3_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST9_FR3_Action0;
  SK5_ST9_FR3_Action0.conditionDatas_.push_back(SK5_ST9_FR3_AC0_Cond0);
  SK5_ST9_FR3_Action0.actionDatas_.push_back(SK5_ST9_FR3_AC0_Data0);
  SkillFrame SK5_ST9_Frame3;
  SK5_ST9_Frame3.startIndex_ = 352;
  SK5_ST9_Frame3.endIndex_ = 352;
  SK5_ST9_Frame3.actions_.push_back(SK5_ST9_FR3_Action0);
  SkillState SK5_State9;
  SK5_State9.animState_ = IORI_ANIMTYPE_1211ShikiYaOtome_9;
  SK5_State9.frames_.push_back(SK5_ST9_Frame0);
  SK5_State9.frames_.push_back(SK5_ST9_Frame1);
  SK5_State9.frames_.push_back(SK5_ST9_Frame2);
  SK5_State9.frames_.push_back(SK5_ST9_Frame3);
  Skill Skill_5;
  Skill_5.skillTag_ = SKILL_5;
  Skill_5.castCondition_ = SKILL_CAST_COND_HasSkillPoint;
  Skill_5.castAction_ = SKILL_CAST_ACTION_ReduceSkillPoint;
  Skill_5.skillStates_.push_back(SK5_State0);
  Skill_5.skillStates_.push_back(SK5_State1);
  Skill_5.skillStates_.push_back(SK5_State2);
  Skill_5.skillStates_.push_back(SK5_State3);
  Skill_5.skillStates_.push_back(SK5_State4);
  Skill_5.skillStates_.push_back(SK5_State5);
  Skill_5.skillStates_.push_back(SK5_State6);
  Skill_5.skillStates_.push_back(SK5_State7);
  Skill_5.skillStates_.push_back(SK5_State8);
  Skill_5.skillStates_.push_back(SK5_State9);
  pSkillComponent_->RegistSkill(Skill_5);

  //SkillFrameActionData a;
  //a.actionType_ = SKILL_FRAME_ACTION_FadeOut;
  //a.actionParams_.fadeDuration_ = 50;
  //a.actionParams_.fadeImageType_ = IMGTYPE_BlackBoardImage;
  //SkillFrameActionConditionData b;
  //b.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  //b.conditionParams_;
  //SkillFrameAction SK5_ST0_FR0_Action0;
  //SK5_ST0_FR0_Action0.conditionDatas_.push_back(b);
  //SK5_ST0_FR0_Action0.actionDatas_.push_back(a);
  //SkillFrame SK5_ST0_Frame0;
  //SK5_ST0_Frame0.startIndex_ = 100;
  //SK5_ST0_Frame0.endIndex_ = 100;
  //SK5_ST0_Frame0.actions_.push_back(SK5_ST0_FR0_Action0);
  //SkillState SK5_State0;
  //SK5_State0.animState_ = IORI_ANIMTYPE_1211ShikiYaOtome_8;
  //SK5_State0.frames_.push_back(SK5_ST0_Frame0);
  //Skill Skill_5;
  //Skill_5.skillTag_ = SKILL_5;
  //Skill_5.skillStates_.push_back(SK5_State0);
  //skillTest_->RegistSkill(Skill_5);
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
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_Left}) &&
        true == pInputController_->IsEqualInputBitSet(KEY_STATE_Down, {KEY_A, KEY_B})) {
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
      pSkillComponent_->ExecuteSkill(SKILL_0);
      return;
    }

    // RIGHT | PRESS - B | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_Right}) &&
        true == pInputController_->IsEqualInputBitSet(KEY_STATE_Down, {KEY_B})) {
      pSkillComponent_->ExecuteSkill(SKILL_4);
      return;
    }

    // A | DOWN
    if (true == pInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_A})) {
      if (GetCloseDistance() > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
        UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_CloseRange);
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_LongRange);
      }
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
    return;
  }
}
