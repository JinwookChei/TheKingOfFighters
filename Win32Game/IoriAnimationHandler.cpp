#include "stdafx.h"
#include "AnimationHandler.h"
#include "IoriAnimationHandler.h"

#define ANIMINTERVAL 30

IoriAnimationHandler::IoriAnimationHandler() {
}

IoriAnimationHandler::~IoriAnimationHandler() {
}

void IoriAnimationHandler::Tick(unsigned long long deltaTick) {

  if (PLAYER_ANIMTYPE_JumpUp == pOwnerStateComponent_->GetCurAnimState()) {
    if (true == pOwnerMovementComponent_->IsFalling()) {
      pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_JumpDown, curAnimationModifier_, true);
    }
  }

  if (PLAYER_ANIMTYPE_JumpDown == pOwnerStateComponent_->GetCurAnimState()) {
    if (true == pOwnerMovementComponent_->IsOnGround()) {
      pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_JumpLand, curAnimationModifier_, true);
    }
  }

  if (PLAYER_ANIMTYPE_JumpLand == pOwnerStateComponent_->GetCurAnimState()) {
    if (true == pOwnerRenderer_->IsAnimationEnd()) {
      pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_Idle, curAnimationModifier_, true);
    }
  }
}

bool IoriAnimationHandler::RegistAnimations() {
  CallCreateAnimation(PLAYER_ANIMTYPE_StartPos, IMGTYPE_IoriImage, 0, 15, ANIMINTERVAL, true, 7);
  CallCreateAnimation(PLAYER_ANIMTYPE_Idle, IMGTYPE_IoriImage, 7, 15, ANIMINTERVAL, true, 7);
  CallCreateAnimation(PLAYER_ANIMTYPE_SeatDown, IMGTYPE_IoriImage, 16, 23, ANIMINTERVAL, true, 18);
  CallCreateAnimation(PLAYER_ANIMTYPE_SeatUp, IMGTYPE_IoriImage, 24, 25, ANIMINTERVAL, false, 24);
  CallCreateAnimation(PLAYER_ANIMTYPE_FrontWalk, IMGTYPE_IoriImage, 27, 34, ANIMINTERVAL, true, 27);
  CallCreateAnimation(PLAYER_ANIMTYPE_BackWalk, IMGTYPE_IoriImage, 35, 44, ANIMINTERVAL, true, 35);
  CallCreateAnimation(PLAYER_ANIMTYPE_BackStep, IMGTYPE_IoriImage, 45, 48, ANIMINTERVAL, false, 45);
  CallCreateAnimation(PLAYER_ANIMTYPE_Run, IMGTYPE_IoriImage, 49, 57, ANIMINTERVAL, true, 51);
  CallCreateAnimation(PLAYER_ANIMTYPE_RunEnd, IMGTYPE_IoriImage, 58, 60, ANIMINTERVAL, false, 59);
  CallCreateAnimation(PLAYER_ANIMTYPE_JumpUp, IMGTYPE_IoriImage, 61, 65, ANIMINTERVAL, false, 61);
  CallCreateAnimation(PLAYER_ANIMTYPE_JumpDown, IMGTYPE_IoriImage, 66, 68, ANIMINTERVAL, false, 66);
  CallCreateAnimation(PLAYER_ANIMTYPE_JumpLand, IMGTYPE_IoriImage, 69, 69, ANIMINTERVAL, false, 69);
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
  return true;
}
