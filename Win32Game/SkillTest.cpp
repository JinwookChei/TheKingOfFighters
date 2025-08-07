#include "stdafx.h"
#include "KOFPlayer.h"
#include "SkillTest.h"
#include "MovementComponent.h"
#include "InputController.h"
#include "ProjectileComponent.h"
#include "MPComponent.h"

SkillTest::SkillTest()
    : pOwnerPlayer_(nullptr),
      pOwnerRenderer_(nullptr),
      pOwnerMovementConponent_(nullptr),
      pOwnerInputController_(nullptr),
      pOwnerAttackCollision_(nullptr),
      pOwnerProjectileComponent_(nullptr),
      pOwnerMPComponent_(nullptr),
      executingSkill_(nullptr),
      curSkillStateIndex_(0) {
}

SkillTest::~SkillTest() {
  for (HashTableIterator iter = skillTable_.begin(); iter != skillTable_.end();) {
    Skill* pDel = (Skill*)*iter;
    iter = skillTable_.erase(iter);

    delete pDel;
  }

  skillTable_.Cleanup();
}

void SkillTest::BeginPlay() {
}

void SkillTest::Tick(unsigned long long deltaTick) {
  UpdateSkill();
}

bool SkillTest::Initialize(
    KOFPlayer* pOwnerPlayer,
    ImageRenderer* pRenderer,
    MovementComponent* pMovementComponent,
    InputController* pInputController,
    CollisionComponent* pAttackCollision,
    ProjectileComponent* pProjectileComponent,
    MPComponent* pMPComponent) {
  if (nullptr == pOwnerPlayer) {
    return false;
  }
  if (nullptr == pRenderer) {
    return false;
  }
  if (nullptr == pMovementComponent) {
    return false;
  }
  if (nullptr == pInputController) {
    return false;
  }
  if (nullptr == pAttackCollision) {
    return false;
  }
  if (nullptr == pProjectileComponent) {
    return false;
  }
  if (nullptr == pMPComponent) {
    return false;
  }

  pOwnerPlayer_ = pOwnerPlayer;
  pOwnerRenderer_ = pRenderer;
  pOwnerMovementConponent_ = pMovementComponent;
  pOwnerInputController_ = pInputController;
  pOwnerAttackCollision_ = pAttackCollision;
  pOwnerProjectileComponent_ = pProjectileComponent;
  pOwnerMPComponent_ = pMPComponent;

  return skillTable_.Initialize(8, 8);
}

bool SkillTest::RegistSkill(Skill skill) {
  Skill* pFind;
  if (0 != skillTable_.Select((void**)&pFind, 1, &skill.skillTag_, 8)) {
    return false;
  }

  Skill* pInfo = new Skill;
  pInfo->skillTag_ = skill.skillTag_;
  pInfo->skillStates_ = skill.skillStates_;
  pInfo->castCondition_ = skill.castCondition_;
  pInfo->castAction_ = skill.castAction_;
  const void* c = &pInfo->skillTag_;
  pInfo->searchHandle_ = skillTable_.Insert(pInfo, &pInfo->skillTag_, 8);

  return nullptr != pInfo->searchHandle_;
}

void SkillTest::UpdateSkill() {
  if (nullptr == executingSkill_) {
    return;
  }

  if (true == pOwnerRenderer_->IsAnimationEnd()) {
    DeActiveSkill();
    return;
  }

  SkillState* pCurState = &executingSkill_->skillStates_[curSkillStateIndex_];

  std::vector<SkillFrame>* pCurSkillFrame = &pCurState->frames_;

  unsigned long long curImageIndex = pOwnerRenderer_->GetImageIndex();

  for (int i = 0; i < pCurSkillFrame->size(); ++i) {
    unsigned long long startIndex = (*pCurSkillFrame)[i].startIndex_;
    unsigned long long endIndex = (*pCurSkillFrame)[i].endIndex_;

    if (curImageIndex >= startIndex && curImageIndex <= endIndex) {
      std::vector<SkillFrameAction>* pActions = &(*pCurSkillFrame)[i].actions_;
      for (int j = 0; j < pActions->size(); ++j) {
        if (true == (*pActions)[j].HasExecuted()) {
          continue;
        }
        std::vector<SKILL_FRAME_ACTION_CONDITION_TYPE>* conditions = &(*pActions)[j].actionConditions_;
        bool conditionFlag = true;
        for (int k = 0; k < conditions->size(); ++k) {
          SKILL_FRAME_ACTION_CONDITION_TYPE conditionType = (*conditions)[k];
          bool ret = CheckFrameActionCondition(conditionType);
          if (false == ret) {
            conditionFlag = false;
            break;
          }
        }
        if (true == conditionFlag) {
          std::vector<SkillFrameActionData>* actionDatas = &(*pActions)[j].actionDatas;
          for (int l = 0; l < actionDatas->size(); ++l) {
            ExcuteSkillFrameAction((*actionDatas)[l].actionType_, (*actionDatas)[l].actionParams_);
          }
          (*pActions)[j].SetHasExcuted(true);
        }
      }
    }
  }
}

void SkillTest::ExecuteSkill(unsigned long long skillTag) {
  if (true == IsSkillExecuting()) {
    return;
  }

  Skill* pInfo;
  if (0 == skillTable_.Select((void**)&pInfo, 1, &skillTag, 8)) {
    return;
  }

  SKILL_CASTING_CONDITION_TYPE executeCondition = pInfo->castCondition_;
  if (false == CheckCastingCondition(executeCondition)) {
    return;
  }
  
  ResetStateMiscFlags(pInfo);

  ResetEventExcutedFlags(pInfo);

  executingSkill_ = pInfo;

  curSkillStateIndex_ = 0;

  unsigned long long animState = executingSkill_->skillStates_[curSkillStateIndex_].animState_;

  pOwnerPlayer_->UpdateAnimState(animState);
}

bool SkillTest::IsSkillExecuting() {
  return nullptr != executingSkill_;
}

void SkillTest::ResetEventExcutedFlags(Skill* pSkill) {
  if (nullptr == pSkill) {
    return;
  }
  for (int i = 0; i < pSkill->skillStates_.size(); ++i) {
    for (int j = 0; j < pSkill->skillStates_[i].frames_.size(); ++j) {
      for (int k = 0; k < pSkill->skillStates_[i].frames_[j].actions_.size(); ++k) {
        pSkill->skillStates_[i].frames_[j].actions_[k].ResetHasExecutedFlag();
      }
    }
  }
}

void SkillTest::ResetStateMiscFlags(Skill* pSkill) {
  if (nullptr == pSkill) {
    return;
  }
  for (int i = 0; i < pSkill->skillStates_.size(); ++i) {
    pSkill->skillStates_[i].SetMiscFlag(false);
  }
}

bool SkillTest::CheckCastingCondition(SKILL_CASTING_CONDITION_TYPE castCondition) {
  switch (castCondition) {
    case SKILL_CAST_COND_None:
      return true;
      break;
    case SKILL_CAST_COND_HasSkillPoint:
      return HasSkillPoint();
      break;
    default:
      break;
  }

  return true;
}

bool SkillTest::HasSkillPoint() const {
  return 1 <= pOwnerMPComponent_->SkillPoint();
}

void SkillTest::ExcuteCastingAction(SKILL_CASTING_ACTION_TYPE castAction) {
  switch (castAction) {
    case SKILL_CAST_ACTION_None:
      break;
    case SKILL_CAST_ACTION_ReduceSkillPoint:
      break;
    default:
      break;
  }
}

bool SkillTest::CheckFrameActionCondition(SKILL_FRAME_ACTION_CONDITION_TYPE actionCondition) const {
  switch (actionCondition) {
    case SKILL_FRAME_ACTION_COND_None:
      return true;
      break;
    case SKILL_FRAME_ACTION_COND_AnimationEnd:
      return pOwnerRenderer_->IsAnimationEnd();
      break;
    case SKILL_FRAME_ACTION_COND_CheckInputDownA:
      return pOwnerInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_A});
      break;
    case SKILL_FRAME_ACTION_COND_CheckInputDownB:
      return pOwnerInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_B});
      break;
    case SKILL_FRAME_ACTION_COND_CheckInputDownC:
      return pOwnerInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_C});
      break;
    case SKILL_FRAME_ACTION_COND_CheckInputDownD:
      return pOwnerInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_D});
      break;
    case SKILL_FRAME_ACTION_COND_HasAttackCollition:
      return pOwnerAttackCollision_->HasHit();
      break;
    case SKILL_FRAME_ACTION_COND_IsStateMiscFlagTrue:
      return GetCurStateMiscFlag();
      break;
    default:
      break;
  }

  return false;
}

bool SkillTest::GetCurStateMiscFlag() const {
  if (nullptr == executingSkill_) {
    return false;
  }
  return executingSkill_->skillStates_[curSkillStateIndex_].MiscFlag();
}

void SkillTest::ExcuteSkillFrameAction(SKILL_FRAME_ACTION_TYPE actionType, const SkillFrameActionParams& params) {
  switch (actionType) {
    case SKILL_FRAME_ACTION_None:
      break;
    case SKILL_FRAME_ACTION_DeactiveSkill:
      DeActiveSkill();
      break;
    case SKILL_FRAME_ACTION_UpdateSkillState:
      ChangeSkillState(params);
      break;
    case SKILL_FRAME_ACTION_MovementJump:
      ExcuteJump(params);
      break;
    case SKILL_FRAME_ACTION_MovementDash:
      ExcuteDash(params);
      break;
    case SKILL_FRAME_ACTION_MovementStopDash:
      ExcuteDashStop(params);
      break;
    case SKILL_FRAME_ACTION_SpawnEffect:
      ExcuteSpawnEffect(params);
      break;
    case SKILL_FRAME_ACTION_FireProjectile:
      ExcuteFireProjectile(params);
      break;
    case SKILL_FRAME_ACTION_CommandExecute:
      ExcuteCommand(params);
      break;
    case SKILL_FRAME_ACTION_SetPostionOppenentPlayer:
      SetPositionOppenentPlayer(params);
      break;
    case SKILL_FRAME_ACTION_LockControlOppenentPlayer:
      LockControlOppenentPlayer(params);
      break;
    case SKILL_FRAME_ACTION_UnLockControlOppenentPlayer:
      UnLockControlOppenentPlayer(params);
      break;
    case SKILL_FRAME_ACTION_FreezeOppenentPlayer:
      FreezeOppenentPlayer(params);
      break;
    case SKILL_FRAME_ACTION_DefreezePlayers:
      DefreezePlayers(params);
      break;
    case SKILL_FRAME_ACTION_CameraShake:
      ExcuteCameraShake(params);
      break;
    case SKILL_FRAME_ACTION_FadeIn:
      ExcuteFadeIn(params);
      break;
    case SKILL_FRAME_ACTION_FadeOut:
      ExcuteFadeOut(params);
      break;
    case SKILL_FRAME_ACTION_FadeInout:
      ExcuteFadeInout(params);
      break;
    case SKILL_FRAME_ACTION_SoundPlay:
      ExcuteSoundPlay(params);
      break;
    case SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue:
      SetCurStateMiscFlagTrue(params);
      break;
    default:
      break;
  }
}

void SkillTest::DeActiveSkill() {
  pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_Idle);
  executingSkill_ = nullptr;
}

void SkillTest::ChangeSkillState(const SkillFrameActionParams& params) {
  if (nullptr == executingSkill_) {
    DeActiveSkill();
    return;
  }

  unsigned int skillStateIndex = params.changeStateIndex_;
  if (skillStateIndex >= executingSkill_->skillStates_.size()) {
    return;
  }

  curSkillStateIndex_ = skillStateIndex;

  unsigned long long animState = executingSkill_->skillStates_[curSkillStateIndex_].animState_;

  pOwnerPlayer_->UpdateAnimState(animState);
}

void SkillTest::ExcuteJump(const SkillFrameActionParams& params) {
  bool facingRight = pOwnerPlayer_->FacingRight();
  Vector jumpForce = params.jumpForce_;
  pOwnerMovementConponent_->Jump(facingRight, jumpForce);
}

void SkillTest::ExcuteDash(const SkillFrameActionParams& params) {
  bool facingRight = pOwnerPlayer_->FacingRight();
  float dashDuration = params.dashDuration_;
  float dashDistance = params.dashDistance_;

  pOwnerMovementConponent_->Dash(facingRight, dashDuration, dashDistance);
}

void SkillTest::ExcuteDashStop(const SkillFrameActionParams& params) {
  pOwnerMovementConponent_->StopDash();
}

void SkillTest::ExcuteSpawnEffect(const SkillFrameActionParams& params) {
  Level* curLevel = pOwnerPlayer_->GetLevel();
  if (nullptr == curLevel) {
    return;
  }

  EFFECT_TYPE effectType = params.effectType_;
  Vector playerPosition = pOwnerPlayer_->GetPosition();
  Vector spawnPositionOffset = params.spawnEffectPos_;

  if (pOwnerPlayer_->FacingRight()) {
    EffectManager::Instance()->SpawnEffect(curLevel, (EFTYPE_Iori_Casting_YamiBarai | EFMOD_NONE), {playerPosition.X - spawnPositionOffset.X, playerPosition.Y + spawnPositionOffset.Y});
  } else {
    EffectManager::Instance()->SpawnEffect(curLevel, (EFTYPE_Iori_Casting_YamiBarai | EFMOD_FLIPPED), {playerPosition.X + spawnPositionOffset.X, playerPosition.Y + spawnPositionOffset.Y});
  }
}

void SkillTest::ExcuteFireProjectile(const SkillFrameActionParams& params) {
  PROJECTILE_TYPE projectileType = params.projectileType_;
  pOwnerProjectileComponent_->FireProjectile(projectileType);
}

void SkillTest::ExcuteCommand(const SkillFrameActionParams& params) {
}

void SkillTest::SetPositionOppenentPlayer(const SkillFrameActionParams& params) {
}

void SkillTest::LockControlOppenentPlayer(const SkillFrameActionParams& params) {
}

void SkillTest::UnLockControlOppenentPlayer(const SkillFrameActionParams& params) {
}

void SkillTest::FreezeOppenentPlayer(const SkillFrameActionParams& params) {
}

void SkillTest::DefreezePlayers(const SkillFrameActionParams& params) {
}

void SkillTest::ExcuteCameraShake(const SkillFrameActionParams& params) {
}

void SkillTest::ExcuteFadeIn(const SkillFrameActionParams& params) {
}

void SkillTest::ExcuteFadeOut(const SkillFrameActionParams& params) {
}

void SkillTest::ExcuteFadeInout(const SkillFrameActionParams& params) {
}

void SkillTest::ExcuteSoundPlay(const SkillFrameActionParams& params) {
}

void SkillTest::SetCurStateMiscFlagTrue(const SkillFrameActionParams& params) {
  if (nullptr == executingSkill_) {
    return;
  }
  executingSkill_->skillStates_[curSkillStateIndex_].SetMiscFlag(true);
}