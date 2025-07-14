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

#define CLOSEDISTANCE 260.0f
#define ANIMINTERVAL 40

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
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {23.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {18.0f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {23.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {18.0f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {23.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {20.0f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {23.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {20.0f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {20.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {20.0f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {20.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {20.0f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {20.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {20.0f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {20.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {20.0f, 0.0f}, 80.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_108ShikiYamiBarai, ATTYPE_NormalAttack, ELMTTYPE_BlueFlame, EFTYPE_Hit_2, true, 5.0f, {20.0f, 60.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {5.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {20.0f, 40.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Shinigami, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 15.0f, {20.0f, 80.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_HyakushikiOniyaki, ATTYPE_NormalAttack, ELMTTYPE_BlueFlame, EFTYPE_Hit_2, true, 20.0f, {40.0f, 80.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {10.0f, 00.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {10.0f, 00.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_3, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {20.0f, 80.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_1, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_2, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_3, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_4, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_5, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_6, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_7, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_8, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 40.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_9, ATTYPE_StrongAttack, ELMTTYPE_BlueFlame, EFTYPE_Iori_Explosion, false, 10.0f, {45.0f, 50.0f}, 140.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_1, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {10.0f, 20.0f}, 100.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_2, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {5.0f, 80.0f}, 100.0f);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_3, ATTYPE_StrongAttack, ELMTTYPE_BlueFlame, EFTYPE_Hit_2, false, 10.0f, {10.0f, 130.0f}, 140.0f);

  // SKILL
  pSkillComponent_->RegistSkill(IORI_SKILL_GaishikiMutan, &Iori::GaishikiMutan, this);
  pSkillComponent_->RegistSkill(IORI_SKILL_108ShikiYamiBarai, &Iori::ShikiYamiBarai108, this);
  pSkillComponent_->RegistSkill(IORI_SKILL_HyakushikiOniyaki, &Iori::HyakushikiOniyaki, this);
  pSkillComponent_->RegistSkill(IORI_SKILL_127ShikiAoiHana, &Iori::ShikiAoiHana127, this);
  pSkillComponent_->RegistSkill(IORI_SKILL_1211ShikiYaOtome, &Iori::ShikiYaOtome1211, this);
  pSkillComponent_->RegistSkill(IORI_SKILL_Ura306shikiShika, &Iori::Ura306shikiShika, this);

  // COMMAND
  pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_A}, std::bind(&Iori::Command_1, this));
  pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_B}, std::bind(&Iori::Command_1, this));
  pCommandComponent_->RegistCommand({CK_Left, CK_Left}, std::bind(&Iori::Command_2, this));
  pCommandComponent_->RegistCommand({CK_Right, CK_Right}, std::bind(&Iori::Command_3, this));
  pCommandComponent_->RegistCommand({CK_Right, CK_Down, CK_Right, CK_A}, std::bind(&Iori::Command_4, this));
  pCommandComponent_->RegistCommand({CK_Right, CK_Down, CK_Right, CK_C}, std::bind(&Iori::Command_4, this));
  pCommandComponent_->RegistCommand({CK_Down, CK_Left, CK_A}, std::bind(&Iori::Command_5, this));
  pCommandComponent_->RegistCommand({CK_Down, CK_Left, CK_C}, std::bind(&Iori::Command_5, this));
  pCommandComponent_->RegistCommand({CK_Down, CK_Right, CK_Down, CK_Left, CK_A}, std::bind(&Iori::Command_6, this));
  pCommandComponent_->RegistCommand({CK_Down, CK_Right, CK_Down, CK_Left, CK_C}, std::bind(&Iori::Command_6, this));
  pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_Left, CK_Down, CK_Right, CK_A}, std::bind(&Iori::Command_7, this));
  pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_Left, CK_Down, CK_Right, CK_C}, std::bind(&Iori::Command_7, this));

  // PROJECTILE
  AttackInfo* pAttackInfo;
  if (false == pAttackTable_->SearchAttackInfo(IORI_ANIMTYPE_108ShikiYamiBarai, &pAttackInfo)) {
    return;
  }
  pProjectileComponent_->RegistProjectileInfo(IORI_PROJECTILE_YamiBarai, pAttackInfo, {180.0f, 50.0f}, true);
  if (false == pAttackTable_->SearchAttackInfo(IORI_ANIMTYPE_HyakushikiOniyaki, &pAttackInfo)) {
    return;
  }
  pProjectileComponent_->RegistProjectileInfo(IORI_PROJECTILE_HyakushikiOniyaki_Low, pAttackInfo, {50.0f, -30.0f}, false, 0);
  if (false == pAttackTable_->SearchAttackInfo(IORI_ANIMTYPE_HyakushikiOniyaki, &pAttackInfo)) {
    return;
  }
  pProjectileComponent_->RegistProjectileInfo(IORI_PROJECTILE_HyakushikiOniyaki_High, pAttackInfo, {-80.0f, -200.0f}, false, 1);
  if (false == pAttackTable_->SearchAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_3, &pAttackInfo)) {
    return;
  }
  pProjectileComponent_->RegistProjectileInfo(IORI_PROJECTILE_Ura306Shiki, pAttackInfo, {400.0f, -300.0f}, false, 0);
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
      if (CLOSEDISTANCE > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
        UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_CloseRange);
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_LongRange);
      }
      return;
    }

    // B | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000100"))) {
      if (CLOSEDISTANCE > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
        UpdateAnimState(PLAYER_ANIMTYPE_LightKick_CloseRange);
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_LightKick_LongRange);
      }

      return;
    }

    // C | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000010"))) {
      if (CLOSEDISTANCE > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
        UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_CloseRange);
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_LongRange);
      }

      return;
    }

    // D | DOWN
    if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000001"))) {
      if (CLOSEDISTANCE > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
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

void Iori::Command_1() {
  UpdateAnimState(IORI_ANIMTYPE_108ShikiYamiBarai);
  pSkillComponent_->ActivateSkill(IORI_SKILL_108ShikiYamiBarai);
}

void Iori::Command_2() {
  UpdateAnimState(PLAYER_ANIMTYPE_BackStep);
  pMovementComponent_->BackStep((FacingRight()));
}

void Iori::Command_3() {
  UpdateAnimState(PLAYER_ANIMTYPE_Run);
}

void Iori::Command_4() {
  UpdateAnimState(IORI_ANIMTYPE_HyakushikiOniyaki);
  pSkillComponent_->ActivateSkill(IORI_SKILL_HyakushikiOniyaki);
}

void Iori::Command_5() {
  UpdateAnimState(IORI_ANIMTYPE_127ShikiAoiHana_1);
  pSkillComponent_->ActivateSkill(IORI_SKILL_127ShikiAoiHana);
}

void Iori::Command_6() {
  if (nullptr == pMPComponent_) {
    return;
  }
  if (0 >= pMPComponent_->SkillPoint()) {
    return;
  }

  Level* pLevel = GetLevel();
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

  UpdateAnimState(PLAYER_ANIMTYPE_UltimateCasting);
  pSkillComponent_->ActivateSkill(IORI_SKILL_1211ShikiYaOtome);
  pMPComponent_->ReduceSkillPoint();
  EffectManager::Instance()->SpawnEffect(pKOFLevel, EFTYPE_Casting_1, GetPosition() + Vector{0.0f, -250.0f});
  EffectManager::Instance()->SpawnEffect(pKOFLevel, EFTYPE_Casting_2, GetPosition() + Vector{0.0f, -250.0f});
  pKOFLevel->FreezeActors({pOpponentPlayer_}, true);
  pBackGroundMask->FadeOut(IMGTYPE_BlackBoardImage, 50.0f);
}

void Iori::Command_7() {
  if (nullptr == pMPComponent_) {
    return;
  }
  if (0 >= pMPComponent_->SkillPoint()) {
    return;
  }

  SkillInfo* pCurSkillInfo = pSkillComponent_->GetCurrentActiveSkillInfo();
  if (nullptr == pCurSkillInfo) {
    return;
  }

  if (IORI_SKILL_1211ShikiYaOtome == pCurSkillInfo->skillTag_) {
    pSkillComponent_->SetMiscTemp(true);
  }
}

void Iori::GaishikiMutan() {
  if (true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();

  if (IORI_ANIMTYPE_GaishikiMutan_1 == pStateComponent_->GetCurAnimState()) {
    if (100 <= curImageIndex && 104 >= curImageIndex) {
      if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00001000")) ||
          true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000010"))) {
        pSkillComponent_->SetMiscTemp(true);
      }
    }

    if (true == pAttackBox_->HasHit() && 105 == curImageIndex && true == pSkillComponent_->GetMiscTemp()) {
      UpdateAnimState(IORI_ANIMTYPE_GaishikiMutan_2);
    }
  }
}

void Iori::ShikiYamiBarai108() {
  if (nullptr == pRender_) {
    return;
  }

  if (nullptr != pRender_ && true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();

  if (prevImageIndex_ == curImageIndex) {
    return;
  }

  if (225 == curImageIndex) {
    Level* curLevel = GetLevel();
    Vector curPosition = GetPosition();
    if (FacingRight()) {
      EffectManager::Instance()->SpawnEffect(curLevel, (EFTYPE_Iori_Casting_YamiBarai | EFMOD_NONE), {curPosition.X - 40.0f, curPosition.Y - 70.0f});
    } else {
      EffectManager::Instance()->SpawnEffect(curLevel, (EFTYPE_Iori_Casting_YamiBarai | EFMOD_FLIPPED), {curPosition.X + 40.0f, curPosition.Y - 70.0f});
    }
  }

  if (226 == curImageIndex) {
    pProjectileComponent_->FireProjectile(IORI_PROJECTILE_YamiBarai);
  }
}

void Iori::HyakushikiOniyaki() {
  if (nullptr == pRender_) {
    return;
  }

  if (true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();

  if (prevImageIndex_ == curImageIndex) {
    return;
  }

  if (276 == curImageIndex) {
    pMovementComponent_->Dash(FacingRight(), 150.0f, 150.0f);
  }

  if (281 == curImageIndex) {
    pMovementComponent_->Jump(FacingRight(), {0.3f, 60.0f});
    pProjectileComponent_->FireProjectile(IORI_PROJECTILE_HyakushikiOniyaki_Low);
  }

  if (284 == curImageIndex) {
    pProjectileComponent_->FireProjectile(IORI_PROJECTILE_HyakushikiOniyaki_High);
  }
}

void Iori::ShikiAoiHana127() {
  if (nullptr == pRender_) {
    return;
  }

  if (true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();
  if (prevImageIndex_ == curImageIndex) {
    return;
  }

  if (curImageIndex == 257) {
    pMovementComponent_->Dash(FacingRight(), 150.0f, 80.0f);
  }

  if (curImageIndex == 262) {
    pMovementComponent_->Dash(FacingRight(), 150.0f, 80.0f);
  }

  if (curImageIndex == 269) {
    pMovementComponent_->Jump(FacingRight(), {0.6f, 60.0f});
  }

  if (IORI_ANIMTYPE_127ShikiAoiHana_1 == pStateComponent_->GetCurAnimState()) {
    if (257 <= curImageIndex && 260 >= curImageIndex) {
      if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00001000")) ||
          true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000010"))) {
        pSkillComponent_->SetMiscTemp(true);
      }

      if (pAttackBox_->HasHit() && pSkillComponent_->GetMiscTemp() == true) {
        UpdateAnimState(IORI_ANIMTYPE_127ShikiAoiHana_2);
        pSkillComponent_->SetMiscTemp(false);
      }
    }
  }

  if (IORI_ANIMTYPE_127ShikiAoiHana_2 == pStateComponent_->GetCurAnimState()) {
    if (IORI_ANIMTYPE_127ShikiAoiHana_2 == pStateComponent_->GetCurAnimState() && 264 <= curImageIndex && 267 >= curImageIndex) {
      if (true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00001000")) ||
          true == IsContainInputBitSet(inputDownBitSet_, std::bitset<8>("00000010"))) {
        pSkillComponent_->SetMiscTemp(true);
      }

      if (pAttackBox_->HasHit() && true == pSkillComponent_->GetMiscTemp()) {
        UpdateAnimState(IORI_ANIMTYPE_127ShikiAoiHana_3);
      }
    }
  }
}

void Iori::ShikiYaOtome1211() {
  if (nullptr == pRender_) {
    return;
  }
  if (true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }

  Level* pLevel = GetLevel();
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

  unsigned int curImageIndex = pRender_->GetImageIndex();
  if (prevImageIndex_ == curImageIndex) {
    return;
  }

  switch (pStateComponent_->GetCurAnimState()) {
    case PLAYER_ANIMTYPE_UltimateCasting: {
      if (347 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_1);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_1: {
      if (70 == curImageIndex) {
        pKOFLevel->DefreezeActors();
        pBackGroundMask->FadeIn(50);
        break;
      }

      if (72 == curImageIndex) {
        pMovementComponent_->Dash(FacingRight(), 250.0f, 1000.0f);
        break;
      }

      if (pAttackBox_->HasHit()) {
        pOpponentPlayer_->SetControlLocked(true);
        pMovementComponent_->Dash(FacingRight(), 250.0f, 1000.0f);
        if (CLOSEDISTANCE - 100.0f > std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X)) {
          UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_2);
          pMovementComponent_->StopDash();
        }
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_2: {
      if (pOpponentPlayer_->GetPosition().X - GetPosition().X <= 300.0f * FacingRightFlag()) {
        pMovementComponent_->StopDash();
      }

      if (120 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }

      if (122 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_3);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_3: {
      if (90 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }
      if (92 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_4);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_4: {
      if (135 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_5);
        break;
      }

      if (138 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_5: {
      if (227 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }

      if (229 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_6);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_6: {
      if (102 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }
      if (106 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_7);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_7: {
      if (161 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }
      if (163 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_8);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_8: {
      if (102 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }
      if (106 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_9);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_9: {
      if (348 == curImageIndex) {
        pOpponentPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_NeckGrab);
        break;
      }

      if (349 == curImageIndex) {
        const Vector& ioriPosition = GetPosition();
        pOpponentPlayer_->SetPosition(ioriPosition + Vector{100.0f * FacingRightFlag(), -50.0f});
        soundChannel_ = SoundManager::Instance()->SoundPlay(SOUNDTYPE_IORI_1211ShikiYaOtome03);
        break;
      }
      if (351 == curImageIndex) {
        pCommandComponent_->ExcuteTask();
        if (true == pSkillComponent_->GetMiscTemp()) {
          ActiveUra306shikiShika();
        } else {
          pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
          pKOFLevel->GetCameraTarget()->OnCameraShake(300);
        }
        break;
      }
      if (352 == curImageIndex) {
        pOpponentPlayer_->SetControlLocked(false);
        break;
      }
      break;
    }
    default:
      break;
  }
}

void Iori::ActiveUra306shikiShika() {
  if (nullptr == pMPComponent_) {
    return;
  }
  if (0 >= pMPComponent_->SkillPoint()) {
    return;
  }

  Level* pLevel = GetLevel();
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

  UpdateAnimState(IORI_ANIMTYPE_Ura306shikiShika_1, ANIMMOD_NONE, true);
  pSkillComponent_->ActivateSkill(IORI_SKILL_Ura306shikiShika);
  pMPComponent_->ReduceSkillPoint();
}

void Iori::Ura306shikiShika() {
  if (nullptr == pRender_) {
    return;
  }
  if (true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }

  Level* pLevel = GetLevel();
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

  unsigned int curImageIndex = pRender_->GetImageIndex();
  if (prevImageIndex_ == curImageIndex) {
    return;
  }

  switch (pStateComponent_->GetCurAnimState()) {
    case IORI_ANIMTYPE_Ura306shikiShika_1: {
      if (355 == curImageIndex) {
        EffectManager::Instance()->SpawnEffect(pKOFLevel, EFTYPE_Casting_1, GetPosition() + Vector{0.0f, -250.0f});
        EffectManager::Instance()->SpawnEffect(pKOFLevel, EFTYPE_Casting_2, GetPosition() + Vector{0.0f, -250.0f});
        pKOFLevel->FreezeActors({this, pOpponentPlayer_}, false, 500);
        pBackGroundMask->FadeOut(IMGTYPE_BlackBoardImage, 50.0f);
      }
      if (356 == curImageIndex) {
        
        pKOFLevel->FreezeActors({pOpponentPlayer_}, true);
      }
      if (360 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_Ura306shikiShika_2);
        pBackGroundMask->FadeIn(50.0f);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_Ura306shikiShika_2: {
        if (363 == curImageIndex) {
        pAttackBox_->ResetHit();
        break;
      }
        if (364 == curImageIndex) {
        pAttackBox_->ResetHit();
          break;
        }
        if (365 == curImageIndex) {
          pAttackBox_->ResetHit();
          break;
        }
        if (366 == curImageIndex) {
          pAttackBox_->ResetHit();
          pKOFLevel->DefreezeActors();
          //pOpponentPlayer_->SetControlLocked(false);
          break;
        }

      if (370 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_Ura306shikiShika_3);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_Ura306shikiShika_3: {
      if (381 == curImageIndex) {
        pProjectileComponent_->FireProjectile(IORI_PROJECTILE_Ura306Shiki);
        break;
      }
      if (386 == curImageIndex) {
        pOpponentPlayer_->SetControlLocked(false);
      }

      break;
    }                            
    default:
      break;
  }
}