#include "stdafx.h"

#include "AnimationHandler.h"
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
#define HYAKUSHIKIONIYAKIRANGE 400.0f
#define RUNRANGE 800.0f
#define JUMPRANGE 400.0f

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

  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_Idle, 20, 0, &AIiori::Idle, this);
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_MoveFront, 200, 8000, &AIiori::MoveFront, this);
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_MoveBack, 200, 8000, &AIiori::MoveBack, this);
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_AttackPunch, 3000, 5000, &AIiori::AttackPunch, this);
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_AttackKick, 3000, 5000, &AIiori::AttackKick, this);
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_AttackJumpPunch, 1000, 5000, &AIiori::AttackJumpPunch, this);
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_AttackJumpKick, 1000, 5000, &AIiori::AttackJumpKick, this);
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_Skill_01, 1000, 5000, &AIiori::ActiveShikiYamiBarai108, this);
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_Skill_02, 1000, 5000, &AIiori::ActiveHyakushikiOniyaki, this);
  pAIBehaviorStateMachine_->RegistBehabior(AI_BEHABIOR_Skill_03, 4000, 5000, &AIiori::ActiveGaishikiMutan, this);
  pAIBehaviorStateMachine_->ChangeBehabiorState(AI_BEHABIOR_Idle);
}

void AIiori::Tick(unsigned long long deltaTick) {
  UpdateCollisionBoundScale();

  CheckPushCollision();

  if (true == pStateComponent_->ContainPlayerState({PS_Attack})) {
    UpdateAttack();
  }

  if (false == IsControlLocked()) {
    if (true == pRender_->IsAnimationEnd()) {
      pCommandComponent_->ExcuteTask();
    }

    ResetInputBitSet();

    pAIBehaviorStateMachine_->UpdateCoolTime(deltaTick);

    pAIBehaviorStateMachine_->DecideBehabior(deltaTick);

    pAIBehaviorStateMachine_->UpdateBehabior();

    // TODO
    if (pStateComponent_->ContainPlayerState({PS_Jump})) {
      if (pMovementComponent_->GetMovementState() == MOVSTATE_Jump) {
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

  pAnimationHandler_->UpdatePrevImageIndex();
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
    int result = dist(gen) == 0 ? 1 : 3;
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
    int result = dist(gen) == 0 ? 0 : 2;
    inputDownBitSet_.set(result);
  } else {
    inputPressBitSet_.set(5);
  }
}

void AIiori::AttackJumpPunch() {
  float distanceX = std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X);
  if (distanceX < JUMPRANGE) {
    inputPressBitSet_.set(5);
    inputPressBitSet_.set(4);
  }

  if (distanceX < PUNCHRANGE) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    int result = dist(gen) == 0 ? 1 : 3;
    inputDownBitSet_.set(result);
  } else {
    inputPressBitSet_.set(5);
  }

  if (PLAYER_ANIMTYPE_HeavyPunch_Jump == pStateComponent_->GetCurAnimState() ||
      PLAYER_ANIMTYPE_LightPunch_Jump == pStateComponent_->GetCurAnimState()) {
    pAIBehaviorStateMachine_->ChangeBehabiorState(AI_BEHABIOR_Idle);
  }
}

void AIiori::AttackJumpKick() {
  float distanceX = std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X);
  if (distanceX < JUMPRANGE) {
    inputPressBitSet_.set(5);
    inputPressBitSet_.set(4);
  }

  if (distanceX < PUNCHRANGE) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    int result = dist(gen) == 0 ? 0 : 2;
    inputDownBitSet_.set(result);
  } else {
    inputPressBitSet_.set(5);
  }

  if (PLAYER_ANIMTYPE_HeavyKick_Jump == pStateComponent_->GetCurAnimState() ||
      PLAYER_ANIMTYPE_LightKick_Jump == pStateComponent_->GetCurAnimState()) {
    pAIBehaviorStateMachine_->ChangeBehabiorState(AI_BEHABIOR_Idle);
  }
}

void AIiori::ActiveGaishikiMutan() {
  float distanceX = std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X);
  if (distanceX > RUNRANGE && distanceX > PUNCHRANGE + 200.0f) {
    pCommandComponent_->JumpNode(CK_Right);
    pCommandComponent_->JumpNode(CK_Right);
  }

  if (distanceX < PUNCHRANGE) {
    inputDownBitSet_.set(1);
    inputPressBitSet_.set(1);
  }
  inputPressBitSet_.set(5);

  if (pStateComponent_->GetCurAnimState() == IORI_ANIMTYPE_GaishikiMutan_2) {
    pAIBehaviorStateMachine_->ChangeBehabiorState(AI_BEHABIOR_Idle);
  }
}

void AIiori::ActiveShikiYamiBarai108() {
  float distanceX = std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X);
  if (distanceX < BACKSTEPRANGE) {
    inputPressBitSet_.set(5);
  }

  pCommandComponent_->JumpNode(CK_Left);
  pCommandComponent_->JumpNode(CK_Down);
  pCommandComponent_->JumpNode(CK_Right);
  pCommandComponent_->JumpNode(CK_A);

  pAIBehaviorStateMachine_->ChangeBehabiorState(AI_BEHABIOR_Idle);
}

void AIiori::ActiveHyakushikiOniyaki() {
  float distanceX = std::fabs(GetPosition().X - pOpponentPlayer_->GetPosition().X);
  if (distanceX >= HYAKUSHIKIONIYAKIRANGE) {
    pCommandComponent_->JumpNode(CK_Left);
    pCommandComponent_->JumpNode(CK_Left);
    return;
  }

  pCommandComponent_->JumpNode(CK_Right);
  pCommandComponent_->JumpNode(CK_Down);
  pCommandComponent_->JumpNode(CK_Right);
  pCommandComponent_->JumpNode(CK_A);

  pAIBehaviorStateMachine_->ChangeBehabiorState(AI_BEHABIOR_Idle);
}
