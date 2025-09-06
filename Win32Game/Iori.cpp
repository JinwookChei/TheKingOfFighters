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
#include "AnimStateTransMachine.h"
#include "InputController.h"
#include "Iori.h"

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
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_JumpUp, IMGTYPE_IoriImage, {594, 595}, 80, false, 595);
  CallCreateAnimation(PLAYER_ANIMTYPE_Hit_JumpDown, IMGTYPE_IoriImage, 80, 85, ANIMINTERVAL, false, 82);
  CallCreateAnimation(PLAYER_ANIMTYPE_NeckGrabbed, IMGTYPE_IoriImage, 572, 575, 150, false, 572);
  CallCreateAnimation(PLAYER_ANIMTYPE_KOKnockBackUp, IMGTYPE_IoriImage, 594, 597, ANIMINTERVAL, false, 594);
  CallCreateAnimation(PLAYER_ANIMTYPE_KOKnockBackDown, IMGTYPE_IoriImage, 608, 610, ANIMINTERVAL, false, 608);
  CallCreateAnimation(PLAYER_ANIMTYPE_KOKnockBackLand, IMGTYPE_IoriImage, {611}, ANIMINTERVAL, true, 611);
  CallCreateAnimation(IORI_ANIMTYPE_108ShikiYamiBarai, IMGTYPE_IoriImage, 223, 230, ANIMINTERVAL, false, 223);
  CallCreateAnimation(IORI_ANIMTYPE_GaishikiMutan_1, IMGTYPE_IoriImage, 99, 107, ANIMINTERVAL, false, 99);
  CallCreateAnimation(IORI_ANIMTYPE_GaishikiMutan_2, IMGTYPE_IoriImage, 160, 164, ANIMINTERVAL, false, 160);
  CallCreateAnimation(IORI_ANIMTYPE_Shinigami, IMGTYPE_IoriImage, 145, 156, ANIMINTERVAL, false, 145);
  CallCreateAnimation(IORI_ANIMTYPE_HyakushikiOniyaki, IMGTYPE_IoriImage, 276, 291, ANIMINTERVAL, false, 276);
  CallCreateAnimation(IORI_ANIMTYPE_127ShikiAoiHana_1, IMGTYPE_IoriImage, 255, 261, ANIMINTERVAL, false, 255);
  CallCreateAnimation(IORI_ANIMTYPE_127ShikiAoiHana_2, IMGTYPE_IoriImage, 262, 268, ANIMINTERVAL, false, 262);
  CallCreateAnimation(IORI_ANIMTYPE_127ShikiAoiHana_3, IMGTYPE_IoriImage, 269, 275, ANIMINTERVAL, false, 269);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_0, IMGTYPE_IoriImage, 344, 347, 70, false, 344);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_1, IMGTYPE_IoriImage, 70, 77, 32, false, 70);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_2, IMGTYPE_IoriImage, 118, 122, 16, false, 118);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_3, IMGTYPE_IoriImage, 88, 92, 16, false, 88);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_4, IMGTYPE_IoriImage, 128, 135, 16, false, 128);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_5, IMGTYPE_IoriImage, 223, 229, 16, false, 223);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_6, IMGTYPE_IoriImage, 99, 107, 16, false, 99);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_7, IMGTYPE_IoriImage, 159, 163, 16, false, 159);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_8, IMGTYPE_IoriImage, 99, 107, 16, false, 99);
  CallCreateAnimation(IORI_ANIMTYPE_1211ShikiYaOtome_9, IMGTYPE_IoriImage, 347, 352, 140, false, 347);
  CallCreateAnimation(IORI_ANIMTYPE_Ura306shikiShika_1, IMGTYPE_IoriImage, 353, 360, 70, false, 353);
  CallCreateAnimation(IORI_ANIMTYPE_Ura306shikiShika_2, IMGTYPE_IoriImage, 361, 370, 30, false, 161);
  CallCreateAnimation(IORI_ANIMTYPE_Ura306shikiShika_3, IMGTYPE_IoriImage, 371, 386, 20, false, 371);

  // ANIM
  AnimTransRule animTransRule_JumpUp;
  animTransRule_JumpUp.transCondition_ = ANIM_TRANS_COND::MovementFalling;
  animTransRule_JumpUp.toAnimState_ = PLAYER_ANIMTYPE_JumpDown;
  AnimTransState animState_JumpUp;
  animState_JumpUp.fromAnimState_ = PLAYER_ANIMTYPE_JumpUp;
  animState_JumpUp.animTransRules_.push_back(animTransRule_JumpUp);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_JumpUp);

  AnimTransRule animTransRule_JumpDown;
  animTransRule_JumpDown.transCondition_ = ANIM_TRANS_COND::MovementOnGround;
  animTransRule_JumpDown.toAnimState_ = PLAYER_ANIMTYPE_JumpLand;
  AnimTransState animState_JumpDown;
  animState_JumpDown.fromAnimState_ = PLAYER_ANIMTYPE_JumpDown;
  animState_JumpDown.animTransRules_.push_back(animTransRule_JumpDown);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_JumpDown);

  AnimTransRule animTransRule_JumpLand;
  animTransRule_JumpLand.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_JumpLand.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_JumpLand;
  animState_JumpLand.fromAnimState_ = PLAYER_ANIMTYPE_JumpLand;
  animState_JumpLand.animTransRules_.push_back(animTransRule_JumpLand);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_JumpLand);

  AnimTransRule animTransRule_HeavyKick_Jump0;
  animTransRule_HeavyKick_Jump0.transCondition_ = ANIM_TRANS_COND::AnimationEnd | ANIM_TRANS_COND::MovementFalling;
  animTransRule_HeavyKick_Jump0.toAnimState_ = PLAYER_ANIMTYPE_JumpDown;
  AnimTransRule animTransRule_HeavyKick_Jump1;
  animTransRule_HeavyKick_Jump1.transCondition_ = ANIM_TRANS_COND::MovementOnGround;
  animTransRule_HeavyKick_Jump1.toAnimState_ = PLAYER_ANIMTYPE_JumpLand;
  AnimTransState animState_HeavyKick_Jump;
  animState_HeavyKick_Jump.fromAnimState_ = PLAYER_ANIMTYPE_HeavyKick_Jump;
  animState_HeavyKick_Jump.animTransRules_.push_back(animTransRule_HeavyKick_Jump0);
  animState_HeavyKick_Jump.animTransRules_.push_back(animTransRule_HeavyKick_Jump1);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_HeavyKick_Jump);

  AnimTransRule animTransRule_HeavyPunch_Jump0;
  animTransRule_HeavyPunch_Jump0.transCondition_ = ANIM_TRANS_COND::AnimationEnd | MovementFalling;
  animTransRule_HeavyPunch_Jump0.toAnimState_ = PLAYER_ANIMTYPE_JumpDown;
  AnimTransRule animTransRule_HeavyPunch_Jump1;
  animTransRule_HeavyPunch_Jump1.transCondition_ = ANIM_TRANS_COND::MovementOnGround;
  animTransRule_HeavyPunch_Jump1.toAnimState_ = PLAYER_ANIMTYPE_JumpLand;
  AnimTransState animState_HeavyPunch_Jump;
  animState_HeavyPunch_Jump.fromAnimState_ = PLAYER_ANIMTYPE_HeavyPunch_Jump;
  animState_HeavyPunch_Jump.animTransRules_.push_back(animTransRule_HeavyPunch_Jump0);
  animState_HeavyPunch_Jump.animTransRules_.push_back(animTransRule_HeavyPunch_Jump1);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_HeavyPunch_Jump);

  AnimTransRule animTransRule_LightKick_Jump0;
  animTransRule_LightKick_Jump0.transCondition_ = ANIM_TRANS_COND::AnimationEnd | ANIM_TRANS_COND::MovementFalling;
  animTransRule_LightKick_Jump0.toAnimState_ = PLAYER_ANIMTYPE_JumpDown;
  AnimTransRule animTransRule_LightKick_Jump1;
  animTransRule_LightKick_Jump1.transCondition_ = ANIM_TRANS_COND::MovementOnGround;
  animTransRule_LightKick_Jump1.toAnimState_ = PLAYER_ANIMTYPE_JumpLand;
  AnimTransState animState_LightKick_Jump;
  animState_LightKick_Jump.fromAnimState_ = PLAYER_ANIMTYPE_LightKick_Jump;
  animState_LightKick_Jump.animTransRules_.push_back(animTransRule_LightKick_Jump0);
  animState_LightKick_Jump.animTransRules_.push_back(animTransRule_LightKick_Jump1);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_LightKick_Jump);

  AnimTransRule animTransRule_LightPunch_Jump0;
  animTransRule_LightPunch_Jump0.transCondition_ = ANIM_TRANS_COND::AnimationEnd | ANIM_TRANS_COND::MovementFalling;
  animTransRule_LightPunch_Jump0.toAnimState_ = PLAYER_ANIMTYPE_JumpDown;
  AnimTransRule animTransRule_LightPunch_Jump1;
  animTransRule_LightPunch_Jump1.transCondition_ = ANIM_TRANS_COND::MovementOnGround;
  animTransRule_LightPunch_Jump1.toAnimState_ = PLAYER_ANIMTYPE_JumpLand;
  AnimTransState animState_LightPunch_Jump;
  animState_LightPunch_Jump.fromAnimState_ = PLAYER_ANIMTYPE_LightPunch_Jump;
  animState_LightPunch_Jump.animTransRules_.push_back(animTransRule_LightPunch_Jump0);
  animState_LightPunch_Jump.animTransRules_.push_back(animTransRule_LightPunch_Jump1);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_LightPunch_Jump);

  AnimTransRule animTransRule_SeatDown;
  animTransRule_SeatDown.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_SeatDown.toAnimState_ = PLAYER_ANIMTYPE_Seat;
  AnimTransState animState_SeatDown;
  animState_SeatDown.fromAnimState_ = PLAYER_ANIMTYPE_SeatDown;
  animState_SeatDown.animTransRules_.push_back(animTransRule_SeatDown);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_SeatDown);

  AnimTransRule animTransRule_HeavyKick_Seat;
  animTransRule_HeavyKick_Seat.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_HeavyKick_Seat.toAnimState_ = PLAYER_ANIMTYPE_Seat;
  AnimTransState animState_HeavyKick_Seat;
  animState_HeavyKick_Seat.fromAnimState_ = PLAYER_ANIMTYPE_HeavyKick_Seat;
  animState_HeavyKick_Seat.animTransRules_.push_back(animTransRule_HeavyKick_Seat);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_HeavyKick_Seat);

  AnimTransRule animTransRule_LightKick_Seat;
  animTransRule_LightKick_Seat.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_LightKick_Seat.toAnimState_ = PLAYER_ANIMTYPE_Seat;
  AnimTransState animState_LightKick_Seat;
  animState_LightKick_Seat.fromAnimState_ = PLAYER_ANIMTYPE_LightKick_Seat;
  animState_LightKick_Seat.animTransRules_.push_back(animTransRule_LightKick_Seat);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_LightKick_Seat);

  AnimTransRule animTransRule_HeavyPunch_Seat;
  animTransRule_HeavyPunch_Seat.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_HeavyPunch_Seat.toAnimState_ = PLAYER_ANIMTYPE_Seat;
  AnimTransState animState_HeavyPunch_Seat;
  animState_HeavyPunch_Seat.fromAnimState_ = PLAYER_ANIMTYPE_HeavyPunch_Seat;
  animState_HeavyPunch_Seat.animTransRules_.push_back(animTransRule_HeavyPunch_Seat);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_HeavyPunch_Seat);

  AnimTransRule animTransRule_LightPunch_Seat;
  animTransRule_LightPunch_Seat.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_LightPunch_Seat.toAnimState_ = PLAYER_ANIMTYPE_Seat;
  AnimTransState animState_LightPunch_Seat;
  animState_LightPunch_Seat.fromAnimState_ = PLAYER_ANIMTYPE_LightPunch_Seat;
  animState_LightPunch_Seat.animTransRules_.push_back(animTransRule_LightPunch_Seat);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_LightPunch_Seat);

  AnimTransRule animTransRule_SeatUp;
  animTransRule_SeatUp.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_SeatUp.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_SeatUp;
  animState_SeatUp.fromAnimState_ = PLAYER_ANIMTYPE_SeatUp;
  animState_SeatUp.animTransRules_.push_back(animTransRule_SeatUp);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_SeatUp);

  AnimTransRule animTransRule_BackStep;
  animTransRule_BackStep.transCondition_ = ANIM_TRANS_COND::AnimationEnd | ANIM_TRANS_COND::MovementOnGround;
  animTransRule_BackStep.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_BackStep;
  animState_BackStep.fromAnimState_ = PLAYER_ANIMTYPE_BackStep;
  animState_BackStep.animTransRules_.push_back(animTransRule_BackStep);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_BackStep);
  
  AnimTransRule animTransRule_RunEnd;
  animTransRule_RunEnd.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_RunEnd.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_RunEnd;
  animState_RunEnd.fromAnimState_ = PLAYER_ANIMTYPE_RunEnd;
  animState_RunEnd.animTransRules_.push_back(animTransRule_RunEnd);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_RunEnd);
  
  AnimTransRule animTransRule_Dash;
  animTransRule_Dash.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_Dash.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_Dash;
  animState_Dash.fromAnimState_ = PLAYER_ANIMTYPE_Dash;
  animState_Dash.animTransRules_.push_back(animTransRule_Dash);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_Dash);
  
  AnimTransRule animTransRule_RollingBack;
  animTransRule_RollingBack.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_RollingBack.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_RollingBack;
  animState_RollingBack.fromAnimState_ = PLAYER_ANIMTYPE_RollingBack;
  animState_RollingBack.animTransRules_.push_back(animTransRule_RollingBack);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_RollingBack);
  
  AnimTransRule animTransRule_Guard;
  animTransRule_Guard.transCondition_ = ANIM_TRANS_COND::OpponentPlayerAttackFinished;
  animTransRule_Guard.toAnimState_ = PLAYER_ANIMTYPE_GuardEnd;
  AnimTransState animState_Guard;
  animState_Guard.fromAnimState_ = PLAYER_ANIMTYPE_Guard;
  animState_Guard.animTransRules_.push_back(animTransRule_Guard);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_Guard);
  
  AnimTransRule animTransRule_GuardEnd;
  animTransRule_GuardEnd.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_GuardEnd.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_GuardEnd;
  animState_GuardEnd.fromAnimState_ = PLAYER_ANIMTYPE_GuardEnd;
  animState_GuardEnd.animTransRules_.push_back(animTransRule_GuardEnd);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_GuardEnd);

  AnimTransRule animTransRule_Guard_Seat;
  animTransRule_Guard_Seat.transCondition_ = ANIM_TRANS_COND::OpponentPlayerAttackFinished;
  animTransRule_Guard_Seat.toAnimState_ = PLAYER_ANIMTYPE_GuardEnd_Seat;
  AnimTransState animState_Guard_Seat;
  animState_Guard_Seat.fromAnimState_ = PLAYER_ANIMTYPE_Guard_Seat;
  animState_Guard_Seat.animTransRules_.push_back(animTransRule_Guard_Seat);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_Guard_Seat);

  AnimTransRule animTransRule_GuardEnd_Seat;
  animTransRule_GuardEnd_Seat.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_GuardEnd_Seat.toAnimState_ = PLAYER_ANIMTYPE_Seat;
  AnimTransState animState_GuardEnd_Seat;
  animState_GuardEnd_Seat.fromAnimState_ = PLAYER_ANIMTYPE_GuardEnd_Seat;
  animState_GuardEnd_Seat.animTransRules_.push_back(animTransRule_GuardEnd_Seat);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_GuardEnd_Seat);

  AnimTransRule animTransRule_HeavyKick_CloseRange;
  animTransRule_HeavyKick_CloseRange.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_HeavyKick_CloseRange.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_HeavyKick_CloseRange;
  animState_HeavyKick_CloseRange.fromAnimState_ = PLAYER_ANIMTYPE_HeavyKick_CloseRange;
  animState_HeavyKick_CloseRange.animTransRules_.push_back(animTransRule_HeavyKick_CloseRange);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_HeavyKick_CloseRange);
  
  AnimTransRule animTransRule_LightKick_CloseRange;
  animTransRule_LightKick_CloseRange.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_LightKick_CloseRange.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_LightKick_CloseRange;
  animState_LightKick_CloseRange.fromAnimState_ = PLAYER_ANIMTYPE_LightKick_CloseRange;
  animState_LightKick_CloseRange.animTransRules_.push_back(animTransRule_LightKick_CloseRange);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_LightKick_CloseRange);

  AnimTransRule animTransRule_HeavyPunch_CloseRange;
  animTransRule_HeavyPunch_CloseRange.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_HeavyPunch_CloseRange.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_HeavyPunch_CloseRange;
  animState_HeavyPunch_CloseRange.fromAnimState_ = PLAYER_ANIMTYPE_HeavyPunch_CloseRange;
  animState_HeavyPunch_CloseRange.animTransRules_.push_back(animTransRule_HeavyPunch_CloseRange);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_HeavyPunch_CloseRange);
  
  AnimTransRule animTransRule_LightPunch_CloseRange;
  animTransRule_LightPunch_CloseRange.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_LightPunch_CloseRange.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_LightPunch_CloseRange;
  animState_LightPunch_CloseRange.fromAnimState_ = PLAYER_ANIMTYPE_LightPunch_CloseRange;
  animState_LightPunch_CloseRange.animTransRules_.push_back(animTransRule_LightPunch_CloseRange);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_LightPunch_CloseRange);

  AnimTransRule animTransRule_HeavyKick_LongRange;
  animTransRule_HeavyKick_LongRange.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_HeavyKick_LongRange.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_HeavyKick_LongRange;
  animState_HeavyKick_LongRange.fromAnimState_ = PLAYER_ANIMTYPE_HeavyKick_LongRange;
  animState_HeavyKick_LongRange.animTransRules_.push_back(animTransRule_HeavyKick_LongRange);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_HeavyKick_LongRange);
  
  AnimTransRule animTransRule_LightKick_LongRange;
  animTransRule_LightKick_LongRange.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_LightKick_LongRange.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_LightKick_LongRange;
  animState_LightKick_LongRange.fromAnimState_ = PLAYER_ANIMTYPE_LightKick_LongRange;
  animState_LightKick_LongRange.animTransRules_.push_back(animTransRule_LightKick_LongRange);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_LightKick_LongRange);

  AnimTransRule animTransRule_HeavyPunch_LongRange;
  animTransRule_HeavyPunch_LongRange.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_HeavyPunch_LongRange.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_HeavyPunch_LongRange;
  animState_HeavyPunch_LongRange.fromAnimState_ = PLAYER_ANIMTYPE_HeavyPunch_LongRange;
  animState_HeavyPunch_LongRange.animTransRules_.push_back(animTransRule_HeavyPunch_LongRange);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_HeavyPunch_LongRange);
  
  AnimTransRule animTransRule_LightPunch_LongRange;
  animTransRule_LightPunch_LongRange.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_LightPunch_LongRange.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_LightPunch_LongRange;
  animState_LightPunch_LongRange.fromAnimState_ = PLAYER_ANIMTYPE_LightPunch_LongRange;
  animState_LightPunch_LongRange.animTransRules_.push_back(animTransRule_LightPunch_LongRange);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_LightPunch_LongRange);
  
  AnimTransRule animTransRule_Hit_High;
  animTransRule_Hit_High.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_Hit_High.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_Hit_High;
  animState_Hit_High.fromAnimState_ = PLAYER_ANIMTYPE_Hit_High;
  animState_Hit_High.animTransRules_.push_back(animTransRule_Hit_High);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_Hit_High);
  
  AnimTransRule animTransRule_Hit_Low;
  animTransRule_Hit_Low.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_Hit_Low.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_Hit_Low;
  animState_Hit_Low.fromAnimState_ = PLAYER_ANIMTYPE_Hit_Low;
  animState_Hit_Low.animTransRules_.push_back(animTransRule_Hit_Low);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_Hit_Low);
  
  AnimTransRule animTransRule_Hit_Strong;
  animTransRule_Hit_Strong.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_Hit_Strong.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_Hit_Strong;
  animState_Hit_Strong.fromAnimState_ = PLAYER_ANIMTYPE_Hit_Strong;
  animState_Hit_Strong.animTransRules_.push_back(animTransRule_Hit_Strong);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_Hit_Strong);
  
  AnimTransRule animTransRule_Hit_JumpUp0;
  animTransRule_Hit_JumpUp0.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_Hit_JumpUp0.toAnimState_ = PLAYER_ANIMTYPE_Hit_JumpDown;
  AnimTransRule animTransRule_Hit_JumpUp1;
  animTransRule_Hit_JumpUp1.transCondition_ = ANIM_TRANS_COND::MovementOnGround;
  animTransRule_Hit_JumpUp1.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_Hit_JumpUp;
  animState_Hit_JumpUp.fromAnimState_ = PLAYER_ANIMTYPE_Hit_JumpUp;
  animState_Hit_JumpUp.animTransRules_.push_back(animTransRule_Hit_JumpUp0);
  animState_Hit_JumpUp.animTransRules_.push_back(animTransRule_Hit_JumpUp1);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_Hit_JumpUp);
  
  AnimTransRule animTransRule_Hit_JumpDown;
  animTransRule_Hit_JumpDown.transCondition_ = ANIM_TRANS_COND::MovementOnGround;
  animTransRule_Hit_JumpDown.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_Hit_JumpDown;
  animState_Hit_JumpDown.fromAnimState_ = PLAYER_ANIMTYPE_Hit_JumpDown;
  animState_Hit_JumpDown.animTransRules_.push_back(animTransRule_Hit_JumpDown);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_Hit_JumpDown);

  AnimTransRule animTransRule_Hit_AirborneUp;
  animTransRule_Hit_AirborneUp.transCondition_ = ANIM_TRANS_COND::MovementFalling;
  animTransRule_Hit_AirborneUp.toAnimState_ = PLAYER_ANIMTYPE_Hit_AirborneDown;
  AnimTransState animState_Hit_AirborneUp;
  animState_Hit_AirborneUp.fromAnimState_ = PLAYER_ANIMTYPE_Hit_AirborneUp;
  animState_Hit_AirborneUp.animTransRules_.push_back(animTransRule_Hit_AirborneUp);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_Hit_AirborneUp);
  
  AnimTransRule animTransRule_Hit_AirborneDown;
  animTransRule_Hit_AirborneDown.transCondition_ = ANIM_TRANS_COND::MovementOnGround;
  animTransRule_Hit_AirborneDown.toAnimState_ = PLAYER_ANIMTYPE_Hit_AirborneLand;
  AnimTransState animState_Hit_AirborneDown;
  animState_Hit_AirborneDown.fromAnimState_ = PLAYER_ANIMTYPE_Hit_AirborneDown;
  animState_Hit_AirborneDown.animTransRules_.push_back(animTransRule_Hit_AirborneDown);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_Hit_AirborneDown);

  AnimTransRule animTransRule_Hit_AirborneLand;
  animTransRule_Hit_AirborneLand.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_Hit_AirborneLand.toAnimState_ = PLAYER_ANIMTYPE_Hit_AirborneGetUp;
  AnimTransState animState_Hit_AirborneLand;
  animState_Hit_AirborneLand.fromAnimState_ = PLAYER_ANIMTYPE_Hit_AirborneLand;
  animState_Hit_AirborneLand.animTransRules_.push_back(animTransRule_Hit_AirborneLand);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_Hit_AirborneLand);
  
  AnimTransRule animTransRule_Hit_AirborneGetUp;
  animTransRule_Hit_AirborneGetUp.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_Hit_AirborneGetUp.toAnimState_ = PLAYER_ANIMTYPE_Idle;
  AnimTransState animState_Hit_AirborneGetUp;
  animState_Hit_AirborneGetUp.fromAnimState_ = PLAYER_ANIMTYPE_Hit_AirborneGetUp;
  animState_Hit_AirborneGetUp.animTransRules_.push_back(animTransRule_Hit_AirborneGetUp);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_Hit_AirborneGetUp);

  AnimTransRule animTransRule_Hit_Seat;
  animTransRule_Hit_Seat.transCondition_ = ANIM_TRANS_COND::AnimationEnd;
  animTransRule_Hit_Seat.toAnimState_ = PLAYER_ANIMTYPE_Seat;
  AnimTransState animState_Hit_Seat;
  animState_Hit_Seat.fromAnimState_ = PLAYER_ANIMTYPE_Hit_Seat;
  animState_Hit_Seat.animTransRules_.push_back(animTransRule_Hit_Seat);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_Hit_Seat);

  AnimTransRule animTransRule_KOKnockBackUp;
  animTransRule_KOKnockBackUp.transCondition_ = ANIM_TRANS_COND::MovementFalling;
  animTransRule_KOKnockBackUp.toAnimState_ = PLAYER_ANIMTYPE_KOKnockBackDown;
  AnimTransState animState_KOKnockBackUp;
  animState_KOKnockBackUp.fromAnimState_ = PLAYER_ANIMTYPE_KOKnockBackUp;
  animState_KOKnockBackUp.animTransRules_.push_back(animTransRule_KOKnockBackUp);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_KOKnockBackUp);

  AnimTransRule animTransRule_KOKnockBackDown;
  animTransRule_KOKnockBackDown.transCondition_ = ANIM_TRANS_COND::MovementOnGround;
  animTransRule_KOKnockBackDown.toAnimState_ = PLAYER_ANIMTYPE_KOKnockBackLand;
  AnimTransState animState_KOKnockBackDown;
  animState_KOKnockBackDown.fromAnimState_ = PLAYER_ANIMTYPE_KOKnockBackDown;
  animState_KOKnockBackDown.animTransRules_.push_back(animTransRule_KOKnockBackDown);
  pAnimaStateTransMachine_->RegistAnimTransition(animState_KOKnockBackDown);

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
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_1211ShikiYaOtome_0, SOUNDTYPE_IORI_1211ShikiYaOtome01);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_GaishikiMutan_1, SOUNDTYPE_IORI_Kiai_Light01);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_GaishikiMutan_2, SOUNDTYPE_IORI_Kiai_Light02);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Shinigami, SOUNDTYPE_IORI_Kiai_Light02);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_HyakushikiOniyaki, SOUNDTYPE_IORI_HyakushikiOniyaki);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_1211ShikiYaOtome_4, SOUNDTYPE_IORI_1211ShikiYaOtome02);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_1211ShikiYaOtome_9, SOUNDTYPE_IORI_1211ShikiYaOtome03);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_HyakushikiOniyaki, SOUNDTYPE_IORI_HyakushikiOniyaki);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Ura306shikiShika_1, SOUNDTYPE_IORI_HyakushikiOniyaki);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Ura306shikiShika_2, SOUNDTYPE_IORI_HyakushikiOniyaki);
  pSoundTable_->RegistSoundInfo(IORI_ANIMTYPE_Ura306shikiShika_3, SOUNDTYPE_IORI_HyakushikiOniyaki);

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
  pStateComponent_->RegistState(IORI_ANIMTYPE_108ShikiYamiBarai, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_1, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_2, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_Shinigami, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_HyakushikiOniyaki, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_1, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_2, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_3, {PS_Attack});
  pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_0, {PS_SkillCasting});
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
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_108ShikiYamiBarai, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_GaishikiMutan_1, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_GaishikiMutan_2, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_Shinigami, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_HyakushikiOniyaki, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_127ShikiAoiHana_1, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_127ShikiAoiHana_2, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_127ShikiAoiHana_3, {PR_LockInput, PR_LockExecuteCommand});
  pRestrictionComponent_->RegistAnimStateRestrict(IORI_ANIMTYPE_1211ShikiYaOtome_0, {PR_LockInput, PR_LockExecuteCommand});
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
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_CloseRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_LongRange, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_Seat, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch_Jump, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, true, 10.0f, {1.5f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, -3.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Shinigami, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 15.0f, {2.0f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.0f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.0f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_3, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {1.5f, -2.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_1, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 100);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_2, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_3, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_4, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_5, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_6, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_7, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_8, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_9, ATTYPE_StrongAttack, ELMTTYPE_BlueFlame, EFTYPE_Iori_Explosion, false, 5.0f, {3.0f, -4.5f}, 150);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_1, ATTYPE_HighAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 5.0f, {0.0f, 0.0f}, 64);
  pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_2, ATTYPE_LowAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, true, 5.0f, {0.0f, -5.0f}, 64);
  // pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Ura306shikiShika_3, ATTYPE_StrongAttack, ELMTTYPE_BlueFlame, EFTYPE_Hit_2, false, 10.0f, {1.5f, -10.0f}, 140.0f);


  // SKILL
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
  SK0_ST0_FR1_AC0_Data0.actionParams_.ChangeSkillState.changeStateIndex_ = 1;
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
  SK1_ST0_FR0_AC0_Data0.actionParams_.SpawnEffect.effectType_ = EFTYPE_Iori_Casting_YamiBarai;
  SK1_ST0_FR0_AC0_Data0.actionParams_.SpawnEffect.spawnEffectPos_ = {40.0f, -280.0f};
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
  SK1_ST0_FR1_AC0_Data0.actionParams_.FireProjectile.projectileType_ = IORI_PROJECTILE_YamiBarai;
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
  SK2_ST0_FR0_AC0_Data0.actionParams_.MovementDash.dashDuration_ = 150.0f;
  SK2_ST0_FR0_AC0_Data0.actionParams_.MovementDash.dashDistance_ = 150.0f;
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
  SK2_ST0_FR1_AC0_Data0.actionParams_.MovementJump.jumpForce_ = {0.4f, -4.5f};
  SkillFrameActionConditionData SK2_ST0_FR1_AC0_Cond0;
  SK2_ST0_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK2_ST0_FR1_Action0;
  SK2_ST0_FR1_Action0.actionDatas_.push_back(SK2_ST0_FR1_AC0_Data0);
  SK2_ST0_FR1_Action0.conditionDatas_.push_back(SK2_ST0_FR1_AC0_Cond0);
  SkillFrameActionData SK2_ST0_FR1_AC1_Data0;
  SK2_ST0_FR1_AC1_Data0.actionType_ = SKILL_FRAME_ACTION_FireProjectile;
  SK2_ST0_FR1_AC1_Data0.actionParams_.FireProjectile.projectileType_ = IORI_PROJECTILE_HyakushikiOniyaki_Low;
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
  SK2_ST0_FR2_AC0_Data0.actionParams_.FireProjectile.projectileType_ = IORI_PROJECTILE_HyakushikiOniyaki_High;
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
  SK3_ST0_FR0_AC0_Data0.actionParams_.MovementDash.dashDuration_ = 150;
  SK3_ST0_FR0_AC0_Data0.actionParams_.MovementDash.dashDistance_ = 80.0f;
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
  SK3_ST0_FR2_AC0_Data0.actionParams_.ChangeSkillState.changeStateIndex_ = 1;
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
  SK3_ST1_FR0_AC0_Data0.actionParams_.MovementDash.dashDuration_ = 150;
  SK3_ST1_FR0_AC0_Data0.actionParams_.MovementDash.dashDistance_ = 80.0f;
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
  SK3_ST1_FR2_AC0_Data0.actionParams_.ChangeSkillState.changeStateIndex_ = 2;
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
  SK3_ST2_FR0_AC0_Data0.actionParams_.MovementJump.jumpForce_ = {0.3f, -3.0f};
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
  SK4_ST0_FR0_AC0_Data0.actionParams_.MovementJump.jumpForce_ = {1.7f, -2.3f};
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
  SK5_ST0_FR0_AC0_Data0.actionParams_.SpawnEffect.effectType_ = EFTYPE_Casting_1;
  SK5_ST0_FR0_AC0_Data0.actionParams_.SpawnEffect.spawnEffectPos_ = {0.0f, -500.0f};
  SkillFrameActionConditionData SK5_ST0_FR0_AC0_Cond0;
  SK5_ST0_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST0_FR0_Action0;
  SK5_ST0_FR0_Action0.actionDatas_.push_back(SK5_ST0_FR0_AC0_Data0);
  SK5_ST0_FR0_Action0.conditionDatas_.push_back(SK5_ST0_FR0_AC0_Cond0);
  SkillFrameActionData SK5_ST0_FR0_AC1_Data0;
  SK5_ST0_FR0_AC1_Data0.actionType_ = SKILL_FRAME_ACTION_SpawnEffect;
  SK5_ST0_FR0_AC1_Data0.actionParams_.SpawnEffect.effectType_ = EFTYPE_Casting_2;
  SK5_ST0_FR0_AC1_Data0.actionParams_.SpawnEffect.spawnEffectPos_ = {0.0f, -500.0f};
  SkillFrameActionConditionData SK5_ST0_FR0_AC1_Cond0;
  SK5_ST0_FR0_AC1_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST0_FR0_Action1;
  SK5_ST0_FR0_Action1.actionDatas_.push_back(SK5_ST0_FR0_AC1_Data0);
  SK5_ST0_FR0_Action1.conditionDatas_.push_back(SK5_ST0_FR0_AC1_Cond0);
  SkillFrameActionData SK5_ST0_FR0_AC2_Data0;
  SK5_ST0_FR0_AC2_Data0.actionType_ = SKILL_FRAME_ACTION_InflictRestrictionOpponentPlayer;
  SK5_ST0_FR0_AC2_Data0.actionParams_.Restriction.isInfinite_ = true;
  SK5_ST0_FR0_AC2_Data0.actionParams_.Restriction.restrictions_.set(PR_LockInput);
  SK5_ST0_FR0_AC2_Data0.actionParams_.Restriction.restrictions_.set(PR_LockExecuteCommand);
  SK5_ST0_FR0_AC2_Data0.actionParams_.Restriction.restrictions_.set(PR_StopAnim);

  SkillFrameActionConditionData SK5_ST0_FR0_AC2_Cond0;
  SK5_ST0_FR0_AC2_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameAction SK5_ST0_FR0_Action2;
  SK5_ST0_FR0_Action2.actionDatas_.push_back(SK5_ST0_FR0_AC2_Data0);
  SK5_ST0_FR0_Action2.conditionDatas_.push_back(SK5_ST0_FR0_AC2_Cond0);
  SkillFrameActionData SK5_ST0_FR0_AC3_Data0;
  SK5_ST0_FR0_AC3_Data0.actionType_ = SKILL_FRAME_ACTION_FadeOut;
  SK5_ST0_FR0_AC3_Data0.actionParams_.Fade.fadeDuration_ = 50;
  SK5_ST0_FR0_AC3_Data0.actionParams_.Fade.fadeImageType_ = IMGTYPE_BlackBoardImage;
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
  SK5_ST0_FR1_AC0_Data0.actionParams_.ChangeSkillState.changeStateIndex_ = 1;
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
  SK5_State0.animState_ = IORI_ANIMTYPE_1211ShikiYaOtome_0;
  SK5_State0.frames_.push_back(SK5_ST0_Frame0);
  SK5_State0.frames_.push_back(SK5_ST0_Frame1);
  SkillFrameActionConditionData SK5_ST1_FR0_AC0_Cond0;
  SK5_ST1_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK5_ST1_FR0_AC0_Data0;
  SK5_ST1_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ClearRestrictionOpponentPlayer;
  SK5_ST1_FR0_AC0_Data0.actionParams_;
  SkillFrameActionData SK5_ST1_FR0_AC0_Data1;
  SK5_ST1_FR0_AC0_Data1.actionType_ = SKILL_FRAME_ACTION_FadeIn;
  SK5_ST1_FR0_AC0_Data1.actionParams_.Fade.fadeDuration_ = 50;
  SkillFrameAction SK5_ST1_FR0_Action0;
  SK5_ST1_FR0_Action0.conditionDatas_.push_back(SK5_ST1_FR0_AC0_Cond0);
  SK5_ST1_FR0_Action0.actionDatas_.push_back(SK5_ST1_FR0_AC0_Data0);
  SK5_ST1_FR0_Action0.actionDatas_.push_back(SK5_ST1_FR0_AC0_Data1);
  SkillFrame SK5_ST1_Frame0;
  SK5_ST1_Frame0.startIndex_ = 70;
  SK5_ST1_Frame0.endIndex_ = 70;
  SK5_ST1_Frame0.actions_.push_back(SK5_ST1_FR0_Action0);
  SkillFrameActionData SK5_ST1_FR1_AC0_Data0;
  SK5_ST1_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_MovementDash;
  SK5_ST1_FR1_AC0_Data0.actionParams_.MovementDash.dashDuration_ = 250;
  SK5_ST1_FR1_AC0_Data0.actionParams_.MovementDash.dashDistance_ = 1000.0f;
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
  SK5_ST1_FR2_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_InflictRestrictionOpponentPlayer;
  SK5_ST1_FR2_AC0_Data0.actionParams_.Restriction.isInfinite_ = true;
  SK5_ST1_FR2_AC0_Data0.actionParams_.Restriction.restrictions_.set(PR_LockInput);
  SK5_ST1_FR2_AC0_Data0.actionParams_.Restriction.restrictions_.set(PR_LockExecuteCommand);
  SK5_ST1_FR2_AC0_Data0.actionParams_.Restriction.restrictions_.set(PR_LockAnimTrans);
  SkillFrameActionData SK5_ST1_FR2_AC0_Data1;
  SK5_ST1_FR2_AC0_Data1.actionType_ = SKILL_FRAME_ACTION_MovementDash;
  SK5_ST1_FR2_AC0_Data1.actionParams_.MovementDash.dashDuration_ = 250;
  SK5_ST1_FR2_AC0_Data1.actionParams_.MovementDash.dashDistance_ = 1000.0f;
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
  SK5_ST1_FR2_AC1_Data1.actionParams_.ChangeSkillState.changeStateIndex_ = 2;
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
  SK5_ST2_FR0_AC0_Data0.actionParams_.Fade.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST2_FR0_AC0_Data0.actionParams_.Fade.fadeDuration_ = 50;
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
  SK5_ST2_FR1_AC0_Data0.actionParams_.ChangeSkillState.changeStateIndex_ = 3;
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
  SK5_ST3_FR0_AC0_Data0.actionParams_.Fade.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST3_FR0_AC0_Data0.actionParams_.Fade.fadeDuration_ = 50;
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
  SK5_ST3_FR1_AC0_Data0.actionParams_.ChangeSkillState.changeStateIndex_ = 4;
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
  SK5_ST4_FR0_AC0_Data0.actionParams_.Fade.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST4_FR0_AC0_Data0.actionParams_.Fade.fadeDuration_ = 50;
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
  SK5_ST4_FR1_AC0_Data0.actionParams_.ChangeSkillState.changeStateIndex_ = 5;
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
  SK5_ST5_FR0_AC0_Data0.actionParams_.Fade.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST5_FR0_AC0_Data0.actionParams_.Fade.fadeDuration_ = 50;
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
  SK5_ST5_FR1_AC0_Data0.actionParams_.ChangeSkillState.changeStateIndex_ = 6;
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
  SK5_ST6_FR0_AC0_Data0.actionParams_.Fade.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST6_FR0_AC0_Data0.actionParams_.Fade.fadeDuration_ = 50;
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
  SK5_ST6_FR1_AC0_Data0.actionParams_.ChangeSkillState.changeStateIndex_ = 7;
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
  SK5_ST7_FR0_AC0_Data0.actionParams_.Fade.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST7_FR0_AC0_Data0.actionParams_.Fade.fadeDuration_ = 50;
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
  SK5_ST7_FR1_AC0_Data0.actionParams_.ChangeSkillState.changeStateIndex_ = 8;
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
  SkillFrameActionConditionData SK5_ST8_FR0_AC0_Cond0;
  SK5_ST8_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK5_ST8_FR0_AC0_Data0;
  SK5_ST8_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_FadeInOut;
  SK5_ST8_FR0_AC0_Data0.actionParams_.Fade.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST8_FR0_AC0_Data0.actionParams_.Fade.fadeDuration_ = 50;
  SkillFrameActionData SK5_ST8_FR0_AC0_Data1;
  SK5_ST8_FR0_AC0_Data1.actionType_ = SKILL_FRAME_ACTION_InflictRestrictionOpponentPlayer;
  SK5_ST8_FR0_AC0_Data1.actionParams_.Restriction.isInfinite_ = true;
  SK5_ST8_FR0_AC0_Data1.actionParams_.Restriction.restrictions_.set(PR_StopAnim);
  SkillFrameAction SK5_ST8_FR0_Action0;
  SK5_ST8_FR0_Action0.actionDatas_.push_back(SK5_ST8_FR0_AC0_Data0);
  SK5_ST8_FR0_Action0.actionDatas_.push_back(SK5_ST8_FR0_AC0_Data1);
  SK5_ST8_FR0_Action0.conditionDatas_.push_back(SK5_ST8_FR0_AC0_Cond0);
  SkillFrame SK5_ST8_Frame0;
  SK5_ST8_Frame0.startIndex_ = 102;
  SK5_ST8_Frame0.endIndex_ = 102;
  SK5_ST8_Frame0.actions_.push_back(SK5_ST8_FR0_Action0);
  SkillFrameActionData SK5_ST8_FR1_AC0_Data0;
  SK5_ST8_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK5_ST8_FR1_AC0_Data0.actionParams_.ChangeSkillState.changeStateIndex_ = 9;
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
  SK5_ST9_FR0_AC0_Data0.actionParams_.SetPostionOpponentPlayer.opponentForcedPosition_ = {50.0f, -40.0f};
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
  SK5_ST9_FR1_AC0_Data0.actionParams_.SoundPlay.soundType_ = SOUNDTYPE_IORI_1211ShikiYaOtome03;
  SkillFrameActionData SK5_ST9_FR1_AC0_Data1;
  SK5_ST9_FR1_AC0_Data1.actionType_ = SKILL_FRAME_ACTION_ReleaseRestrictionOpponentPlayer;
  SK5_ST9_FR1_AC0_Data1.actionParams_.Restriction.restrictions_.set(PR_StopAnim);
  SkillFrameActionData SK5_ST9_FR1_AC0_Data2;
  SK5_ST9_FR1_AC0_Data2.actionType_ = SKILL_FRAME_ACTION_ChangeOpponentAnimState;
  SK5_ST9_FR1_AC0_Data2.actionParams_.ChangeOpponentAnimState.opponentAnimState_ = PLAYER_ANIMTYPE_NeckGrabbed;
  SkillFrameAction SK5_ST9_FR1_Action0;
  SK5_ST9_FR1_Action0.conditionDatas_.push_back(SK5_ST9_FR1_AC0_Cond0);
  SK5_ST9_FR1_Action0.actionDatas_.push_back(SK5_ST9_FR1_AC0_Data0);
  SK5_ST9_FR1_Action0.actionDatas_.push_back(SK5_ST9_FR1_AC0_Data1);
  SK5_ST9_FR1_Action0.actionDatas_.push_back(SK5_ST9_FR1_AC0_Data2);
  SkillFrame SK5_ST9_Frame1;
  SK5_ST9_Frame1.startIndex_ = 349;
  SK5_ST9_Frame1.endIndex_ = 349;
  SK5_ST9_Frame1.actions_.push_back(SK5_ST9_FR1_Action0);

  SkillFrameActionConditionData SK5_ST9_FR2_AC0_Cond0;
  SK5_ST9_FR2_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK5_ST9_FR2_AC0_Data0;
  SK5_ST9_FR2_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_FadeInOut;
  SK5_ST9_FR2_AC0_Data0.actionParams_.Fade.fadeImageType_ = IMGTYPE_WhiteBoardImage;
  SK5_ST9_FR2_AC0_Data0.actionParams_.Fade.fadeDuration_ = 50;
  SkillFrameActionData SK5_ST9_FR2_AC0_Data1;
  SK5_ST9_FR2_AC0_Data1.actionType_ = SKILL_FRAME_ACTION_CameraShake;
  SK5_ST9_FR2_AC0_Data1.actionParams_.CameraShake.cameraShakeDuration_ = 400;
  SkillFrameAction SK5_ST9_FR2_Action0;
  SK5_ST9_FR2_Action0.conditionDatas_.push_back(SK5_ST9_FR2_AC0_Cond0);
  SK5_ST9_FR2_Action0.actionDatas_.push_back(SK5_ST9_FR2_AC0_Data0);
  SK5_ST9_FR2_Action0.actionDatas_.push_back(SK5_ST9_FR2_AC0_Data1);
  SkillFrameActionConditionData SK5_ST9_FR2_AC1_Cond0;
  SK5_ST9_FR2_AC1_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_HasAttackCollition;
  SkillFrameActionConditionData SK5_ST9_FR2_AC1_Cond1;
  SK5_ST9_FR2_AC1_Cond1.conditionType_ = SKILL_FRAME_ACTION_COND_IsCommandMiscOn;
  SkillFrameActionData SK5_ST9_FR2_AC1_Data0;
  SK5_ST9_FR2_AC1_Data0.actionType_ = SKILL_FRAME_ACTION_ClearRestrictionOpponentPlayer;
  SkillFrameActionData SK5_ST9_FR2_AC1_Data1;
  SK5_ST9_FR2_AC1_Data1.actionType_ = SKILL_FRAME_ACTION_ExecuteNextSkill;
  SK5_ST9_FR2_AC1_Data1.actionParams_.NextSkill.skillTag_ = SKILL_6;
  SkillFrameAction SK5_ST9_FR2_Action1;
  SK5_ST9_FR2_Action1.conditionDatas_.push_back(SK5_ST9_FR2_AC1_Cond0);
  SK5_ST9_FR2_Action1.conditionDatas_.push_back(SK5_ST9_FR2_AC1_Cond1);
  SK5_ST9_FR2_Action1.actionDatas_.push_back(SK5_ST9_FR2_AC1_Data0);
  SK5_ST9_FR2_Action1.actionDatas_.push_back(SK5_ST9_FR2_AC1_Data1);
  SkillFrame SK5_ST9_Frame2;
  SK5_ST9_Frame2.startIndex_ = 351;
  SK5_ST9_Frame2.endIndex_ = 351;
  SK5_ST9_Frame2.actions_.push_back(SK5_ST9_FR2_Action0);
  SK5_ST9_Frame2.actions_.push_back(SK5_ST9_FR2_Action1);
  SkillFrameActionConditionData SK5_ST9_FR3_AC0_Cond0;
  SK5_ST9_FR3_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_AnimationEnd;
  SkillFrameActionData SK5_ST9_FR3_AC0_Data0;
  SK5_ST9_FR3_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ClearRestrictionOpponentPlayer;
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

  SkillFrameActionConditionData SK6_ST0_FR0_AC0_Cond0;
  SK6_ST0_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK6_ST0_FR0_AC0_Data0;
  SK6_ST0_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_SpawnEffect;
  SK6_ST0_FR0_AC0_Data0.actionParams_.SpawnEffect.effectType_ = EFTYPE_Casting_1;
  SK6_ST0_FR0_AC0_Data0.actionParams_.SpawnEffect.spawnEffectPos_ = {0.0f, -500.0f};
  SkillFrameActionData SK6_ST0_FR0_AC0_Data1;
  SK6_ST0_FR0_AC0_Data1.actionType_ = SKILL_FRAME_ACTION_SpawnEffect;
  SK6_ST0_FR0_AC0_Data1.actionParams_.SpawnEffect.effectType_ = EFTYPE_Casting_2;
  SK6_ST0_FR0_AC0_Data1.actionParams_.SpawnEffect.spawnEffectPos_ = {0.0f, -500.0f};
  SkillFrameActionData SK6_ST0_FR0_AC0_Data2;
  SK6_ST0_FR0_AC0_Data2.actionType_ = SKILL_FRAME_ACTION_InflictRestrictionOpponentPlayer;
  SK6_ST0_FR0_AC0_Data2.actionParams_.Restriction.isInfinite_ = true;
  SK6_ST0_FR0_AC0_Data2.actionParams_.Restriction.restrictions_.set(PR_StopMove);
  SK6_ST0_FR0_AC0_Data2.actionParams_.Restriction.restrictions_.set(PR_StopAnim);
  SkillFrameActionData SK6_ST0_FR0_AC0_Data3;
  SK6_ST0_FR0_AC0_Data3.actionType_ = SKILL_FRAME_ACTION_FadeOut;
  SK6_ST0_FR0_AC0_Data3.actionParams_.Fade.fadeDuration_ = 50;
  SK6_ST0_FR0_AC0_Data3.actionParams_.Fade.fadeImageType_ = IMGTYPE_BlackBoardImage;
  SkillFrameAction SK6_ST0_FR0_Action0;
  SK6_ST0_FR0_Action0.conditionDatas_.push_back(SK6_ST0_FR0_AC0_Cond0);
  SK6_ST0_FR0_Action0.actionDatas_.push_back(SK6_ST0_FR0_AC0_Data0);
  SK6_ST0_FR0_Action0.actionDatas_.push_back(SK6_ST0_FR0_AC0_Data1);
  SK6_ST0_FR0_Action0.actionDatas_.push_back(SK6_ST0_FR0_AC0_Data2);
  SK6_ST0_FR0_Action0.actionDatas_.push_back(SK6_ST0_FR0_AC0_Data3);
  SkillFrame SK6_ST0_Frame0;
  SK6_ST0_Frame0.startIndex_ = 353;
  SK6_ST0_Frame0.endIndex_ = 353;
  SK6_ST0_Frame0.actions_.push_back(SK6_ST0_FR0_Action0);
  SkillFrameActionConditionData SK6_ST0_FR1_AC0_Cond0;
  SK6_ST0_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK6_ST0_FR1_AC0_Data0;
  SK6_ST0_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ClearRestrictionOpponentPlayer;
  SkillFrameAction SK6_ST0_FR1_Action0;
  SK6_ST0_FR1_Action0.conditionDatas_.push_back(SK6_ST0_FR1_AC0_Cond0);
  SK6_ST0_FR1_Action0.actionDatas_.push_back(SK6_ST0_FR1_AC0_Data0);
  SkillFrame SK6_ST0_Frame1;
  SK6_ST0_Frame1.startIndex_ = 356;
  SK6_ST0_Frame1.endIndex_ = 356;
  SK6_ST0_Frame1.actions_.push_back(SK6_ST0_FR1_Action0);
  SkillFrameActionConditionData SK6_ST0_FR2_AC0_Cond0;
  SK6_ST0_FR2_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK6_ST0_FR2_AC0_Data0;
  SK6_ST0_FR2_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_InflictRestrictionOpponentPlayer;
  SK6_ST0_FR2_AC0_Data0.actionParams_.Restriction.isInfinite_ = true;
  SK6_ST0_FR2_AC0_Data0.actionParams_.Restriction.restrictions_.set(PR_StopMove);
  SK6_ST0_FR2_AC0_Data0.actionParams_.Restriction.restrictions_.set(PR_StopAnim);
  SK6_ST0_FR2_AC0_Data0.actionParams_.Restriction.restrictions_.set(PR_LockAnimTrans);
  SkillFrameAction SK6_ST0_FR2_Action0;
  SK6_ST0_FR2_Action0.conditionDatas_.push_back(SK6_ST0_FR2_AC0_Cond0);
  SK6_ST0_FR2_Action0.actionDatas_.push_back(SK6_ST0_FR2_AC0_Data0);
  SkillFrame SK6_ST0_Frame2;
  SK6_ST0_Frame2.startIndex_ = 357;
  SK6_ST0_Frame2.endIndex_ = 357;
  SK6_ST0_Frame2.actions_.push_back(SK6_ST0_FR2_Action0);
  SkillFrameActionConditionData SK6_ST0_FR3_AC0_Cond0;
  SK6_ST0_FR3_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK6_ST0_FR3_AC0_Data0;
  SK6_ST0_FR3_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK6_ST0_FR3_AC0_Data0.actionParams_.ChangeSkillState.changeStateIndex_ = 1;
  SkillFrameAction SK6_ST0_FR3_Action0;
  SK6_ST0_FR3_Action0.conditionDatas_.push_back(SK6_ST0_FR3_AC0_Cond0);
  SK6_ST0_FR3_Action0.actionDatas_.push_back(SK6_ST0_FR3_AC0_Data0);
  SkillFrame SK6_ST0_Frame3;
  SK6_ST0_Frame3.startIndex_ = 360;
  SK6_ST0_Frame3.endIndex_ = 360;
  SK6_ST0_Frame3.actions_.push_back(SK6_ST0_FR3_Action0);
  SkillState SK6_State0;
  SK6_State0.animState_ = IORI_ANIMTYPE_Ura306shikiShika_1;
  SK6_State0.frames_.push_back(SK6_ST0_Frame0);
  SK6_State0.frames_.push_back(SK6_ST0_Frame1);
  SK6_State0.frames_.push_back(SK6_ST0_Frame2);
  SK6_State0.frames_.push_back(SK6_ST0_Frame3);
  SkillFrameActionConditionData SK6_ST1_FR0_AC0_Cond0;
  SK6_ST1_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK6_ST1_FR0_AC0_Data0;
  SK6_ST1_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ReleaseRestrictionOpponentPlayer;
  SK6_ST1_FR0_AC0_Data0.actionParams_.Restriction.restrictions_.set(PR_StopMove);
  SkillFrameAction SK6_ST1_FR0_Action0;
  SK6_ST1_FR0_Action0.conditionDatas_.push_back(SK6_ST1_FR0_AC0_Cond0);
  SK6_ST1_FR0_Action0.actionDatas_.push_back(SK6_ST1_FR0_AC0_Data0);
  SkillFrame SK6_ST1_Frame0;
  SK6_ST1_Frame0.startIndex_ = 363;
  SK6_ST1_Frame0.endIndex_ = 363;
  SK6_ST1_Frame0.actions_.push_back(SK6_ST1_FR0_Action0);
  SkillFrameActionConditionData SK6_ST1_FR1_AC0_Cond0;
  SK6_ST1_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK6_ST1_FR1_AC0_Data0;
  SK6_ST1_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ChangeSkillState;
  SK6_ST1_FR1_AC0_Data0.actionParams_.ChangeSkillState.changeStateIndex_ = 2;
  SkillFrameAction SK6_ST1_FR1_Action0;
  SK6_ST1_FR1_Action0.conditionDatas_.push_back(SK6_ST1_FR1_AC0_Cond0);
  SK6_ST1_FR1_Action0.actionDatas_.push_back(SK6_ST1_FR1_AC0_Data0);
  SkillFrame SK6_ST1_Frame1;
  SK6_ST1_Frame1.startIndex_ = 370;
  SK6_ST1_Frame1.endIndex_ = 370;
  SK6_ST1_Frame1.actions_.push_back(SK6_ST1_FR1_Action0);
  SkillState SK6_State1;
  SK6_State1.animState_ = IORI_ANIMTYPE_Ura306shikiShika_2;
  SK6_State1.frames_.push_back(SK6_ST1_Frame0);
  SK6_State1.frames_.push_back(SK6_ST1_Frame1);
  SkillFrameActionConditionData SK6_ST2_FR0_AC0_Cond0;
  SK6_ST2_FR0_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK6_ST2_FR0_AC0_Data0;
  SK6_ST2_FR0_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_FireProjectile;
  SK6_ST2_FR0_AC0_Data0.actionParams_.FireProjectile.projectileType_ = PROJECTILE_TYPE::IORI_PROJECTILE_Ura306Shiki;
  SkillFrameActionData SK6_ST2_FR0_AC0_Data1;
  SK6_ST2_FR0_AC0_Data1.actionType_ = SKILL_FRAME_ACTION_ReleaseRestrictionOpponentPlayer;
  SK6_ST2_FR0_AC0_Data1.actionParams_.Restriction.restrictions_.set(PR_StopAnim);
  SkillFrameActionData SK6_ST2_FR0_AC0_Data2;
  SK6_ST2_FR0_AC0_Data2.actionType_ = SKILL_FRAME_ACTION_CameraShake;
  SK6_ST2_FR0_AC0_Data2.actionParams_.CameraShake.cameraShakeDuration_ = 500;
  SkillFrameAction SK6_ST2_FR0_Action0;
  SK6_ST2_FR0_Action0.conditionDatas_.push_back(SK6_ST2_FR0_AC0_Cond0);
  SK6_ST2_FR0_Action0.actionDatas_.push_back(SK6_ST2_FR0_AC0_Data0);
  SK6_ST2_FR0_Action0.actionDatas_.push_back(SK6_ST2_FR0_AC0_Data1);
  SK6_ST2_FR0_Action0.actionDatas_.push_back(SK6_ST2_FR0_AC0_Data2);
  SkillFrame SK6_ST2_Frame0;
  SK6_ST2_Frame0.startIndex_ = 381;
  SK6_ST2_Frame0.endIndex_ = 381;
  SK6_ST2_Frame0.actions_.push_back(SK6_ST2_FR0_Action0);
  SkillFrameActionConditionData SK6_ST2_FR1_AC0_Cond0;
  SK6_ST2_FR1_AC0_Cond0.conditionType_ = SKILL_FRAME_ACTION_COND_None;
  SkillFrameActionData SK6_ST2_FR1_AC0_Data0;
  SK6_ST2_FR1_AC0_Data0.actionType_ = SKILL_FRAME_ACTION_ClearRestrictionOpponentPlayer;
  SkillFrameAction SK6_ST2_FR1_Action0;
  SK6_ST2_FR1_Action0.conditionDatas_.push_back(SK6_ST2_FR1_AC0_Cond0);
  SK6_ST2_FR1_Action0.actionDatas_.push_back(SK6_ST2_FR1_AC0_Data0);
  SkillFrame SK6_ST2_Frame1;
  SK6_ST2_Frame1.startIndex_ = 386;
  SK6_ST2_Frame1.endIndex_ = 386;
  SK6_ST2_Frame1.actions_.push_back(SK6_ST2_FR1_Action0);
  SkillState SK6_State2;
  SK6_State2.animState_ = IORI_ANIMTYPE_Ura306shikiShika_3;
  SK6_State2.frames_.push_back(SK6_ST2_Frame0);
  SK6_State2.frames_.push_back(SK6_ST2_Frame1);
  Skill Skill_6;
  Skill_6.skillTag_ = SKILL_6;
  Skill_6.castCondition_ = SKILL_CAST_COND_HasSkillPoint;
  Skill_6.castAction_ = SKILL_CAST_ACTION_ReduceSkillPoint;
  Skill_6.skillStates_.push_back(SK6_State0);
  Skill_6.skillStates_.push_back(SK6_State1);
  Skill_6.skillStates_.push_back(SK6_State2);
  pSkillComponent_->RegistSkill(Skill_6);


    // COMMAND
  CommandAction CM0_Action0;
  CM0_Action0.action_ = COMMAND_ACTION_UpdateAnimState;
  CM0_Action0.params_.UpdateAnimState.animStateTag_ = PLAYER_ANIMTYPE_BackStep;
  CommandAction CM0_Action1;
  CM0_Action1.action_ = COMMAND_ACTION_MovementBackStep;
  Command command0;
  command0.commandTag_ = COMMAND_0;
  command0.actions_.push_back(CM0_Action0);
  command0.actions_.push_back(CM0_Action1);
  pCommandComponent_->RegistCommand({CK_Left, CK_Left}, command0);

  CommandAction CM1_Action0;
  CM1_Action0.action_ = COMMAND_ACTION_UpdateAnimState;
  CM1_Action0.params_.UpdateAnimState.animStateTag_ = PLAYER_ANIMTYPE_Run;
  Command command1;
  command1.commandTag_ = COMMAND_1;
  command1.actions_.push_back(CM1_Action0);
  pCommandComponent_->RegistCommand({CK_Right, CK_Right}, command1);

  CommandAction CM2_Action0;
  CM2_Action0.action_ = COMMAND_ACTION_ExecuteSkill;
  CM2_Action0.params_.ExecuteSkill.skillTag_ = SKILL_1;
  Command command2;
  command2.commandTag_ = COMMAND_2;
  command2.actions_.push_back(CM2_Action0);
  pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_A}, command2);
  pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_B}, command2);

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
