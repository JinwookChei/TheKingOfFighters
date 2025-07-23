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

#include "CommandHandler.h"
#include "IoriCommandHandler.h"
#include "SkillHandler.h"
#include "IoriSkillHandler.h"

#define ANIMINTERVAL 35

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
  CallCreateAnimation(PLAYER_ANIMTYPE_StartPos, IMGTYPE_IoriImage, 0, 15, ANIMINTERVAL, true, 7);
  CallCreateAnimation(PLAYER_ANIMTYPE_Idle, IMGTYPE_IoriImage, 7, 15, ANIMINTERVAL, true, 7);
  CallCreateAnimation(PLAYER_ANIMTYPE_SeatDown, IMGTYPE_IoriImage, 16, 23, ANIMINTERVAL, true, 18);
  CallCreateAnimation(PLAYER_ANIMTYPE_SeatUp, IMGTYPE_IoriImage, 24, 25, ANIMINTERVAL, false, 24);
  CallCreateAnimation(PLAYER_ANIMTYPE_FrontWalk, IMGTYPE_IoriImage, 27, 34, ANIMINTERVAL, true, 27);
  CallCreateAnimation(PLAYER_ANIMTYPE_BackWalk, IMGTYPE_IoriImage, 35, 44, ANIMINTERVAL, true, 35);
  CallCreateAnimation(PLAYER_ANIMTYPE_BackStep, IMGTYPE_IoriImage, 45, 48, ANIMINTERVAL, false, 45);
  CallCreateAnimation(PLAYER_ANIMTYPE_Run, IMGTYPE_IoriImage, 49, 57, ANIMINTERVAL, true, 51);
  CallCreateAnimation(PLAYER_ANIMTYPE_RunEnd, IMGTYPE_IoriImage, 58, 60, ANIMINTERVAL, false, 59);
  CallCreateAnimation(PLAYER_ANIMTYPE_Jump, IMGTYPE_IoriImage, 61, 69, ANIMINTERVAL, false, 61);
  // CallCreateAnimation(PLAYER_ANIMTYPE_JumpStart, IMGTYPE_IoriImage, 61, 69, ANIMINTERVAL, false, 61);
  // CallCreateAnimation(PLAYER_ANIMTYPE_JumpIdle, IMGTYPE_IoriImage, 61, 69, ANIMINTERVAL, false, 61);
  // CallCreateAnimation(PLAYER_ANIMTYPE_Jump, IMGTYPE_IoriImage, 61, 69, ANIMINTERVAL, false, 61);
  CallCreateAnimation(PLAYER_ANIMTYPE_Dash, IMGTYPE_IoriImage, 70, 77, ANIMINTERVAL, false, 70);
  CallCreateAnimation(PLAYER_ANIMTYPE_RollingBack, IMGTYPE_IoriImage, 78, 87, ANIMINTERVAL, false, 78);
  CallCreateAnimation(PLAYER_ANIMTYPE_Guard, IMGTYPE_IoriImage, 541, 541, ANIMINTERVAL, false, 541);
  CallCreateAnimation(PLAYER_ANIMTYPE_GuardEnd, IMGTYPE_IoriImage, 542, 543, ANIMINTERVAL, false, 542);
  CallCreateAnimation(PLAYER_ANIMTYPE_Guard_Seat, IMGTYPE_IoriImage, 548, 548, ANIMINTERVAL, false, 548);
  CallCreateAnimation(PLAYER_ANIMTYPE_GuardEnd_Seat, IMGTYPE_IoriImage, 549, 549, ANIMINTERVAL, false, 549);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyKick_CloseRange, IMGTYPE_IoriImage, 136, 144, ANIMINTERVAL, false, 136);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightKick_CloseRange, IMGTYPE_IoriImage, 123, 127, ANIMINTERVAL, false, 123);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, IMGTYPE_IoriImage, 128, 135, ANIMINTERVAL, false, 128);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightPunch_CloseRange, IMGTYPE_IoriImage, 118, 122, ANIMINTERVAL, false, 118);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyKick_LongRange, IMGTYPE_IoriImage, 108, 117, ANIMINTERVAL, false, 108);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightKick_LongRange, IMGTYPE_IoriImage, 94, 98, ANIMINTERVAL, false, 94);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyPunch_LongRange, IMGTYPE_IoriImage, 99, 107, ANIMINTERVAL, false, 99);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightPunch_LongRange, IMGTYPE_IoriImage, 88, 93, ANIMINTERVAL, false, 88);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyKick_Seat, IMGTYPE_IoriImage, 181, 191, ANIMINTERVAL, false, 181);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightKick_Seat, IMGTYPE_IoriImage, 165, 171, ANIMINTERVAL, false, 165);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyPunch_Seat, IMGTYPE_IoriImage, 172, 180, ANIMINTERVAL, false, 172);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightPunch_Seat, IMGTYPE_IoriImage, 192, 197, ANIMINTERVAL, false, 192);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyKick_Jump, IMGTYPE_IoriImage, 213, 218, ANIMINTERVAL, false, 213);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightKick_Jump, IMGTYPE_IoriImage, 204, 205, ANIMINTERVAL, false, 204);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyPunch_Jump, IMGTYPE_IoriImage, 206, 212, ANIMINTERVAL, false, 206);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightPunch_Jump, IMGTYPE_IoriImage, 198, 203, ANIMINTERVAL, false, 198);
  CallCreateAnimation(PLAYER_ANIMTYPE_HitHigh, IMGTYPE_IoriImage, 557, 562, ANIMINTERVAL, false, 557);
  CallCreateAnimation(PLAYER_ANIMTYPE_HitLow, IMGTYPE_IoriImage, 563, 567, ANIMINTERVAL, false, 563);
  CallCreateAnimation(PLAYER_ANIMTYPE_HitStrong, IMGTYPE_IoriImage, 594, 607, ANIMINTERVAL, false, 594);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_Seat, IMGTYPE_IoriImage, 552, 556, ANIMINTERVAL, false, 552);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_Jump, IMGTYPE_IoriImage, {557 /*, 558*/, 80, 81, 82, 83, 84, 85}, {80, ANIMINTERVAL, ANIMINTERVAL, ANIMINTERVAL, ANIMINTERVAL, ANIMINTERVAL, ANIMINTERVAL}, false, 557);
  CallCreateAnimation(PLAYER_ANIMTYPE_NeckGrab, IMGTYPE_IoriImage, 572, 575, 200, false, 572);
  CallCreateAnimation(IORI_ANIMTYPE_108ShikiYamiBarai, IMGTYPE_IoriImage, 223, 230, ANIMINTERVAL, false, 223);
  CallCreateAnimation(IORI_ANIMTYPE_GaishikiMutan_1, IMGTYPE_IoriImage, 99, 107, ANIMINTERVAL, false, 99);
  CallCreateAnimation(IORI_ANIMTYPE_GaishikiMutan_2, IMGTYPE_IoriImage, 160, 164, ANIMINTERVAL, false, 160);
  CallCreateAnimation(IORI_ANIMTYPE_Shinigami, IMGTYPE_IoriImage, 145, 156, ANIMINTERVAL, false, 145);
  CallCreateAnimation(IORI_ANIMTYPE_HyakushikiOniyaki, IMGTYPE_IoriImage, 276, 291, ANIMINTERVAL, false, 276);
  CallCreateAnimation(IORI_ANIMTYPE_127ShikiAoiHana_1, IMGTYPE_IoriImage, 255, 261, ANIMINTERVAL, false, 255);
  CallCreateAnimation(IORI_ANIMTYPE_127ShikiAoiHana_2, IMGTYPE_IoriImage, 262, 268, ANIMINTERVAL, false, 262);
  CallCreateAnimation(IORI_ANIMTYPE_127ShikiAoiHana_3, IMGTYPE_IoriImage, 269, 275, ANIMINTERVAL, false, 269);
  CallCreateAnimation(PLAYER_ANIMTYPE_UltimateCasting, IMGTYPE_IoriImage, 344, 347, 120, false, 344);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_1, IMGTYPE_IoriImage, 70, 77, 20, false, 70);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_2, IMGTYPE_IoriImage, 118, 122, 20, false, 118);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_3, IMGTYPE_IoriImage, 88, 92, 20, false, 88);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_4, IMGTYPE_IoriImage, 128, 135, 20, false, 128);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_5, IMGTYPE_IoriImage, 223, 229, 20, false, 223);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_6, IMGTYPE_IoriImage, 99, 106, 20, false, 99);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_7, IMGTYPE_IoriImage, 159, 163, 20, false, 159);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_8, IMGTYPE_IoriImage, 99, 107, 20, false, 99);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_9, IMGTYPE_IoriImage, 347, 352, 200, false, 347);
  CallCreateAnimation(IORI_ANIMTYPE_Ura306shikiShika_1, IMGTYPE_IoriImage, 353, 360, 20, false, 353);
  CallCreateAnimation(IORI_ANIMTYPE_Ura306shikiShika_2, IMGTYPE_IoriImage, 361, 370, 20, false, 161);
  CallCreateAnimation(IORI_ANIMTYPE_Ura306shikiShika_3, IMGTYPE_IoriImage, 371, 386, 20, false, 371);

  UpdateAnimState(PLAYER_ANIMTYPE_StartPos);

  // SOUND
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Jump, SOUNDTYPE_COMMON_Jump01);
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
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HitHigh, SOUNDTYPE_None);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HitLow, SOUNDTYPE_None);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_HitStrong, SOUNDTYPE_None);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Hit_Seat, SOUNDTYPE_None);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Hit_Jump, SOUNDTYPE_None);
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
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Idle, {PS_Idle}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatDown, {PS_Seat}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatUp, {PS_None}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_FrontWalk, {PS_Move}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackWalk, {PS_Move}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackStep, {PS_Move}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Run, {PS_Run}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_RunEnd, {PS_None}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Jump, {PS_Jump}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Dash, {PS_Rolling}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_RollingBack, {PS_Rolling}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Guard, {PS_Guard}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_GuardEnd, {PS_None}, false);
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
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HitHigh, {PS_Hit}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HitLow, {PS_Hit}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HitStrong, {PS_Hit}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_Seat, {PS_Hit, PS_Seat}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Hit_Jump, {PS_Hit}, false);
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
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, -5.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Shinigami, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 15.0f, {2.0f, -8.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_3, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_1, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_2, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_3, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_4, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_5, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_6, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_7, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_8, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_9, ATTYPE_StrongAttack, ELMTTYPE_BlueFlame, EFTYPE_Iori_Explosion, false, 10.0f, {1.5f, -8.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_1, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, 0.0f}, 100.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_2, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, true, 5.0f, {0.5f, -10.0f}, 100.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_3, ATTYPE_StrongAttack, ELMTTYPE_BlueFlame, EFTYPE_Hit_2, false, 10.0f, {0.5f, -10.0f}, 140.0f);


  // COMMAND
  pCommandHandler_ = CreateComponent<IoriCommandHandler>();
  if (nullptr == pCommandHandler_) {
    __debugbreak();
    return;
  }
  if (false == pCommandHandler_->Initialize(
      this, 
      pCommandComponent_, 
      pMovementComponent_, 
      pSkillComponent_, 
      pMPComponent_)) {
    __debugbreak();
    return;
  }

  if (false == pCommandHandler_->RegistCommands()) {
    __debugbreak();
    return;
  }

  // SKILL
  pSkillHandler_ = CreateComponent<IoriSkillHandler>();
  if (nullptr == pSkillHandler_) {
    __debugbreak();
    return;
  }
  if (false == pSkillHandler_->Initialize(
      this,
      pSkillComponent_,
      pRender_, 
      pMovementComponent_, 
      pStateComponent_, 
      pAttackBox_, 
      pCommandComponent_,
      pProjectileComponent_, 
      pMPComponent_)) {
    __debugbreak();
    return;
  }
  if (false == pSkillHandler_->RegistSkills()) {
    __debugbreak();
    return;
  }
}

void Iori::CompareInputBitset() {
  if (pStateComponent_->EqualPlayerState({PS_Jump})) {
    // A | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00001000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_Jump);
      return;
    }
    // B | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000100"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightKick_Jump);
      return;
    }
    // C | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000010"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_Jump);
      return;
    }
    // D | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000001"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_Jump);
      return;
    }

    if (true == pRender_->IsAnimationEnd()) {
      UpdateAnimState(PLAYER_ANIMTYPE_Idle);
      return;
    }
    return;
  }

  if (pStateComponent_->ContainPlayerState({PS_Seat})) {
    // LEFT | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("10000000"))) {
      if (pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
        UpdateAnimState(PLAYER_ANIMTYPE_Guard_Seat);
        return;
      }
    }
    if (pStateComponent_->ContainPlayerState({PS_Guard})) {
      if (false == pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
        UpdateAnimState(PLAYER_ANIMTYPE_GuardEnd_Seat);
        return;
      }
    }
    // A | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00001000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_Seat);
      return;
    }
    // B | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000100"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightKick_Seat);
      return;
    }
    // C | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000010"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_Seat);
      return;
    }
    // D | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000001"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_Seat);
      return;
    }
    // DOWN | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01000000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_SeatDown, ANIMMOD_NONE, false, 18, 50);
      return;
    }

    UpdateAnimState(PLAYER_ANIMTYPE_SeatUp);
    return;
  }

  // IDLE Guard
  if (pStateComponent_->EqualPlayerState({PS_Guard})) {
    if (false == pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
      UpdateAnimState(PLAYER_ANIMTYPE_GuardEnd);
      return;
    }
  }

  if (pStateComponent_->ContainPlayerState({PS_Run})) {
    if (false == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00100000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_RunEnd);
      return;
    }
  }

  // IDLE
  if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00000000")) &&
      true == IsEqualInputBitSet(inputDownBitSet_, std::bitset<8>("00000000")) &&
      true == IsEqualInputBitSet(inputUpBitSet_, std::bitset<8>("00000000"))) {
    UpdateAnimState(PLAYER_ANIMTYPE_Idle);
    return;
  } else {
    // LEFT | PRESS Contain
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("10000000"))) {
      if (pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
        UpdateAnimState(PLAYER_ANIMTYPE_Guard);
        return;
      }
    }

    // RIGHT | PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00100000"))) {
      if (true == pStateComponent_->ContainPlayerState({PS_Run})) {
        pMovementComponent_->Run(FacingRight());
        return;
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_FrontWalk);
        pMovementComponent_->Move(FacingRight());
        return;
      }
    }

    // LEFT | PRESS Equal
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("10000000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_BackWalk);
      pMovementComponent_->MoveBack(FacingRight());
      return;
    }

    // DOWN | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01000000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_SeatDown);
      return;
    }

    // RIGHT UP | PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00110000"))) {
      if (true == pStateComponent_->ContainPlayerState({PS_Run})) {
        UpdateAnimState(PLAYER_ANIMTYPE_Jump);
        pMovementComponent_->JumpForward(FacingRight(), true);
        pGhostEffect_->On();
        return;
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_Jump);
        pMovementComponent_->JumpForward(FacingRight(), false);
        return;
      }
    }

    // LEFT UP | PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("10010000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_Jump);
      pMovementComponent_->JumpForward(!FacingRight(), false);
      return;
    }

    // UP | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00010000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_Jump);
      pMovementComponent_->Jump();
      return;
    }

    // A B LEFT | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("10000000")) &&
        true == IsEqualInputBitSet(inputDownBitSet_, std::bitset<8>("00001100"))) {
      UpdateAnimState((PLAYER_ANIMTYPE_RollingBack));
      pMovementComponent_->Dash(!FacingRight(), 300.0f, 400.0f);
      pGhostEffect_->On();
      return;
    }

    // A B | PRESS
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00001100"))) {
      UpdateAnimState((PLAYER_ANIMTYPE_Dash));
      pMovementComponent_->Dash(FacingRight(), 300.0f, 500.0f);
      pGhostEffect_->On();
      return;
    }

    // RIGHT | PRESS - A | DOWN
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00100000")) &&
        (true == IsEqualInputBitSet(inputDownBitSet_, std::bitset<8>("00001000")) ||
         true == IsEqualInputBitSet(inputDownBitSet_, std::bitset<8>("00000010")))) {
      UpdateAnimState(IORI_ANIMTYPE_GaishikiMutan_1);
      pSkillComponent_->ActivateSkill(IORI_SKILL_GaishikiMutan);
      return;
    }

    // RIGHT | PRESS - B | DOWN
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00100000")) && true == IsEqualInputBitSet(inputDownBitSet_, std::bitset<8>("00000100"))) {
      UpdateAnimState(IORI_ANIMTYPE_Shinigami);
      pSkillComponent_->ActivateSkill(IORI_SKILL_Shinigami);
      return;
    }

    // A | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00001000"))) {
      if (GetCloseDistance() > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
        UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_CloseRange);
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_LongRange);
      }
      return;
    }

    // B | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000100"))) {
      if (GetCloseDistance() > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
        UpdateAnimState(PLAYER_ANIMTYPE_LightKick_CloseRange);
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_LightKick_LongRange);
      }

      return;
    }

    // C | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000010"))) {
      if (GetCloseDistance() > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
        UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_CloseRange);
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_LongRange);
      }

      return;
    }

    // D | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000001"))) {
      if (GetCloseDistance() > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
        UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_CloseRange);
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_LongRange);
      }

      return;
    }

    UpdateAnimState(PLAYER_ANIMTYPE_Idle);
    return;
  }
}
