#include "stdafx.h"
#include "KOFPlayer.h"
#include "MovementComponent.h"
#include "RestrictionComponent.h"
#include "StateComponent.h"
#include "AnimationHandler.h"

AnimationHandler::AnimationHandler()
    : pOwnerPlayer_(nullptr),
      pOwnerRenderer_(nullptr),
      pOwnerStateComponent_(nullptr),
      pOwnerRestrictionComponent_(nullptr),
      pOwnerMovementComponent_(nullptr),
      curAnimationState_(PLAYER_ANIMTYPE_None),
      curAnimationModifier_(ANIMMOD_NONE),
      animTransitionTable_(),
      transCondition_(TRANSITION_CONDITION::None) {
}

AnimationHandler::~AnimationHandler() {
  for (HashTableIterator iter = animTransitionTable_.begin(); iter != animTransitionTable_.end();) {
    AttackInfo* pDel = (AttackInfo*)*iter;
    iter = animTransitionTable_.erase(iter);

    delete pDel;
  }

  animTransitionTable_.Cleanup();
}

void AnimationHandler::BeginPlay() {
}

void AnimationHandler::Tick(unsigned long long deltaTick) {
}

bool AnimationHandler::Initialize(
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

bool AnimationHandler::CallCreateAnimation(
    unsigned long long animationTag,
    unsigned long long imageIndex,
    unsigned int startIndex,
    unsigned int endIndex,
    unsigned long long interval,
    bool loop,
    unsigned long long loopStartFrame) {
  if (nullptr == pOwnerRenderer_) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_NONE, imageIndex | IMGMOD_NONE, startIndex, endIndex, interval, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_FLIPPED, imageIndex | IMGMOD_FLIPPED, startIndex, endIndex, interval, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_BLUEFLAME, startIndex, endIndex, interval, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME, startIndex, endIndex, interval, loop, loopStartFrame)) {
    return false;
  }
  return true;
}

bool AnimationHandler::CallCreateAnimation(
    unsigned long long animationTag,
    unsigned long long imageIndex,
    const std::vector<unsigned int>& indices,
    unsigned long long interval,
    bool loop,
    unsigned long long loopStartFrame) {
  if (nullptr == pOwnerRenderer_) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_NONE, imageIndex | IMGMOD_NONE, indices, interval, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_FLIPPED, imageIndex | IMGMOD_FLIPPED, indices, interval, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_BLUEFLAME, indices, interval, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME, indices, interval, loop, loopStartFrame)) {
    return false;
  }

  return true;
}

bool AnimationHandler::CallCreateAnimation(
    unsigned long long animationTag,
    unsigned long long imageIndex,
    const std::vector<unsigned int>& indices,
    const std::vector<unsigned long long> intervals,
    bool loop,
    unsigned long long loopStartFrame) {
  if (nullptr == pOwnerRenderer_) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_NONE, imageIndex | IMGMOD_NONE, indices, intervals, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_FLIPPED, imageIndex | IMGMOD_FLIPPED, indices, intervals, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_BLUEFLAME, indices, intervals, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME, indices, intervals, loop, loopStartFrame)) {
    return false;
  }

  return true;
}

unsigned long long AnimationHandler::CurrentAnimationState() const {
  return curAnimationState_;
}

void AnimationHandler::SetCurrentAnimationState(unsigned long long animationState) {
  curAnimationState_ = animationState;
}

unsigned long long AnimationHandler::CurrentAnimationModifier() const {
  return curAnimationModifier_;
}

void AnimationHandler::SetCurrentAnimationModifier(unsigned long long animationModifier) {
  curAnimationModifier_ = animationModifier;
}

bool AnimationHandler::RegistAnimTransition(unsigned long long curAnimState, unsigned int transCondition1, bool equalCondition1, unsigned long long nextAnimState1, unsigned int transCondition2, bool equalCondition2, unsigned long long nextAnimState2, unsigned int transCondition3, bool equalCondition3, unsigned long long nextAnimState3) {
  AnimTransitionRule* pFind;
  if (0 != animTransitionTable_.Select((void**)&pFind, 1, &curAnimState, 8)) {
    return false;
  }

  AnimTransitionRule* pInfo = new AnimTransitionRule;
  pInfo->curAnimState_ = curAnimState;

  pInfo->transCondition1_ = transCondition1;
  pInfo->equalCondition1_ = equalCondition1;
  pInfo->nextAnimState1_ = nextAnimState1;

  pInfo->transCondition2_ = transCondition2;
  pInfo->equalCondition2_ = equalCondition2;
  pInfo->nextAnimState2_ = nextAnimState2;

  pInfo->transCondition3_ = transCondition3;
  pInfo->equalCondition3_ = equalCondition3;
  pInfo->nextAnimState3_ = nextAnimState3;

  pInfo->searchHandle_ = animTransitionTable_.Insert(pInfo, &pInfo->curAnimState_, 8);

  return nullptr != pInfo->searchHandle_;
}

void AnimationHandler::InitCondition() {
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

void AnimationHandler::UpdateAnimation() {
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

  if (nullptr == pInfo) {
    return;
  }

  unsigned int transCondition = pInfo->transCondition1_;
  if (transCondition == None) {
    return;
  }
  if (pInfo->equalCondition1_) {
    if (0 == (transCondition ^ transCondition_)) {
      pOwnerPlayer_->UpdateAnimState(pInfo->nextAnimState1_, curAnimationModifier_, true);
      return;
    }
  } else {
    if (transCondition == (transCondition & transCondition_)) {
      pOwnerPlayer_->UpdateAnimState(pInfo->nextAnimState1_, curAnimationModifier_, true);
      return;
    }
  }

  transCondition = pInfo->transCondition2_;
  if (transCondition == None) {
    return;
  }
  if (pInfo->equalCondition2_) {
    if (0 == (transCondition ^ transCondition_)) {
      pOwnerPlayer_->UpdateAnimState(pInfo->nextAnimState2_, curAnimationModifier_, true);
      return;
    }
  } else {
    if (transCondition == (transCondition & transCondition_)) {
      pOwnerPlayer_->UpdateAnimState(pInfo->nextAnimState2_, curAnimationModifier_, true);
      return;
    }
  }

  transCondition = pInfo->transCondition3_;
  if (transCondition == None) {
    return;
  }
  if (pInfo->equalCondition3_) {
    if (0 == (transCondition ^ transCondition_)) {
      pOwnerPlayer_->UpdateAnimState(pInfo->nextAnimState3_, curAnimationModifier_, true);
      return;
    }
  } else {
    if (transCondition == (transCondition & transCondition_)) {
      pOwnerPlayer_->UpdateAnimState(pInfo->nextAnimState3_, curAnimationModifier_, true);
      return;
    }
  }
}
