#include "stdafx.h"
#include "KOFPlayer.h"
#include "MovementComponent.h"
#include "RestrictionComponent.h"
#include "StateComponent.h"
#include "AnimStateTransMachine.h"

AnimaStateTransMachine::AnimaStateTransMachine()
    : pOwnerPlayer_(nullptr),
      pOwnerRenderer_(nullptr),
      pOwnerStateComponent_(nullptr),
      pOwnerRestrictionComponent_(nullptr),
      pOwnerMovementComponent_(nullptr),
      animTransStateTable_(),
      curTickTransCond(ANIM_TRANS_COND::None) {
}

AnimaStateTransMachine::~AnimaStateTransMachine() {
  for (HashTableIterator iter = animTransStateTable_.begin(); iter != animTransStateTable_.end();) {
    AnimTransState* pDel = (AnimTransState*)*iter;
    iter = animTransStateTable_.erase(iter);

    delete pDel;
  }

  animTransStateTable_.Cleanup();
}

void AnimaStateTransMachine::BeginPlay() {
}

void AnimaStateTransMachine::Tick(unsigned long long deltaTick) {
  if (true == pOwnerRestrictionComponent_->ContainFinalRestrict({PR_StopAnim})) {
    pOwnerRenderer_->SetEnableTick(false);
  } else {
    pOwnerRenderer_->SetEnableTick(true);
  }

  ClearCurrentTransCondition();

  UpdateTransition();
}

bool AnimaStateTransMachine::Initialize(
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

  bool ret = animTransStateTable_.Initialize(8, 8);
  return ret;
}

bool AnimaStateTransMachine::RegistAnimTransition(const AnimTransState& animTransState) {
  AnimTransState* pFind;
  if (0 != animTransStateTable_.Select((void**)&pFind, 1, &animTransState.fromAnimState_, 8)) {
    return false;
  }

  AnimTransState* pNewState = new AnimTransState;
  pNewState->fromAnimState_ = animTransState.fromAnimState_;
  pNewState->animTransRules_ = animTransState.animTransRules_;

  pNewState->searchHandle_ = animTransStateTable_.Insert(pNewState, &pNewState->fromAnimState_, 8);

  return nullptr != pNewState->searchHandle_;
}

void AnimaStateTransMachine::ClearCurrentTransCondition() {
  curTickTransCond = ANIM_TRANS_COND::None;

  if (pOwnerRenderer_->IsAnimationEnd()) {
    curTickTransCond |= ANIM_TRANS_COND::AnimationEnd;
  }
  if (pOwnerMovementComponent_->IsRising()) {
    curTickTransCond |= ANIM_TRANS_COND::MovementRising;
  }
  if (pOwnerMovementComponent_->IsFalling()) {
    curTickTransCond |= ANIM_TRANS_COND::MovementFalling;
  }
  if (pOwnerMovementComponent_->IsOnGround()) {
    curTickTransCond |= ANIM_TRANS_COND::MovementOnGround;
  }
  if (false == pOwnerPlayer_->GetOpponentPlayer()->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
    curTickTransCond |= ANIM_TRANS_COND::OpponentPlayerAttackFinished;
  }
}

void AnimaStateTransMachine::UpdateTransition() {
  if (true == pOwnerRestrictionComponent_->ContainFinalRestrict({PR_LockAnimTrans})) {
    return;
  }

  unsigned long long curAnim = pOwnerStateComponent_->GetCurAnimState();
  unsigned long long animMod = ExtractAnimationModifier();

  AnimTransState* pState;
  if (0 == animTransStateTable_.Select((void**)&pState, 1, &curAnim, 8)) {
    return;
  }

  for (int i = 0; i < pState->animTransRules_.size(); ++i) {
    unsigned int transCond = pState->animTransRules_[i].transCondition_;
    unsigned long long toAnimState = pState->animTransRules_[i].toAnimState_;

      if (transCond == (transCond & curTickTransCond)) {
      pOwnerPlayer_->UpdateAnimState(toAnimState, animMod, true);
      return;
    }
  }
}

unsigned long long AnimaStateTransMachine::ExtractAnimationModifier() {
  AnimationInfo* curAnimInfo = pOwnerRenderer_->GetCurAnimationInfo();
  if (nullptr == curAnimInfo) {
    return 0;
  }

  unsigned long long animModeMask = ANIMMOD_MASK;
  unsigned long long curAnimTag = curAnimInfo->animationTag_;

  unsigned long long result = curAnimTag & animModeMask;
  return result;
}
