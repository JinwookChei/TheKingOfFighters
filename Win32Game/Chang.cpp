#include "stdafx.h"
#include "KOFPlayer.h"
#include "MovementComponent.h"
#include "SoundTable.h"
#include "AttackTable.h"
#include "SkillComponent.h"
#include "CommandComponent.h"
#include "StateComponent.h"
#include "RestrictionComponent.h"
#include "GhostEffect.h"
#include "AnimationStateMachine.h"
#include "InputController.h"
#include "Chang.h"

#define ANIMINTERVAL 35

Chang::Chang() {
}

Chang::~Chang() {
}

void Chang::BeginPlay() {
}

void Chang::Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) {
  KOFPlayer::Initialize(isPlayer1, position, useCameraPosition, opponentPlayer);

  // CHARACTER SETTING
  IImage* pImage = ImgManager::GetIntance()->GetImg(IMGTYPE_ChangImage);
  if (nullptr == pImage) {
    return;
  }

  SetCharacterScale(pImage->GetScale(8) * pRender_->GetLocalScale());

  // ANIM
  CallCreateAnimation(PLAYER_ANIMTYPE_StartPos, IMGTYPE_ChangImage, 0, 7, ANIMINTERVAL, false, 7);
  CallCreateAnimation(PLAYER_ANIMTYPE_Idle, IMGTYPE_ChangImage, 8, 13, ANIMINTERVAL, true, 8);
  CallCreateAnimation(PLAYER_ANIMTYPE_SeatDown, IMGTYPE_ChangImage, 14, 15, ANIMINTERVAL, false, 14);
  CallCreateAnimation(PLAYER_ANIMTYPE_Seat, IMGTYPE_ChangImage, 16, 20, ANIMINTERVAL, true, 16);
  CallCreateAnimation(PLAYER_ANIMTYPE_SeatUp, IMGTYPE_ChangImage, 21, 22, ANIMINTERVAL, false, 21);
  CallCreateAnimation(PLAYER_ANIMTYPE_FrontWalk, IMGTYPE_ChangImage, 23, 32, ANIMINTERVAL, true, 23);
  CallCreateAnimation(PLAYER_ANIMTYPE_BackWalk, IMGTYPE_ChangImage, 23, 32, ANIMINTERVAL, true, 23);
  CallCreateAnimation(PLAYER_ANIMTYPE_BackStep, IMGTYPE_ChangImage, 33, 35, ANIMINTERVAL, false, 33);
  CallCreateAnimation(PLAYER_ANIMTYPE_Run, IMGTYPE_ChangImage, 23, 32, 16, true, 23);
  CallCreateAnimation(PLAYER_ANIMTYPE_RunEnd, IMGTYPE_ChangImage, {32}, 16, false, 32);
  CallCreateAnimation(PLAYER_ANIMTYPE_JumpUp, IMGTYPE_ChangImage, 36, 39, ANIMINTERVAL, false, 36);
  CallCreateAnimation(PLAYER_ANIMTYPE_JumpDown, IMGTYPE_ChangImage, 40, 41, ANIMINTERVAL, false, 40);
  CallCreateAnimation(PLAYER_ANIMTYPE_JumpLand, IMGTYPE_ChangImage, {42}, ANIMINTERVAL, false, 42);
  CallCreateAnimation(PLAYER_ANIMTYPE_Dash, IMGTYPE_ChangImage, 43, 51, ANIMINTERVAL, false, 43);
  CallCreateAnimation(PLAYER_ANIMTYPE_RollingBack, IMGTYPE_ChangImage, 52, 61, ANIMINTERVAL, false, 52);
  CallCreateAnimation(PLAYER_ANIMTYPE_Guard, IMGTYPE_ChangImage, {293}, ANIMINTERVAL, false, 293);
  CallCreateAnimation(PLAYER_ANIMTYPE_GuardEnd, IMGTYPE_ChangImage, 294, 295, ANIMINTERVAL, false, 294);
  CallCreateAnimation(PLAYER_ANIMTYPE_Guard_Seat, IMGTYPE_ChangImage, {302}, ANIMINTERVAL, true, 302);
  CallCreateAnimation(PLAYER_ANIMTYPE_GuardEnd_Seat, IMGTYPE_ChangImage, 303, 305, ANIMINTERVAL, false, 303);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyKick_CloseRange, IMGTYPE_ChangImage, 107, 111, ANIMINTERVAL, false, 107);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightKick_CloseRange, IMGTYPE_ChangImage, 66, 69, ANIMINTERVAL, false, 66);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, IMGTYPE_ChangImage, 96, 104, ANIMINTERVAL, false, 96);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightPunch_CloseRange, IMGTYPE_ChangImage, 90, 95, ANIMINTERVAL, false, 90);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyKick_LongRange, IMGTYPE_ChangImage, 82, 89, ANIMINTERVAL, false, 82);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightKick_LongRange, IMGTYPE_ChangImage, 66, 69, ANIMINTERVAL, false, 66);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyPunch_LongRange, IMGTYPE_ChangImage, 70, 77, ANIMINTERVAL, false, 70);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightPunch_LongRange, IMGTYPE_ChangImage, 62, 66, ANIMINTERVAL, false, 62);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyKick_Seat, IMGTYPE_ChangImage, 173, 182, ANIMINTERVAL, false, 173);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightKick_Seat, IMGTYPE_ChangImage, 152, 159, ANIMINTERVAL, false, 152);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyPunch_Seat, IMGTYPE_ChangImage, 160, 172, ANIMINTERVAL, false, 160);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightPunch_Seat, IMGTYPE_ChangImage, 146, 151, ANIMINTERVAL, false, 146);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyKick_Jump, IMGTYPE_ChangImage, 197, 201, ANIMINTERVAL, false, 197);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightKick_Jump, IMGTYPE_ChangImage, 187, 189, ANIMINTERVAL, false, 187);
  CallCreateAnimation(PLAYER_ANIMTYPE_HeavyPunch_Jump, IMGTYPE_ChangImage, 190, 196, ANIMINTERVAL, false, 190);
  CallCreateAnimation(PLAYER_ANIMTYPE_LightPunch_Jump, IMGTYPE_ChangImage, 183, 186, ANIMINTERVAL, false, 183);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_High, IMGTYPE_ChangImage, 310, 314, ANIMINTERVAL, false, 310);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_Low, IMGTYPE_ChangImage, 315, 319, ANIMINTERVAL, false, 315);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_Strong, IMGTYPE_ChangImage, 339, 350, ANIMINTERVAL, false, 339);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_AirborneUp, IMGTYPE_ChangImage, 339, 341, ANIMINTERVAL, false, 339);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_AirborneDown, IMGTYPE_ChangImage, 351, 353, ANIMINTERVAL, false, 351);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_AirborneLand, IMGTYPE_ChangImage, {354, 354, 355, 355, 355, 355}, ANIMINTERVAL, false, 354);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_AirborneGetUp, IMGTYPE_ChangImage, 356, 358, ANIMINTERVAL, false, 356);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_Seat, IMGTYPE_ChangImage, 320, 324, ANIMINTERVAL, false, 320);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_JumpUp, IMGTYPE_ChangImage, {339, 341}, 80, false, 339);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_JumpDown, IMGTYPE_ChangImage, 54, 59, ANIMINTERVAL, false, 54);
  CallCreateAnimation(PLAYER_ANIMTYPE_NeckGrabbed, IMGTYPE_ChangImage, 325, 330, 150, false, 325);
  CallCreateAnimation(PLAYER_ANIMTYPE_KOKnockBackUp, IMGTYPE_ChangImage, 339, 342, ANIMINTERVAL, false, 339);
  CallCreateAnimation(PLAYER_ANIMTYPE_KOKnockBackDown, IMGTYPE_ChangImage, 351, 353, ANIMINTERVAL, false, 351);
  CallCreateAnimation(PLAYER_ANIMTYPE_KOKnockBackLand, IMGTYPE_ChangImage, {354}, ANIMINTERVAL, true, 354);


  //CallCreateAnimation(PLAYER_ANIMTYPE_UltimateCasting, IMGTYPE_ChangImage, 344, 347, 70, false, 344);
  CallCreateAnimation(IORI_ANIMTYPE_108ShikiYamiBarai, IMGTYPE_ChangImage, 223, 230, ANIMINTERVAL, false, 223);
  CallCreateAnimation(IORI_ANIMTYPE_GaishikiMutan_1, IMGTYPE_ChangImage, 99, 107, ANIMINTERVAL, false, 99);
  CallCreateAnimation(IORI_ANIMTYPE_GaishikiMutan_2, IMGTYPE_ChangImage, 160, 164, ANIMINTERVAL, false, 160);
  CallCreateAnimation(IORI_ANIMTYPE_Shinigami, IMGTYPE_ChangImage, 145, 156, ANIMINTERVAL, false, 145);
  CallCreateAnimation(IORI_ANIMTYPE_HyakushikiOniyaki, IMGTYPE_ChangImage, 276, 291, ANIMINTERVAL, false, 276);
  CallCreateAnimation(IORI_ANIMTYPE_127ShikiAoiHana_1, IMGTYPE_ChangImage, 255, 261, ANIMINTERVAL, false, 255);
  CallCreateAnimation(IORI_ANIMTYPE_127ShikiAoiHana_2, IMGTYPE_ChangImage, 262, 268, ANIMINTERVAL, false, 262);
  CallCreateAnimation(IORI_ANIMTYPE_127ShikiAoiHana_3, IMGTYPE_ChangImage, 269, 275, ANIMINTERVAL, false, 269);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_1, IMGTYPE_ChangImage, 70, 77, 32, false, 70);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_2, IMGTYPE_ChangImage, 118, 122, 16, false, 118);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_3, IMGTYPE_ChangImage, 88, 92, 16, false, 88);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_4, IMGTYPE_ChangImage, 128, 135, 16, false, 128);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_5, IMGTYPE_ChangImage, 223, 229, 16, false, 223);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_6, IMGTYPE_ChangImage, 99, 107, 16, false, 99);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_7, IMGTYPE_ChangImage, 159, 163, 16, false, 159);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_8, IMGTYPE_ChangImage, 99, 107, 16, false, 99);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_9, IMGTYPE_ChangImage, 347, 352, 140, false, 347);
  CallCreateAnimation(IORI_ANIMTYPE_Ura306shikiShika_1, IMGTYPE_ChangImage, 353, 360, 70, false, 353);
  CallCreateAnimation(IORI_ANIMTYPE_Ura306shikiShika_2, IMGTYPE_ChangImage, 361, 370, 30, false, 161);
  CallCreateAnimation(IORI_ANIMTYPE_Ura306shikiShika_3, IMGTYPE_ChangImage, 371, 386, 20, false, 371);

  // ANIM
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_JumpUp, (TRANSITION_CONDITION::MovementFalling), false, PLAYER_ANIMTYPE_JumpDown);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_JumpLand);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_JumpLand, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_HeavyKick_Jump, (TRANSITION_CONDITION::AnimationEnd | TRANSITION_CONDITION::MovementFalling), true, PLAYER_ANIMTYPE_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_JumpLand);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_HeavyPunch_Jump, (TRANSITION_CONDITION::AnimationEnd | TRANSITION_CONDITION::MovementFalling), true, PLAYER_ANIMTYPE_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_JumpLand);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_LightKick_Jump, (TRANSITION_CONDITION::AnimationEnd | TRANSITION_CONDITION::MovementFalling), true, PLAYER_ANIMTYPE_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_JumpLand);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_LightPunch_Jump, (TRANSITION_CONDITION::AnimationEnd | TRANSITION_CONDITION::MovementFalling), true, PLAYER_ANIMTYPE_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_JumpLand);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_SeatDown, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_HeavyKick_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_LightKick_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_HeavyPunch_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_LightPunch_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_SeatUp, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_BackStep, (TRANSITION_CONDITION::AnimationEnd | TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_RunEnd, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_Dash, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_RollingBack, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_Guard, (TRANSITION_CONDITION::OpponentPlayerAttackFinished), false, PLAYER_ANIMTYPE_GuardEnd);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_GuardEnd, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_Guard_Seat, (TRANSITION_CONDITION::OpponentPlayerAttackFinished), false, PLAYER_ANIMTYPE_GuardEnd_Seat);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_GuardEnd_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_HeavyKick_CloseRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_LightKick_CloseRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_LightPunch_CloseRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_HeavyKick_LongRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_LightKick_LongRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_HeavyPunch_LongRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_LightPunch_LongRange, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_HeavyKick_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_SeatDown);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_LightKick_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_SeatDown);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_HeavyPunch_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_SeatDown);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_LightPunch_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_SeatDown);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_Hit_High, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_Hit_Low, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_Hit_Strong, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_Hit_JumpUp, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Hit_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_Hit_JumpDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_Hit_AirborneUp, (TRANSITION_CONDITION::MovementFalling), false, PLAYER_ANIMTYPE_Hit_AirborneDown);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_Hit_AirborneDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_Hit_AirborneLand);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_Hit_AirborneLand, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Hit_AirborneGetUp);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_Hit_AirborneGetUp, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Idle);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_Hit_Seat, (TRANSITION_CONDITION::AnimationEnd), false, PLAYER_ANIMTYPE_Seat);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_KOKnockBackUp, (TRANSITION_CONDITION::MovementFalling), false, PLAYER_ANIMTYPE_KOKnockBackDown);
  pAnimationStateMachine_->RegistAnimTransition(PLAYER_ANIMTYPE_KOKnockBackDown, (TRANSITION_CONDITION::MovementOnGround), false, PLAYER_ANIMTYPE_KOKnockBackLand);

  // SOUND
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_JumpUp, SOUNDTYPE_COMMON_Jump01);
  pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_Run, SOUNDTYPE_COMMON_FootStep);
  //pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_108ShikiYamiBarai, SOUNDTYPE_IORI_108ShikiYamiBarai);
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
  //pSoundTable_->RegistSoundInfo(PLAYER_ANIMTYPE_UltimateCasting, SOUNDTYPE_IORI_1211ShikiYaOtome01);


  /*pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_GaishikiMutan_1, SOUNDTYPE_IORI_Kiai_Light01);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_GaishikiMutan_2, SOUNDTYPE_IORI_Kiai_Light02);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Shinigami, SOUNDTYPE_IORI_Kiai_Light02);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_HyakushikiOniyaki, SOUNDTYPE_IORI_HyakushikiOniyaki);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_1211ShikiYaOtome_4, SOUNDTYPE_IORI_1211ShikiYaOtome02);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_1211ShikiYaOtome_9, SOUNDTYPE_IORI_1211ShikiYaOtome03);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_HyakushikiOniyaki, SOUNDTYPE_IORI_HyakushikiOniyaki);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Ura306shikiShika_1, SOUNDTYPE_IORI_HyakushikiOniyaki);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Ura306shikiShika_2, SOUNDTYPE_IORI_HyakushikiOniyaki);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Ura306shikiShika_3, SOUNDTYPE_IORI_HyakushikiOniyaki);*/

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
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_KOKnockBackUp, {PS_Hit});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_KOKnockBackDown, {PS_Hit});
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_KOKnockBackLand, {PS_Hit});
  //pStateComponent_->RegistState(PLAYER_ANIMTYPE_UltimateCasting, {PS_SkillCasting});

  //pStateComponent_->RegistState(IORI_ANIMTYPE_108ShikiYamiBarai, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_1, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_2, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_Shinigami, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_HyakushikiOniyaki, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_1, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_2, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_3, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_1, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_2, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_3, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_4, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_5, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_6, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_7, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_8, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_9, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_Ura306shikiShika_1, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_Ura306shikiShika_2, {PS_Attack});
  //pStateComponent_->RegistState(IORI_ANIMTYPE_Ura306shikiShika_3, {PS_Attack});

  // RESTRICTION
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_StartPos, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Idle, {});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_SeatDown, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Seat, {});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_SeatUp, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_FrontWalk, {});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_BackWalk, {});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_BackStep, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Run, {});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_RunEnd, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_JumpUp, {PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_JumpDown, {PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_JumpLand, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Dash, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_RollingBack, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Guard, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_GuardEnd, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Guard_Seat, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_GuardEnd_Seat, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyKick_CloseRange, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightKick_CloseRange, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightPunch_CloseRange, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyKick_LongRange, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightKick_LongRange, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyPunch_LongRange, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightPunch_LongRange, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyKick_Seat, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightKick_Seat, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyPunch_Seat, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightPunch_Seat, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyKick_Jump, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightKick_Jump, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_HeavyPunch_Jump, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_LightPunch_Jump, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_High, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_Low, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_Strong, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_AirborneUp, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_AirborneDown, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_AirborneLand, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_AirborneGetUp, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_Seat, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_JumpUp, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_Hit_JumpDown, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_NeckGrabbed, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_KOKnockBackUp, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_KOKnockBackDown, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_KOKnockBackLand, {PR_LockInput, PR_LockExecuteCommand});
  //pRestrictionComponent_->RegistAnimStateRestrict(PLAYER_ANIMTYPE_UltimateCasting, {PR_LockInput, PR_LockExecuteCommand});

  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_108ShikiYamiBarai, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_GaishikiMutan_1, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_GaishikiMutan_2, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_Shinigami, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_HyakushikiOniyaki, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_127ShikiAoiHana_1, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_127ShikiAoiHana_2, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_127ShikiAoiHana_3, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_1, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_2, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_3, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_4, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_5, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_6, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_7, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_8, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_9, {PR_LockInput});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_Ura306shikiShika_1, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_Ura306shikiShika_2, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_Ura306shikiShika_3, {PR_LockInput, PR_LockExecuteCommand});

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
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_9, ATTYPE_StrongAttack, ELMTTYPE_BlueFlame, EFTYPE_Iori_Explosion, false, 5.0f, {3.0f, -4.5f}, 150);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_1, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_2, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, true, 5.0f, {0.0f, -7.0f}, 100);

  // COMMAND
  CommandAction CM0_Action0;
  CM0_Action0.action_ = COMMAND_ACTION_ExecuteSkill;
  CM0_Action0.params_.ExecuteSkill.skillTag_ = SKILL_1;
  Command command0;
  command0.commandTag_ = 0;
  command0.actions_.push_back(CM0_Action0);
  pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_A}, command0);
  pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_B}, command0);

  CommandAction CM1_Action0;
  CM1_Action0.action_ = COMMAND_ACTION_UpdateAnimState;
  CM1_Action0.params_.UpdateAnimState.animStateTag_ = PLAYER_ANIMTYPE_BackStep;
  CommandAction CM1_Action1;
  CM1_Action1.action_ = COMMAND_ACTION_MovementBackStep;
  Command command1;
  command1.commandTag_ = 1;
  command1.actions_.push_back(CM1_Action0);
  command1.actions_.push_back(CM1_Action1);
  pCommandComponent_->RegistCommand({CK_Left, CK_Left}, command1);

  CommandAction CM2_Action0;
  CM2_Action0.action_ = COMMAND_ACTION_UpdateAnimState;
  CM2_Action0.params_.UpdateAnimState.animStateTag_ = PLAYER_ANIMTYPE_Run;
  Command command2;
  command2.commandTag_ = 2;
  command2.actions_.push_back(CM2_Action0);
  pCommandComponent_->RegistCommand({CK_Right, CK_Right}, command2);

  CommandAction CM3_Action0;
  CM3_Action0.action_ = COMMAND_ACTION_ExecuteSkill;
  CM3_Action0.params_.ExecuteSkill.skillTag_ = SKILL_2;
  Command command3;
  command3.commandTag_ = 3;
  command3.actions_.push_back(CM3_Action0);
  pCommandComponent_->RegistCommand({CK_Right, CK_Down, CK_Right, CK_A}, command3);
  pCommandComponent_->RegistCommand({CK_Right, CK_Down, CK_Right, CK_C}, command3);

  CommandAction CM4_Action0;
  CM4_Action0.action_ = COMMAND_ACTION_ExecuteSkill;
  CM4_Action0.params_.ExecuteSkill.skillTag_ = SKILL_3;
  Command command4;
  command4.commandTag_ = 4;
  command4.actions_.push_back(CM4_Action0);
  pCommandComponent_->RegistCommand({CK_Down, CK_Left, CK_A}, command4);
  pCommandComponent_->RegistCommand({CK_Down, CK_Left, CK_C}, command4);

  CommandAction CM5_Action0;
  CM5_Action0.action_ = COMMAND_ACTION_ExecuteSkill;
  CM5_Action0.params_.ExecuteSkill.skillTag_ = SKILL_5;
  Command command5;
  command5.commandTag_ = 5;
  command5.actions_.push_back(CM5_Action0);
  pCommandComponent_->RegistCommand({CK_Down, CK_Right, CK_Down, CK_Left, CK_A}, command5);
  pCommandComponent_->RegistCommand({CK_Down, CK_Right, CK_Down, CK_Left, CK_C}, command5);

  CommandAction CM6_Action0;
  CM6_Action0.action_ = COMMAND_ACTION_TurnOnMisc;
  CM6_Action0.params_.TurnOnMisc.miscOnDuration_ = 500;
  Command command6;
  command6.commandTag_ = 6;
  command6.actions_.push_back(CM6_Action0);
  pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_Left, CK_Down, CK_Right, CK_A}, command6);
  pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_Left, CK_Down, CK_Right, CK_C}, command6);

  // SKILL
  // SKILL 0
  SkillFrameActionData SK0_ST0_FR0_AC0_Data0;
  SkillFrameActionConditionData SK0_ST0_FR0_AC0_Cond0;
  SkillFrameAction SK0_ST0_FR0_Action0;
  SkillFrameActionData SK0_ST0_FR0_AC1_Data;
  SkillFrameActionConditionData SK0_ST0_FR0_AC1_Cond0;
  SkillFrameAction SK0_ST0_FR0_Action1;
  SkillFrame SK0_ST0_Frame0;
  SkillFrameActionData SK0_ST0_FR1_AC0_Data0;
  SkillFrameActionConditionData SK0_ST0_FR1_AC0_Cond0;
  SkillFrameActionConditionData SK0_ST0_FR1_AC0_Cond1;
  SkillFrameAction SK0_ST0_FR1_Action0;
  SkillFrame SK0_ST0_Frame1;
  SkillState SK0_State0;
  SkillState SK0_State1;
  Skill Skill_0;

  // SKILL 1
  SkillFrameActionData SK1_ST0_FR0_AC0_Data0;
  SkillFrameActionConditionData SK1_ST0_FR0_AC0_Cond0;
  SkillFrameAction SK1_ST0_FR0_Action0;
  SkillFrame SK1_ST0_Frame0;
  SkillFrameActionData SK1_ST0_FR1_AC0_Data0;
  SkillFrameActionConditionData SK1_ST0_FR1_AC0_Cond0;
  SkillFrameAction SK1_ST0_FR1_Action0;
  SkillFrame SK1_ST0_Frame1;
  SkillState SK1_State0;
  Skill skill_1;

  // SKILL 2
  SkillFrameActionData SK2_ST0_FR0_AC0_Data0;
  SkillFrameActionConditionData SK2_ST0_FR0_AC0_Cond0;
  SkillFrameAction SK2_ST0_FR0_Action0;
  SkillFrame SK2_ST0_Frame0;
  SkillFrameActionData SK2_ST0_FR1_AC0_Data0;
  SkillFrameActionConditionData SK2_ST0_FR1_AC0_Cond0;
  SkillFrameAction SK2_ST0_FR1_Action0;
  SkillFrameActionData SK2_ST0_FR1_AC1_Data0;
  SkillFrameActionConditionData SK2_ST0_FR1_AC1_Cond0;
  SkillFrameAction SK2_ST0_FR1_Action1;
  SkillFrame SK2_ST0_Frame1;
  SkillFrameActionData SK2_ST0_FR2_AC0_Data0;
  SkillFrameActionConditionData SK2_ST0_FR2_AC0_Cond0;
  SkillFrameAction SK2_ST0_FR2_Action0;
  SkillFrame SK2_ST0_Frame2;
  SkillState SK2_State0;
  Skill Skill_2;

  // SKILL 3
  SkillFrameActionData SK3_ST0_FR0_AC0_Data0;
  SkillFrameActionConditionData SK3_ST0_FR0_AC0_Cond0;
  SkillFrameAction SK3_ST0_FR0_Action0;
  SkillFrame SK3_ST0_Frame0;
  SkillFrameActionData SK3_ST0_FR1_AC0_Data0;
  SkillFrameActionConditionData SK3_ST0_FR1_AC0_Cond0;
  SkillFrameAction SK3_ST0_FR1_Action0;
  SkillFrameActionData SK3_ST0_FR1_AC1_Data0;
  SkillFrameActionConditionData SK3_ST0_FR1_AC1_Cond0;
  SkillFrameAction SK3_ST0_FR1_Action1;
  SkillFrame SK3_ST0_Frame1;
  SkillFrameActionData SK3_ST0_FR2_AC0_Data0;
  SkillFrameActionConditionData SK3_ST0_FR2_AC0_Cond0;
  SkillFrameActionConditionData SK3_ST0_FR2_AC0_Cond1;
  SkillFrameAction SK3_ST0_FR2_Action0;
  SkillFrame SK3_ST0_Frame2;
  SkillState SK3_State0;
  SkillFrameActionData SK3_ST1_FR0_AC0_Data0;
  SkillFrameActionConditionData SK3_ST1_FR0_AC0_Cond0;
  SkillFrameAction SK3_ST1_FR0_Action0;
  SkillFrame SK3_ST1_Frame0;
  SkillFrameActionData SK3_ST1_FR1_AC0_Data0;
  SkillFrameActionConditionData SK3_ST1_FR1_AC0_Cond0;
  SkillFrameAction SK3_ST1_FR1_Action0;
  SkillFrameActionData SK3_ST1_FR1_AC1_Data0;
  SkillFrameActionConditionData SK3_ST1_FR1_AC1_Cond0;
  SkillFrameAction SK3_ST1_FR1_Action1;
  SkillFrame SK3_ST1_Frame1;
  SkillFrameActionData SK3_ST1_FR2_AC0_Data0;
  SkillFrameActionConditionData SK3_ST1_FR2_AC0_Cond0;
  SkillFrameActionConditionData SK3_ST1_FR2_AC0_Cond1;
  SkillFrameAction SK3_ST1_FR2_Action0;
  SkillFrame SK3_ST1_Frame2;
  SkillState SK3_State1;
  SkillFrameActionData SK3_ST2_FR0_AC0_Data0;
  SkillFrameActionConditionData SK3_ST2_FR0_AC0_Cond0;
  SkillFrameAction SK3_ST2_FR0_Action0;
  SkillFrame SK3_ST2_Frame0;
  SkillState SK3_State2;
  Skill Skill_3;

  // SKILL 4
  SkillFrameActionData SK4_ST0_FR0_AC0_Data0;
  SkillFrameActionConditionData SK4_ST0_FR0_AC0_Cond0;
  SkillFrameAction SK4_ST0_FR0_Action0;
  SkillFrame SK4_ST0_Frame0;
  SkillState SK4_State0;
  Skill skill_4;

  // SKILL 5
  SkillFrameActionData SK5_ST0_FR0_AC0_Data0;
  SkillFrameActionConditionData SK5_ST0_FR0_AC0_Cond0;
  SkillFrameAction SK5_ST0_FR0_Action0;
  SkillFrameActionData SK5_ST0_FR0_AC1_Data0;
  SkillFrameActionConditionData SK5_ST0_FR0_AC1_Cond0;
  SkillFrameAction SK5_ST0_FR0_Action1;
  SkillFrameActionData SK5_ST0_FR0_AC2_Data0;

  SkillFrameActionConditionData SK5_ST0_FR0_AC2_Cond0;
  SkillFrameAction SK5_ST0_FR0_Action2;
  SkillFrameActionData SK5_ST0_FR0_AC3_Data0;
  SkillFrameActionConditionData SK5_ST0_FR0_AC3_Cond0;
  SkillFrameAction SK5_ST0_FR0_Action3;
  SkillFrame SK5_ST0_Frame0;
  SkillFrameActionData SK5_ST0_FR1_AC0_Data0;
  SkillFrameActionConditionData SK5_ST0_FR1_AC0_Cond0;
  SkillFrameAction SK5_ST0_FR1_Action0;
  SkillFrame SK5_ST0_Frame1;
  SkillState SK5_State0;
  SkillFrameActionConditionData SK5_ST1_FR0_AC0_Cond0;
  SkillFrameActionData SK5_ST1_FR0_AC0_Data0;
  SkillFrameActionData SK5_ST1_FR0_AC0_Data1;
  SkillFrameAction SK5_ST1_FR0_Action0;
  SkillFrame SK5_ST1_Frame0;
  SkillFrameActionData SK5_ST1_FR1_AC0_Data0;
  SkillFrameActionConditionData SK5_ST1_FR1_AC0_Cond0;
  SkillFrameAction SK5_ST1_FR1_Action0;
  SkillFrame SK5_ST1_Frame1;
  SkillFrameActionConditionData SK5_ST1_FR2_AC0_Cond0;
  SkillFrameActionData SK5_ST1_FR2_AC0_Data0;
  SkillFrameActionData SK5_ST1_FR2_AC0_Data1;
  SkillFrameAction SK5_ST1_FR2_Action0;
  SkillFrameActionConditionData SK5_ST1_FR2_AC1_Cond0;
  SkillFrameActionConditionData SK5_ST1_FR2_AC1_Cond1;
  SkillFrameActionData SK5_ST1_FR2_AC1_Data0;
  SkillFrameActionData SK5_ST1_FR2_AC1_Data1;
  SkillFrameAction SK5_ST1_FR2_Action1;
  SkillFrame SK5_ST1_Frame2;
  SkillState SK5_State1;

  SkillFrameActionData SK5_ST2_FR0_AC0_Data0;
  SkillFrameActionConditionData SK5_ST2_FR0_AC0_Cond0;
  SkillFrameAction SK5_ST2_FR0_Action0;
  SkillFrame SK5_ST2_Frame0;
  SkillFrameActionData SK5_ST2_FR1_AC0_Data0;
  SkillFrameActionConditionData SK5_ST2_FR1_AC0_Cond0;
  SkillFrameAction SK5_ST2_FR1_Action0;
  SkillFrame SK5_ST2_Frame1;
  SkillState SK5_State2;
  SkillFrameActionData SK5_ST3_FR0_AC0_Data0;
  SkillFrameActionConditionData SK5_ST3_FR0_AC0_Cond0;
  SkillFrameAction SK5_ST3_FR0_Action0;
  SkillFrame SK5_ST3_Frame0;
  SkillFrameActionData SK5_ST3_FR1_AC0_Data0;
  SkillFrameActionConditionData SK5_ST3_FR1_AC0_Cond0;
  SkillFrameAction SK5_ST3_FR1_Action0;
  SkillFrame SK5_ST3_Frame1;
  SkillState SK5_State3;

  SkillFrameActionData SK5_ST4_FR0_AC0_Data0;
  SkillFrameActionConditionData SK5_ST4_FR0_AC0_Cond0;
  SkillFrameAction SK5_ST4_FR0_Action0;
  SkillFrame SK5_ST4_Frame0;
  SkillFrameActionData SK5_ST4_FR1_AC0_Data0;
  SkillFrameActionConditionData SK5_ST4_FR1_AC0_Cond0;
  SkillFrameAction SK5_ST4_FR1_Action0;
  SkillFrame SK5_ST4_Frame1;
  SkillState SK5_State4;

  SkillFrameActionData SK5_ST5_FR0_AC0_Data0;
  SkillFrameActionConditionData SK5_ST5_FR0_AC0_Cond0;
  SkillFrameAction SK5_ST5_FR0_Action0;
  SkillFrame SK5_ST5_Frame0;
  SkillFrameActionData SK5_ST5_FR1_AC0_Data0;
  SkillFrameActionConditionData SK5_ST5_FR1_AC0_Cond0;
  SkillFrameAction SK5_ST5_FR1_Action0;
  SkillFrame SK5_ST5_Frame1;
  SkillState SK5_State5;

  SkillFrameActionData SK5_ST6_FR0_AC0_Data0;
  SkillFrameActionConditionData SK5_ST6_FR0_AC0_Cond0;
  SkillFrameAction SK5_ST6_FR0_Action0;
  SkillFrame SK5_ST6_Frame0;
  SkillFrameActionData SK5_ST6_FR1_AC0_Data0;
  SkillFrameActionConditionData SK5_ST6_FR1_AC0_Cond0;
  SkillFrameAction SK5_ST6_FR1_Action0;
  SkillFrame SK5_ST6_Frame1;
  SkillState SK5_State6;

  SkillFrameActionData SK5_ST7_FR0_AC0_Data0;
  SkillFrameActionConditionData SK5_ST7_FR0_AC0_Cond0;
  SkillFrameAction SK5_ST7_FR0_Action0;
  SkillFrame SK5_ST7_Frame0;
  SkillFrameActionData SK5_ST7_FR1_AC0_Data0;
  SkillFrameActionConditionData SK5_ST7_FR1_AC0_Cond0;
  SkillFrameAction SK5_ST7_FR1_Action0;
  SkillFrame SK5_ST7_Frame1;
  SkillState SK5_State7;
  SkillFrameActionConditionData SK5_ST8_FR0_AC0_Cond0;
  SkillFrameActionData SK5_ST8_FR0_AC0_Data0;
  SkillFrameActionData SK5_ST8_FR0_AC0_Data1;
  SkillFrameAction SK5_ST8_FR0_Action0;
  SkillFrame SK5_ST8_Frame0;
  SkillFrameActionData SK5_ST8_FR1_AC0_Data0;
  SkillFrameActionConditionData SK5_ST8_FR1_AC0_Cond0;
  SkillFrameAction SK5_ST8_FR1_Action0;
  SkillFrame SK5_ST8_Frame1;
  SkillState SK5_State8;
  SkillFrameActionData SK5_ST9_FR0_AC0_Data0;
  SkillFrameActionConditionData SK5_ST9_FR0_AC0_Cond0;
  SkillFrameAction SK5_ST9_FR0_Action0;
  SkillFrame SK5_ST9_Frame0;
  SkillFrameActionConditionData SK5_ST9_FR1_AC0_Cond0;
  SkillFrameActionData SK5_ST9_FR1_AC0_Data0;
  SkillFrameActionData SK5_ST9_FR1_AC0_Data1;
  SkillFrameActionData SK5_ST9_FR1_AC0_Data2;
  SkillFrameAction SK5_ST9_FR1_Action0;
  SkillFrame SK5_ST9_Frame1;

  SkillFrameActionConditionData SK5_ST9_FR2_AC0_Cond0;
  SkillFrameActionData SK5_ST9_FR2_AC0_Data0;
  SkillFrameActionData SK5_ST9_FR2_AC0_Data1;
  SkillFrameAction SK5_ST9_FR2_Action0;
  SkillFrameActionConditionData SK5_ST9_FR2_AC1_Cond0;
  SkillFrameActionConditionData SK5_ST9_FR2_AC1_Cond1;
  SkillFrameActionData SK5_ST9_FR2_AC1_Data0;
  SkillFrameActionData SK5_ST9_FR2_AC1_Data1;
  SkillFrameAction SK5_ST9_FR2_Action1;
  SkillFrame SK5_ST9_Frame2;
  SkillFrameActionConditionData SK5_ST9_FR3_AC0_Cond0;
  SkillFrameActionData SK5_ST9_FR3_AC0_Data0;
  SkillFrameAction SK5_ST9_FR3_Action0;
  SkillFrame SK5_ST9_Frame3;
  SkillState SK5_State9;
  Skill Skill_5;

  SkillFrameActionConditionData SK6_ST0_FR0_AC0_Cond0;
  SkillFrameActionData SK6_ST0_FR0_AC0_Data0;
  SkillFrameActionData SK6_ST0_FR0_AC0_Data1;
  SkillFrameActionData SK6_ST0_FR0_AC0_Data2;
  SkillFrameActionData SK6_ST0_FR0_AC0_Data3;
  SkillFrameAction SK6_ST0_FR0_Action0;
  SkillFrame SK6_ST0_Frame0;
  SkillFrameActionConditionData SK6_ST0_FR1_AC0_Cond0;
  SkillFrameActionData SK6_ST0_FR1_AC0_Data0;
  SkillFrameAction SK6_ST0_FR1_Action0;
  SkillFrame SK6_ST0_Frame1;
  SkillFrameActionConditionData SK6_ST0_FR2_AC0_Cond0;
  SkillFrameActionData SK6_ST0_FR2_AC0_Data0;
  SkillFrameAction SK6_ST0_FR2_Action0;
  SkillFrame SK6_ST0_Frame2;
  SkillFrameActionConditionData SK6_ST0_FR3_AC0_Cond0;
  SkillFrameActionData SK6_ST0_FR3_AC0_Data0;
  SkillFrameAction SK6_ST0_FR3_Action0;
  SkillFrame SK6_ST0_Frame3;
  SkillState SK6_State0;
  SkillFrameActionConditionData SK6_ST1_FR0_AC0_Cond0;
  SkillFrameActionData SK6_ST1_FR0_AC0_Data0;
  SkillFrameAction SK6_ST1_FR0_Action0;
  SkillFrame SK6_ST1_Frame0;
  SkillFrameActionConditionData SK6_ST1_FR1_AC0_Cond0;
  SkillFrameActionData SK6_ST1_FR1_AC0_Data0;
  SkillFrameAction SK6_ST1_FR1_Action0;
  SkillFrame SK6_ST1_Frame1;
  SkillState SK6_State1;
  SkillFrameActionConditionData SK6_ST2_FR0_AC0_Cond0;
  SkillFrameActionData SK6_ST2_FR0_AC0_Data0;
  SkillFrameActionData SK6_ST2_FR0_AC0_Data1;
  SkillFrameActionData SK6_ST2_FR0_AC0_Data2;
  SkillFrameAction SK6_ST2_FR0_Action0;
  SkillFrame SK6_ST2_Frame0;
  SkillFrameActionConditionData SK6_ST2_FR1_AC0_Cond0;
  SkillFrameActionData SK6_ST2_FR1_AC0_Data0;
  SkillFrameAction SK6_ST2_FR1_Action0;
  SkillFrame SK6_ST2_Frame1;
  SkillState SK6_State2;
  Skill Skill_6;
}

void Chang::CompareInputBitset() {
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
