#include "stdafx.h"

#include "CommandComponent.h"
#include "SkillComponent.h"
#include "ProjectileComponent.h"
#include "MovementComponent.h"
#include "StateComponent.h"
#include "AttackTable.h"
#include "SoundTable.h"
#include "HealthComponent.h"
#include "GhostEffect.h"
#include "CollisionBox.h"
#include "KOFLevel.h"

#include "KOFPlayer.h"
#include "Iori.h"
#include "AIiori.h"

#include "AIBehaviorStateMachine.h"

AIiori::AIiori()
    : pAIBehaviorStateMachine_(nullptr) {
}

AIiori::~AIiori() {
}

void AIiori::Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) {
  Iori::Initialize(isPlayer1, position, useCameraPosition, opponentPlayer);

  pAIBehaviorStateMachine_ = CreateComponent<AIBehaviorStateMachine>();
  if (false == pAIBehaviorStateMachine_->Initialize()) {
    return;
  }

  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_Idle, 100, 0, &AIiori::Idle, this);
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_MoveFront, 1000, 1000, &AIiori::MoveFront, this);
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_MoveBack, 1000, 1000, &AIiori::MoveBack, this);
  pAIBehaviorStateMachine_->ChangeBehabiorState(AI_BEHABIOR_Idle);
}

void AIiori::Tick(unsigned long long deltaTick) {
  UpdateCollisionBoundScale();

  CheckPushCollision();

  if (true == pStateComponent_->ContainPlayerState({PS_Attack})) {
    UpdateAttack();
  }

  if (false == isControlLocked_) {
    // UpdateCommand();

    // if (true == pRender_->IsAnimationEnd()) {
    //   pCommandComponent_->ExcuteTask();
    // }

    ResetInputBitSet();

    pAIBehaviorStateMachine_->UpdateCoolTime(deltaTick);

    pAIBehaviorStateMachine_->DecideBehabior(deltaTick);

    pAIBehaviorStateMachine_->UpdateBehabior();


    //UpdateInput();

    // TODO
    if (pStateComponent_->ContainPlayerState({PS_Jump})) {
      if (false == pMovementComponent_->EqualMovementState({MOVSTATE_Jump})) {
        UpdateAnimState(PLAYER_ANIMTYPE_Idle, ANIMMOD_NONE);
      }
    }
    // END

    if (true == pStateComponent_->CanInput() || true == pRender_->IsAnimationEnd()) {
      CompareInputBitset();
    }

    if (pProjectileComponent_->GetActiveProjectilesCount() > 0) {
      pStateComponent_->AddState({PS_Attack});
    }

    pSkillComponent_->UpdateActiveSkill();
  }

  UpdatePrevAnimationIndex();
}

void AIiori::UpdateInput() {
  AI_BEHABIOR_STATE curBehabiorState = pAIBehaviorStateMachine_->GetCurBehabior();

  if (true == pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({ PS_Attack })) {
    inputPressBitSet_.set(7);
  }

  switch (curBehabiorState) {
    case AI_BEHABIOR_Idle:
      break;
    case AI_BEHABIOR_MoveFront: {
      inputPressBitSet_.set(5);
    }

    break;
    default:
      break;
  }
}


void AIiori::Idle() {
}



void AIiori::MoveFront() {
    inputPressBitSet_.set(5);
}

void AIiori::MoveBack() {
  inputPressBitSet_.set(7);
}

