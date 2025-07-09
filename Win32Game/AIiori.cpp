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

#include <random>
#include "AIBehaviorStateMachine.h"


#define PUNCHRANGE 200.0f
#define KICKRANGE 300.0f
#define BACKSTEPRANGE 400.0f

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
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_AttackPunch, 3000, 1000, &AIiori::AttackPunch, this);
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_AttackKick, 3000, 1000, &AIiori::AttackKick, this);
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_Skill_01, 1000, 1000, &AIiori::ActiveShikiYamiBarai108, this);
  pAIBehaviorStateMachine_->ChangeBehabiorState(AI_BEHABIOR_Idle);
}

void AIiori::Tick(unsigned long long deltaTick) {
  UpdateCollisionBoundScale();

  CheckPushCollision();

  if (true == pStateComponent_->ContainPlayerState({PS_Attack})) {
    UpdateAttack();
  }

  if (false == isControlLocked_) {
    if (true == pRender_->IsAnimationEnd()) {
      pCommandComponent_->ExcuteTask();
    }

    ResetInputBitSet();

    pAIBehaviorStateMachine_->UpdateCoolTime(deltaTick);

    pAIBehaviorStateMachine_->DecideBehabior(deltaTick);

    pAIBehaviorStateMachine_->UpdateBehabior();

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

void AIiori::Idle() {
  if (true == pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
    inputPressBitSet_.set(7);
  }
}

void AIiori::MoveFront() {
  if (true == pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
    inputPressBitSet_.set(7);
  }
  inputPressBitSet_.set(5);
}

void AIiori::MoveBack() {
  if (true == pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
    inputPressBitSet_.set(7);
  }

  float distanceX = std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X);
  if (distanceX < BACKSTEPRANGE) {
    pCommandComponent_->JumpNode(CK_Left);
    pCommandComponent_->JumpNode(CK_Left);
  }

  inputPressBitSet_.set(7);
}

void AIiori::AttackPunch() {
  if (true == pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
    inputPressBitSet_.set(7);
  }

  float distanceX = std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X);
  if (distanceX < PUNCHRANGE) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    int result = dist(gen) == 0 ? 0 : 2;
    inputDownBitSet_.set(result);
  } else {
    inputPressBitSet_.set(5);
  }
}

void AIiori::AttackKick() {
  if (true == pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
    inputPressBitSet_.set(7);
  }

  float distanceX = std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X);
  if (distanceX < KICKRANGE) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    int result = dist(gen) == 0 ? 1 : 3;
    inputDownBitSet_.set(result);
  } else {
    inputPressBitSet_.set(5);
  }
}

void AIiori::ActiveShikiYamiBarai108() {

  float distanceX = std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X);
  if (distanceX < BACKSTEPRANGE) {
    pCommandComponent_->JumpNode(CK_Left);
    pCommandComponent_->JumpNode(CK_Left);
    return;
  }

  pCommandComponent_->JumpNode(CK_Left);
  pCommandComponent_->JumpNode(CK_Down);
  pCommandComponent_->JumpNode(CK_Right);
  pCommandComponent_->JumpNode(CK_A);

  pAIBehaviorStateMachine_->ChangeBehabiorState(AI_BEHABIOR_Idle);
}
