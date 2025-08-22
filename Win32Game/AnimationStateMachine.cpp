#include "stdafx.h"
#include "KOFPlayer.h"
#include "MovementComponent.h"
#include "RestrictionComponent.h"
#include "StateComponent.h"
#include "AnimationStateMachine.h"

AnimationStateMachine::AnimationStateMachine()
    : pOwnerPlayer_(nullptr),
      pOwnerRenderer_(nullptr),
      pOwnerStateComponent_(nullptr),
      pOwnerRestrictionComponent_(nullptr),
      pOwnerMovementComponent_(nullptr),
      //curAnimationState_(PLAYER_ANIMTYPE_None),
      //curAnimationModifier_(ANIMMOD_NONE),
      animTransitionTable_(),
      transCondition_(TRANSITION_CONDITION::None) {
}

AnimationStateMachine::~AnimationStateMachine() {
  for (HashTableIterator iter = animTransitionTable_.begin(); iter != animTransitionTable_.end();) {
    AttackInfo* pDel = (AttackInfo*)*iter;
    iter = animTransitionTable_.erase(iter);

    delete pDel;
  }

  animTransitionTable_.Cleanup();
}

void AnimationStateMachine::BeginPlay() {
}

void AnimationStateMachine::Tick(unsigned long long deltaTick) {
  if (true == pOwnerRestrictionComponent_->ContainFinalRestrict({PR_StopAnim})) {
    pOwnerRenderer_->SetEnableTick(false);
  } else {
    pOwnerRenderer_->SetEnableTick(true);
  }

  InitCondition();

  if (false == pOwnerRestrictionComponent_->ContainFinalRestrict({ PR_LockAnimTrans })) {
    UpdateAnimation();
  }
}

bool AnimationStateMachine::Initialize(
    KOFPlayer* pOwnerPlayer,
    ImageRenderer* pImageRenderer,
    StateComponent* pStateComponent,
    MovementComponent* pMovementComponent,
    RestrictionComponent* pRestrictionComponent) {
  if (nullptr == pOwnerPlayer) {
    return false;
  }
  if (nullptr == pImageRenderer) {
    return false;
  }
  if (nullptr == pStateComponent) {
    return false;
  }
  if (nullptr == pMovementComponent) {
    return false;
  }
  if (nullptr == pRestrictionComponent) {
    return false;
  }

  pOwnerPlayer_ = pOwnerPlayer;
  pOwnerRenderer_ = pImageRenderer;
  pOwnerStateComponent_ = pStateComponent;
  pOwnerMovementComponent_ = pMovementComponent;
  pOwnerRestrictionComponent_ = pRestrictionComponent;

  bool ret = animTransitionTable_.Initialize(8, 8);
  return ret;
}

//unsigned long long AnimationStateMachine::CurrentAnimationState() const {
//  return curAnimationState_;
//}
//
//void AnimationStateMachine::SetCurrentAnimationState(unsigned long long animationState) {
//  curAnimationState_ = animationState;
//}
//
//unsigned long long AnimationStateMachine::CurrentAnimationModifier() const {
//  return curAnimationModifier_;
//}
//
//void AnimationStateMachine::SetCurrentAnimationModifier(unsigned long long animationModifier) {
//  curAnimationModifier_ = animationModifier;
//}

bool AnimationStateMachine::RegistAnimTransition(unsigned long long fromAnimState, unsigned int transCondition1, bool isEqualCondition1, unsigned long long nextAnimState1, unsigned int transCondition2, bool isEqualCondition2, unsigned long long nextAnimState2, unsigned int transCondition3, bool isEqualCondition3, unsigned long long nextAnimState3) {
  AnimTransitionRule* pFind;
  if (0 != animTransitionTable_.Select((void**)&pFind, 1, &fromAnimState, 8)) {
    return false;
  }

  AnimTransitionRule* pInfo = new AnimTransitionRule;
  pInfo->fromAnimState_ = fromAnimState;

  pInfo->transCondition1_ = transCondition1;
  pInfo->isEqualCondition1_ = isEqualCondition1;
  pInfo->toAnimState1_ = nextAnimState1;

  pInfo->transCondition2_ = transCondition2;
  pInfo->isEqualCondition2_ = isEqualCondition2;
  pInfo->toAnimState2_ = nextAnimState2;

  pInfo->transCondition3_ = transCondition3;
  pInfo->isEqualCondition3_ = isEqualCondition3;
  pInfo->toAnimState3_ = nextAnimState3;

  pInfo->searchHandle_ = animTransitionTable_.Insert(pInfo, &pInfo->fromAnimState_, 8);

  return nullptr != pInfo->searchHandle_;
}

void AnimationStateMachine::InitCondition() {
  transCondition_ = TRANSITION_CONDITION::None;

  if (pOwnerRenderer_->IsAnimationEnd()) {
    transCondition_ |= TRANSITION_CONDITION::AnimationEnd;
  }
  if (pOwnerMovementComponent_->IsRising()) {
    transCondition_ |= TRANSITION_CONDITION::MovementRising;
  }
  if (pOwnerMovementComponent_->IsFalling()) {
    transCondition_ |= TRANSITION_CONDITION::MovementFalling;
  }
  if (pOwnerMovementComponent_->IsOnGround()) {
    transCondition_ |= TRANSITION_CONDITION::MovementOnGround;
  }
  if (false == pOwnerPlayer_->GetOpponentPlayer()->GetPlayerStateComponent()->ContainPlayerState({ PS_Attack }))
  {
    transCondition_ |= TRANSITION_CONDITION::OpponentPlayerAttackFinished;
  }
}

void AnimationStateMachine::UpdateAnimation() {
  if (nullptr == pOwnerRestrictionComponent_) {
    return;
  }
  if (true == pOwnerRestrictionComponent_->ContainFinalRestrict({PR_LockAnimTrans})) {
    return;
  }

  AnimTransitionRule* pInfo;
  unsigned long long curAnim = pOwnerStateComponent_->GetCurAnimState();


  if (0 == animTransitionTable_.Select((void**)&pInfo, 1, &curAnim, 8)) {
    return;
  }

  unsigned long long animMod = ExtractAnimationModifier();

  unsigned int transCondition = pInfo->transCondition1_;
  if (transCondition == None) {
    return;
  }
  if (pInfo->isEqualCondition1_) {
    if (0 == (transCondition ^ transCondition_)) {
      pOwnerPlayer_->UpdateAnimState(pInfo->toAnimState1_, animMod, true);
      return;
    }
  } else {
    if (transCondition == (transCondition & transCondition_)) {
      pOwnerPlayer_->UpdateAnimState(pInfo->toAnimState1_, animMod, true);
      return;
    }
  }

  transCondition = pInfo->transCondition2_;
  if (transCondition == None) {
    return;
  }
  if (pInfo->isEqualCondition2_) {
    if (0 == (transCondition ^ transCondition_)) {
      pOwnerPlayer_->UpdateAnimState(pInfo->toAnimState2_, animMod, true);
      return;
    }
  } else {
    if (transCondition == (transCondition & transCondition_)) {
      pOwnerPlayer_->UpdateAnimState(pInfo->toAnimState2_, animMod, true);
      return;
    }
  }

  transCondition = pInfo->transCondition3_;
  if (transCondition == None) {
    return;
  }
  if (pInfo->isEqualCondition3_) {
    if (0 == (transCondition ^ transCondition_)) {
      pOwnerPlayer_->UpdateAnimState(pInfo->toAnimState3_, animMod, true);
      return;
    }
  } else {
    if (transCondition == (transCondition & transCondition_)) {
      pOwnerPlayer_->UpdateAnimState(pInfo->toAnimState3_, animMod, true);
      return;
    }
  }
}

unsigned long long AnimationStateMachine::ExtractAnimationModifier() {
  AnimationInfo* curAnimInfo = pOwnerRenderer_->GetCurAnimationInfo();
  if (nullptr == curAnimInfo) {
    return 0;
  }

  unsigned long long animModeMask = ANIMMOD_MASK;
  unsigned long long curAnimTag = curAnimInfo->animationTag_;

  unsigned long long result = curAnimTag & animModeMask;
  return result;
}
