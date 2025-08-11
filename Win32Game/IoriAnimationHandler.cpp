#include "stdafx.h"
#include "AnimationHandler.h"
#include "IoriAnimationHandler.h"

#define ANIMINTERVAL 35
//#define ANIMINTERVAL 300

IoriAnimationHandler::IoriAnimationHandler() {
}

IoriAnimationHandler::~IoriAnimationHandler() {
}

void IoriAnimationHandler::Tick(unsigned long long deltaTick) {
  InitCondition();

  UpdateAnimation();
}


bool IoriAnimationHandler::RegistAnimations() {
  CallCreateAnimation(PLAYER_ANIMTYPE_StartPos, IMGTYPE_IoriImage, 0, 15, ANIMINTERVAL, true, 7);
  CallCreateAnimation(PLAYER_ANIMTYPE_Idle, IMGTYPE_IoriImage, 7, 15, ANIMINTERVAL, true, 7);
  CallCreateAnimation(PLAYER_ANIMTYPE_SeatDown, IMGTYPE_IoriImage, 16, 17, ANIMINTERVAL, false, 16);
  CallCreateAnimation(PLAYER_ANIMTYPE_Seat, IMGTYPE_IoriImage, 18, 23, ANIMINTERVAL, true, 18);
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
  CallCreateAnimation(PLAYER_ANIMTYPE_LightKick_Jump, IMGTYPE_IoriImage, {204, 204, 205, 205}, ANIMINTERVAL, false, 204);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyPunch_Jump, IMGTYPE_IoriImage, 206, 212, ANIMINTERVAL, false, 206);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightPunch_Jump, IMGTYPE_IoriImage, 198, 203, ANIMINTERVAL, false, 198);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_High, IMGTYPE_IoriImage, 557, 562, ANIMINTERVAL, false, 557);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_Low, IMGTYPE_IoriImage, 563, 567, ANIMINTERVAL, false, 563);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_Strong, IMGTYPE_IoriImage, 594, 607, ANIMINTERVAL, false, 594);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_AirborneUp, IMGTYPE_IoriImage, 594, 597, ANIMINTERVAL, false, 594);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_AirborneDown, IMGTYPE_IoriImage, 608, 608, ANIMINTERVAL, false, 608);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_AirborneLand, IMGTYPE_IoriImage, {609, 610, 611, 611, 611, 611, 611, 611}, ANIMINTERVAL, false, 609);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_AirborneGetUp, IMGTYPE_IoriImage, 612, 615, ANIMINTERVAL, false, 612);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_Seat, IMGTYPE_IoriImage, 552, 556, ANIMINTERVAL, false, 552);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_JumpUp, IMGTYPE_IoriImage, {595}, 160, false, 595);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_JumpDown, IMGTYPE_IoriImage, 80, 85, ANIMINTERVAL, false, 82);
  CallCreateAnimation(PLAYER_ANIMTYPE_Grabbed, IMGTYPE_IoriImage, {557}, 150, false, 557);
  CallCreateAnimation(PLAYER_ANIMTYPE_NeckGrabbed, IMGTYPE_IoriImage, 572, 575, 150, false, 572);
  CallCreateAnimation(IORI_ANIMTYPE_108ShikiYamiBarai, IMGTYPE_IoriImage, 223, 230, ANIMINTERVAL, false, 223);
  CallCreateAnimation(IORI_ANIMTYPE_GaishikiMutan_1, IMGTYPE_IoriImage, 99, 107, ANIMINTERVAL, false, 99);
  CallCreateAnimation(IORI_ANIMTYPE_GaishikiMutan_2, IMGTYPE_IoriImage, 160, 164, ANIMINTERVAL, false, 160);
  CallCreateAnimation(IORI_ANIMTYPE_Shinigami, IMGTYPE_IoriImage, 145, 156, ANIMINTERVAL, false, 145);
  CallCreateAnimation(IORI_ANIMTYPE_HyakushikiOniyaki, IMGTYPE_IoriImage, 276, 291, ANIMINTERVAL, false, 276);
  CallCreateAnimation(IORI_ANIMTYPE_127ShikiAoiHana_1, IMGTYPE_IoriImage, 255, 261, ANIMINTERVAL, false, 255);
  CallCreateAnimation(IORI_ANIMTYPE_127ShikiAoiHana_2, IMGTYPE_IoriImage, 262, 268, ANIMINTERVAL, false, 262);
  CallCreateAnimation(IORI_ANIMTYPE_127ShikiAoiHana_3, IMGTYPE_IoriImage, 269, 275, ANIMINTERVAL, false, 269);
  CallCreateAnimation(PLAYER_ANIMTYPE_UltimateCasting, IMGTYPE_IoriImage, 344, 347, 70, false, 344);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_1, IMGTYPE_IoriImage, 70, 77, 32, false, 70);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_2, IMGTYPE_IoriImage, 118, 122, 16, false, 118);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_3, IMGTYPE_IoriImage, 88, 92, 16, false, 88);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_4, IMGTYPE_IoriImage, 128, 135, 16, false, 128);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_5, IMGTYPE_IoriImage, 223, 229, 16, false, 223);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_6, IMGTYPE_IoriImage, 99, 107, 16, false, 99);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_7, IMGTYPE_IoriImage, 159, 163, 16, false, 159);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_8, IMGTYPE_IoriImage, 99, 107, 16, false, 99);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_9, IMGTYPE_IoriImage, 347, 352, 180, false, 347);
  CallCreateAnimation(IORI_ANIMTYPE_Ura306shikiShika_1, IMGTYPE_IoriImage, 353, 360, 16, false, 353);
  CallCreateAnimation(IORI_ANIMTYPE_Ura306shikiShika_2, IMGTYPE_IoriImage, 361, 370, 30, false, 161);
  CallCreateAnimation(IORI_ANIMTYPE_Ura306shikiShika_3, IMGTYPE_IoriImage, 371, 386, 20, false, 371);

  RegistAnimTransition(PLAYER_ANIMTYPE_JumpUp, (TRANSITION_CONDITION::MovementFalling), false, PLAYER_ANIMTYPE_JumpDown);
  RegistAnimTransition(PLAYER_ANIMTYPE_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_JumpLand);
  RegistAnimTransition(PLAYER_ANIMTYPE_JumpLand, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_HeavyKick_Jump, (TRANSITION_CONDITION::AnimationEnd | TRANSITION_CONDITION::MovementFalling), true, PLAYER_ANIMTYPE_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_JumpLand);
  RegistAnimTransition(PLAYER_ANIMTYPE_HeavyPunch_Jump, (TRANSITION_CONDITION::AnimationEnd | TRANSITION_CONDITION::MovementFalling), true, PLAYER_ANIMTYPE_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_JumpLand);
  RegistAnimTransition(PLAYER_ANIMTYPE_LightKick_Jump, (TRANSITION_CONDITION::AnimationEnd | TRANSITION_CONDITION::MovementFalling), true, PLAYER_ANIMTYPE_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_JumpLand);
  RegistAnimTransition(PLAYER_ANIMTYPE_LightPunch_Jump, (TRANSITION_CONDITION::AnimationEnd | TRANSITION_CONDITION::MovementFalling), true, PLAYER_ANIMTYPE_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_JumpLand);
  RegistAnimTransition(PLAYER_ANIMTYPE_SeatDown, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);
  RegistAnimTransition(PLAYER_ANIMTYPE_HeavyKick_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);
  RegistAnimTransition(PLAYER_ANIMTYPE_LightKick_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);
  RegistAnimTransition(PLAYER_ANIMTYPE_HeavyPunch_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);
  RegistAnimTransition(PLAYER_ANIMTYPE_LightPunch_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);
  RegistAnimTransition(PLAYER_ANIMTYPE_SeatUp, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_BackStep, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_RunEnd, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_Dash, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_RollingBack, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_Guard, (TRANSITION_CONDITION::OpponentPlayerAttackFinished), false, PLAYER_ANIMTYPE_GuardEnd);
  RegistAnimTransition(PLAYER_ANIMTYPE_GuardEnd, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_Guard_Seat, (TRANSITION_CONDITION::OpponentPlayerAttackFinished), false, PLAYER_ANIMTYPE_GuardEnd_Seat);
  RegistAnimTransition(PLAYER_ANIMTYPE_GuardEnd_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);
  RegistAnimTransition(PLAYER_ANIMTYPE_HeavyKick_CloseRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_LightKick_CloseRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_LightPunch_CloseRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_HeavyKick_LongRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_LightKick_LongRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_HeavyPunch_LongRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_LightPunch_LongRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_HeavyKick_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_SeatDown);
  RegistAnimTransition(PLAYER_ANIMTYPE_LightKick_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_SeatDown);
  RegistAnimTransition(PLAYER_ANIMTYPE_HeavyPunch_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_SeatDown);
  RegistAnimTransition(PLAYER_ANIMTYPE_LightPunch_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_SeatDown);
  RegistAnimTransition(PLAYER_ANIMTYPE_Hit_High, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_Hit_Low, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_Hit_Strong, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_Hit_JumpUp, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Hit_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_Hit_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_Hit_AirborneUp, (TRANSITION_CONDITION::MovementFalling), false, PLAYER_ANIMTYPE_Hit_AirborneDown);
  RegistAnimTransition(PLAYER_ANIMTYPE_Hit_AirborneDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_Hit_AirborneLand);
  RegistAnimTransition(PLAYER_ANIMTYPE_Hit_AirborneLand, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Hit_AirborneGetUp);
  RegistAnimTransition(PLAYER_ANIMTYPE_Hit_AirborneGetUp, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  RegistAnimTransition(PLAYER_ANIMTYPE_Hit_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);

  return true;
}

