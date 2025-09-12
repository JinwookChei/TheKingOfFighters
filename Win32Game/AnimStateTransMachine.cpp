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

  UpdateCurrentTransCondition();

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

// AnimTransState HashTable 등록.
bool AnimaStateTransMachine::RegistAnimTransition(const AnimTransState& animTransState) {
  // 만약 등록할 AnimTransState이 HashTable에 이미 존재하면 실패.
  AnimTransState* pFind;
  if (0 != animTransStateTable_.Select((void**)&pFind, 1, &animTransState.fromAnimState_, 8)) {
    return false;
  }

  // 새 AnimTransState의 메모리를 할당하고, HashTable에 등록.
  AnimTransState* pNewState = new AnimTransState;
  pNewState->fromAnimState_ = animTransState.fromAnimState_;
  pNewState->animTransRules_ = animTransState.animTransRules_;
  pNewState->searchHandle_ = animTransStateTable_.Insert(pNewState, &pNewState->fromAnimState_, 8);

  return nullptr != pNewState->searchHandle_;
}

void AnimaStateTransMachine::UpdateCurrentTransCondition() {
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

// Animation Transition. 매 Tick마다 실행.
void AnimaStateTransMachine::UpdateTransition() {
  // 상태제약중 LockAnimTrans 상태면 Animation Transition 실행하지 않음.
  if (true == pOwnerRestrictionComponent_->ContainFinalRestrict({PR_LockAnimTrans})) {
    return;
  }

  // 현재 Animation State
  unsigned long long curAnim = pOwnerStateComponent_->GetCurAnimState();
  // 현재 Animation Modifier ( Modifier - 좌우반전된 애니메이션, 속성이펙트가 적용된 애니메이션인지.. )
  unsigned long long animMod = ExtractAnimationModifier();

  // 현재 Animation State를 Key값으로 AnimTransState를 검색.
  AnimTransState* pState;
  if (0 == animTransStateTable_.Select((void**)&pState, 1, &curAnim, 8)) {
    return;
  }

  // 검색해서 가져온 AnimTransState에서 TransCondition을 만족하면 Animation 업데이트.
  for (int i = 0; i < pState->animTransRules_.size(); ++i) {
    unsigned int transCond = pState->animTransRules_[i].transCondition_;
    unsigned long long toAnimState = pState->animTransRules_[i].toAnimState_;

      if (transCond == (transCond & curTickTransCond)) {            // curTickTransCond ? 현재 Tick에서의 캐릭터 상태조건.
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
