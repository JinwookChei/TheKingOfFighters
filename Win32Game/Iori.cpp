#include "stdafx.h"
#include "KOFPlayer.h"
#include "KOFLevel.h"
#include "BackGroundMask.h"
#include "MovementComponent.h"
#include "AttackTable.h"
#include "SkillComponent.h"
#include "CommandComponent.h"
#include "ProjectileComponent.h"
#include "HealthComponent.h"
#include "StateComponent.h"
#include "GhostEffect.h"
#include "CollisionBox.h"
#include "Iori.h"

Iori::Iori() {
  playerKeySet_ = {'A', 'S', 'Z', 'X', VK_UP, VK_RIGHT, VK_DOWN, VK_LEFT};  // D C B A UP RIGHT DONW LEFT
}

Iori::~Iori() {
}

void Iori::BeginPlay() {
}

void Iori::Initialize(const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) {
  KOFPlayer::Initialize(position, useCameraPosition, opponentPlayer);

  // CHARACTER SETTING
  IImage* pImage = ImgManager::GetIntance()->GetImg(IMGTYPE_IoriImage);
  if (nullptr == pImage) {
    return;
  }
  SetCharacterScale(pImage->GetScale(7) * pRender_->GetLocalScale());

  // RENDERER
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Idle | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 7, 15, 50, true, 7);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_SeatDown | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 16, 23, 50, true, 18);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_SeatUp | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 24, 25, 50, false, 24);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_FrontWalk | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 27, 34, 50, true, 27);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackWalk | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 35, 44, 50, true, 35);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackStep | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 45, 48, 50, false, 45);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Run | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 49, 57, 50, true, 51);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_RunEnd | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 58, 60, 50, false, 59);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Jump | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 61, 69, 50, false, 61);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Dash | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 70, 77, 50, false, 70);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_RollingBack | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 78, 87, 50, false, 78);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Guard | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 541, 541, 50, false, 541);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_GuardEnd | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 542, 543, 50, false, 542);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyKick | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 108, 117, 50, false, 108);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightKick | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 94, 98, 50, false, 94);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyPunch | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 99, 107, 50, false, 99);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightPunch | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 88, 93, 50, false, 88);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyKick_Seat | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 181, 191, 50, false, 181);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightKick_Seat | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 165, 171, 50, false, 165);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyPunch_Seat | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 172, 180, 50, false, 172);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightPunch_Seat | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 192, 197, 50, false, 192);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyKick_Jump | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 213, 218, 50, false, 213);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightKick_Jump | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 204, 205, 50, false, 204);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyPunch_Jump | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 206, 212, 50, false, 206);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightPunch_Jump | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 198, 203, 50, false, 198);
  pRender_->CreateAnimation((IORI_ANIMTYPE_108ShikiYamiBarai | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 223, 230, 50, false, 223);
  pRender_->CreateAnimation((IORI_ANIMTYPE_GaishikiMutan_1 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 99, 107, 50, false, 99);
  pRender_->CreateAnimation((IORI_ANIMTYPE_GaishikiMutan_2 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 160, 164, 50, false, 160);
  pRender_->CreateAnimation((IORI_ANIMTYPE_Shinigami | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 136, 144, 50, false, 136);
  pRender_->CreateAnimation((IORI_ANIMTYPE_HyakushikiOniyaki | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 276, 291, 50, false, 276);
  pRender_->CreateAnimation((IORI_ANIMTYPE_127ShikiAoiHana_1 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 255, 261, 50, false, 255);
  pRender_->CreateAnimation((IORI_ANIMTYPE_127ShikiAoiHana_2 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 262, 268, 50, false, 262);
  pRender_->CreateAnimation((IORI_ANIMTYPE_127ShikiAoiHana_3 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 269, 275, 50, false, 269);
  pRender_->CreateAnimation((IORI_ANIMTYPE_UltimateCasting | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 344, 347, 100, false, 344);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_1 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 70, 77, 20, false, 70);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_2 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 118, 122, 20, false, 118);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_3 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 88, 92, 20, false, 88);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_4 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 128, 135, 20, false, 128);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_5 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 223, 229, 20, false, 223);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_6 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 99, 106, 20, false, 99);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_7 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 159, 163, 20, false, 159);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_8 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 99, 107, 20, false, 99);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_9 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 347, 352, 250, false, 347);

  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Idle | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 7, 15, 50, true, 7);         // ¾ÆÀÌµé
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_SeatDown | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 16, 23, 50, true, 18);   // ¾É±â. Down
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_SeatUp | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 24, 25, 50, false, 24);    // ¾É±â. Up
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_FrontWalk | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 27, 34, 50, true, 27);  // -> °È±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackWalk | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 35, 44, 50, true, 35);   // <- µÚ·Î°¡±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackStep | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 45, 48, 50, false, 45);  // <- <- ¹é½ºÅÇ
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Run | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 49, 57, 50, true, 51);        // ->-> ¶Ù±â Start
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_RunEnd | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 58, 60, 50, false, 59);    // ->-> ¶Ù±â Stop
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Jump | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 61, 69, 50, false, 61);      // Á¡ÇÁ
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Dash | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 70, 77, 50, false, 70);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_RollingBack | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 78, 87, 50, false, 78);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Guard | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 541, 541, 50, false, 541);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_GuardEnd | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 542, 543, 50, false, 542);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyKick | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 108, 117, 50, false, 108);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightKick | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 94, 98, 50, false, 94);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyPunch | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 99, 107, 50, false, 99);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightPunch | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 88, 93, 50, false, 88);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyKick_Seat | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 181, 191, 50, false, 181);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightKick_Seat | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 165, 171, 50, false, 165);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyPunch_Seat | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 172, 180, 50, false, 172);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightPunch_Seat | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 192, 197, 50, false, 192);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyKick_Jump | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 213, 218, 50, false, 213);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightKick_Jump | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 204, 205, 50, false, 204);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyPunch_Jump | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 206, 212, 50, false, 206);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightPunch_Jump | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 198, 203, 50, false, 198);
  pRender_->CreateAnimation((IORI_ANIMTYPE_108ShikiYamiBarai | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 223, 230, 50, false, 223);
  pRender_->CreateAnimation((IORI_ANIMTYPE_GaishikiMutan_1 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 99, 107, 50, false, 99);
  pRender_->CreateAnimation((IORI_ANIMTYPE_GaishikiMutan_2 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 160, 164, 50, false, 160);
  pRender_->CreateAnimation((IORI_ANIMTYPE_Shinigami | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 136, 144, 50, false, 136);
  pRender_->CreateAnimation((IORI_ANIMTYPE_HyakushikiOniyaki | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 276, 291, 50, false, 276);
  pRender_->CreateAnimation((IORI_ANIMTYPE_127ShikiAoiHana_1 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 255, 261, 50, false, 255);
  pRender_->CreateAnimation((IORI_ANIMTYPE_127ShikiAoiHana_2 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 262, 268, 50, false, 262);
  pRender_->CreateAnimation((IORI_ANIMTYPE_127ShikiAoiHana_3 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 269, 275, 50, false, 269);
  pRender_->CreateAnimation((IORI_ANIMTYPE_UltimateCasting | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 344, 347, 100, false, 344);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_1 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 70, 77, 20, false, 70);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_2 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 118, 122, 20, false, 118);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_3 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 88, 92, 20, false, 88);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_4 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 128, 135, 20, false, 128);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_5 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 223, 229, 20, false, 223);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_6 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 99, 106, 20, false, 99);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_7 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 159, 163, 20, false, 159);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_8 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 99, 107, 20, false, 99);
  pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_9 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 347, 352, 250, false, 347);
  UpdateAnimState(PLAYER_ANIMTYPE_Idle);

  // STATE
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Idle, {PS_Idle}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatDown, {PS_Seat}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatUp, {PS_Seat}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_FrontWalk, {PS_Move}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackWalk, {PS_Move}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackStep, {PS_Move}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Run, {PS_Move}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_RunEnd, {PS_Move}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Jump, {PS_Jump}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Dash, {PS_Rolling}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_RollingBack, {PS_Rolling}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Guard, {PS_Guard}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_GuardEnd, {PS_Guard}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick, {PS_Attack}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick, {PS_Attack}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch, {PS_Attack}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch, {PS_Attack}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_Seat, {PS_Seat, PS_Attack}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_Seat, {PS_Seat, PS_Attack}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_Seat, {PS_Seat, PS_Attack}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_Seat, {PS_Seat, PS_Attack}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick_Jump, {PS_Jump, PS_Attack}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick_Jump, {PS_Jump, PS_Attack}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch_Jump, {PS_Jump, PS_Attack}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch_Jump, {PS_Jump, PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_108ShikiYamiBarai, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_1, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_2, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_Shinigami, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_HyakushikiOniyaki, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_1, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_2, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_3, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_UltimateCasting, {PS_SkillCasting}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_1, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_2, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_3, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_4, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_5, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_6, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_7, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_8, {PS_Attack}, false);
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_9, {PS_Attack}, false);

  // DAMAGE
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_108ShikiYamiBarai, ATTYPE_NormalAttack, ELMTTYPE_BlueFlame, EFKEY_Hit_2, 5.0f, {20.0f, 60.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {5.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {20.0f, 40.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Shinigami, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 15.0f, {20.0f, 80.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_HyakushikiOniyaki, ATTYPE_NormalAttack, ELMTTYPE_BlueFlame, EFKEY_Hit_2, 20.0f, {40.0f, 80.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {10.0f, 00.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {10.0f, 00.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_3, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {20.0f, 80.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_1, ATTYPE_LowAttack, ELMTTYPE_BlueFlame, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_2, ATTYPE_HighAttack, ELMTTYPE_BlueFlame, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_3, ATTYPE_HighAttack, ELMTTYPE_BlueFlame, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_4, ATTYPE_HighAttack, ELMTTYPE_BlueFlame, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_5, ATTYPE_LowAttack, ELMTTYPE_BlueFlame, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_6, ATTYPE_LowAttack, ELMTTYPE_BlueFlame, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_7, ATTYPE_HighAttack, ELMTTYPE_BlueFlame, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_8, ATTYPE_LowAttack, ELMTTYPE_BlueFlame, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_9, ATTYPE_StrongAttack, ELMTTYPE_BlueFlame, EFKEY_Iori_Explosion, 10.0f, {45.0f, 60.0f});

  // SKILL
  pSkillComponent_->RegistSkill(IORI_SKILL_GaishikiMutan, &Iori::GaishikiMutan, this);
  pSkillComponent_->RegistSkill(IORI_SKILL_108ShikiYamiBarai, &Iori::ShikiYamiBarai108, this);
  pSkillComponent_->RegistSkill(IORI_SKILL_Shinigami, &Iori::Shinigami, this);
  pSkillComponent_->RegistSkill(IORI_SKILL_HyakushikiOniyaki, &Iori::HyakushikiOniyaki, this);
  pSkillComponent_->RegistSkill(IORI_SKILL_127ShikiAoiHana, &Iori::ShikiAoiHana127, this);
  pSkillComponent_->RegistSkill(IORI_SKILL_1211ShikiYaOtome, &Iori::ShikiYaOtome1211, this);

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

  // PROJECTILE
  pProjectileComponent_->RegistProjectileInfo(IORI_PROJECTILE_108ShikiYamiBarai, IMGTYPE_IoriImage, 239, 244, 20, true, {169, 139, 150, 0}, {35.0f, 0.0f}, {180.0f, 50.0f}, {1500.0f, 0.0f});
  pProjectileComponent_->RegistProjectileInfo(IORI_PROJECTILE_HyakushikiOniyaki_Low, IMGTYPE_IoriImage, 292, 301, 50, false, {169, 139, 150, 0}, {0.0f, -7.0f}, {50.0f, -30.0f}, {0.0f, 0.0f});
  pProjectileComponent_->RegistProjectileInfo(IORI_PROJECTILE_HyakushikiOniyaki_High, IMGTYPE_IoriImage, 302, 311, 40, false, {169, 139, 150, 0}, {0.0f, -7.0f}, {-80.0f, -200.0f}, {0.0f, 0.0f});

  // GHOST EFFECT
  //pGhostEffect_->SetTransparentColor(ioriTransparentColor);
}

void Iori::CompareInputBitset() {
  if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00000000")) &&
      true == IsEqualInputBitSet(inputUpBitSet_, std::bitset<8>("00000000")) &&
      false == pStateComponent_->ContainPlayerState({PS_Jump})) {
    if (PLAYER_ANIMTYPE_SeatDown == pStateComponent_->GetCurAnimState()) {
      UpdateAnimState(PLAYER_ANIMTYPE_SeatUp);
      return;
    }

    if (PLAYER_ANIMTYPE_Run == pStateComponent_->GetCurAnimState()) {
      UpdateAnimState(PLAYER_ANIMTYPE_RunEnd);
      return;
    }

    UpdateAnimState(PLAYER_ANIMTYPE_Idle);
    return;
  }

  // JUMP STATE
  else if (true == pStateComponent_->EqualPlayerState({PS_Jump})) {
    // A | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_Jump);
      return;
    }
    // B | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000100"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightKick_Jump);
      return;
    }
    // C | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000010"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_Jump);
      return;
    }
    // D | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000001"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_Jump);
      return;
    }
    if (true == pRender_->IsAnimationEnd()) {
      UpdateAnimState(PLAYER_ANIMTYPE_Idle);
      return;
    }
  }

  // SEAT STATE
  else if (true == pStateComponent_->ContainPlayerState({PS_Seat})) {
    // A | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01001000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_Seat);
      return;
    }
    // B | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01000100"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightKick_Seat);
      return;
    }
    // C | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01000010"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_Seat);
      return;
    }
    // D | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01000001"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_Seat);
      return;
    }
    // DOWN | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01000000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_SeatDown, 18, 50);
      return;
    }
  }

  // NORAL STATE
  else {
    // LEFT UP | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("10010000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_Jump);
      pMovementComponent_->JumpForward(!FacingRight(), false);
      return;
    }

    // RIGHT UP | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00110000"))) {
      if (PLAYER_ANIMTYPE_Run == pStateComponent_->GetCurAnimState()) {
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

    // A B LEFT | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("10001100"))) {
      UpdateAnimState((PLAYER_ANIMTYPE_RollingBack));
      pMovementComponent_->Dash(!FacingRight(), 150.0f, 300.0f);
      pGhostEffect_->On();
      return;
    }

    // A B | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001100"))) {
      UpdateAnimState((PLAYER_ANIMTYPE_Dash));
      pMovementComponent_->Dash(FacingRight(), 150.0f, 300.0f);
      pGhostEffect_->On();
      return;
    }
    

    
     
    // RIGHT A | PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00101000"))) {
      UpdateAnimState(IORI_ANIMTYPE_GaishikiMutan_1);
      pSkillComponent_->ActivateSkill(IORI_SKILL_GaishikiMutan);
      return;
    }

    // RIGHT B | PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00100100"))) {
      UpdateAnimState(IORI_ANIMTYPE_Shinigami);
      pSkillComponent_->ActivateSkill(IORI_SKILL_Shinigami);
      return;
    }

    // LEFT | PRESS Contain
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("10000000"))) {
      if (pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
        UpdateAnimState(PLAYER_ANIMTYPE_Guard);
        return;
      }
    }

    if (PLAYER_ANIMTYPE_Guard == pStateComponent_->GetCurAnimState()) {
      UpdateAnimState(PLAYER_ANIMTYPE_GuardEnd);
      return;
    }
    
    // LEFT | PRESS Equal
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("10000000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_BackWalk);
      pMovementComponent_->MoveBack(FacingRight());
      return;
    }

    // LEFT | UP
    if (true == IsEqualInputBitSet(inputUpBitSet_, std::bitset<8>("10000000"))) {
    }

    // DOWN | PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("01000000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_SeatDown);
      return;
    }

    // DOWN | UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("01000000"))) {
    }

    // RIGHT | PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00100000"))) {
      if (PLAYER_ANIMTYPE_Run == animState_) {
        pMovementComponent_->Run(FacingRight());
        return;
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_FrontWalk);
        pMovementComponent_->Move(FacingRight());
        return;
      }
    }

    // RIGHT | UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00100000"))) {
    }

    // UP | PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00010000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_Jump);
      pMovementComponent_->Jump();
      return;
    }

    // UP | UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00010000"))) {
    }

    // A | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightPunch);
      return;
    }

    // A | UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00001000"))) {
    }

    // B | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000100"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightKick);
      return;
    }

    // B | UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00000100"))) {
    }

    // C | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000010"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch);
      return;
    }

    // C | UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00000010"))) {
    }

    // D | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000001"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick);
      return;
    }

    // D | UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00000001"))) {
    }
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
  Level* pLevel = GetLevel();
  if (nullptr == pLevel) {
    return;
  }

  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }

  BackGroundMask* pBackGroundMask = pKOFLevel->GetBackGroundMask();
  if (nullptr == pBackGroundMask) {
    return;
  }

  UpdateAnimState(IORI_ANIMTYPE_UltimateCasting);
  pSkillComponent_->ActivateSkill(IORI_SKILL_1211ShikiYaOtome);

  EffectManager::Instance()->SpawnEffect(pKOFLevel, EFKEY_Casting_1, GetPosition() + Vector{0.0f, -250.0f});
  EffectManager::Instance()->SpawnEffect(pKOFLevel, EFKEY_Casting_2, GetPosition() + Vector{0.0f, -250.0f});
  pKOFLevel->FreezeActors({pOpponentPlayer_}, true);
  pBackGroundMask->FadeOut(IMGTYPE_BlackBoardImage, 50.0f);
}

void Iori::GaishikiMutan() {
  if (true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();

  if (IORI_ANIMTYPE_GaishikiMutan_1 == pStateComponent_->GetCurAnimState()) {
    if (100 <= curImageIndex && 104 >= curImageIndex) {
      if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000"))) {
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

  if (226 == curImageIndex) {
    pProjectileComponent_->FireProjectile(IORI_PROJECTILE_108ShikiYamiBarai, FacingRight());
  }
}

void Iori::Shinigami() {
  if (nullptr == pRender_) {
    return;
  }

  if (true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
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
    pProjectileComponent_->FireProjectile(IORI_PROJECTILE_HyakushikiOniyaki_Low, FacingRight());
  }

  if (284 == curImageIndex) {
    pProjectileComponent_->FireProjectile(IORI_PROJECTILE_HyakushikiOniyaki_High, FacingRight());
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
      if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000")) ||
          true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000010"))) {
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
      if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000")) ||
          true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000010"))) {
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

  BackGroundMask* pBackGroundMask = pKOFLevel->GetBackGroundMask();
  if (nullptr == pBackGroundMask) {
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();

  switch (pStateComponent_->GetCurAnimState()) {
    case IORI_ANIMTYPE_UltimateCasting: {
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
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_2);
        pOpponentPlayer_->SetControlLocked(true);
        pMovementComponent_->Dash(FacingRight(), 250.0f, 1000.0f);
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
      if (349 == curImageIndex) {
        const Vector& ioriPosition = GetPosition();
        pOpponentPlayer_->SetPosition(ioriPosition + Vector{100.0f * FacingRightFlag(), -50.0f});
        break;
      }
      if (351 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
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
