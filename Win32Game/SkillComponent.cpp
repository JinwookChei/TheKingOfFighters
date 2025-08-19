#include "stdafx.h"
#include "KOFPlayer.h"
#include "SkillComponent.h"
#include "MovementComponent.h"
#include "InputController.h"
#include "ProjectileComponent.h"
#include "MPComponent.h"
#include "ScreenMask.h"
#include "KOFLevel.h"
#include "CameraTarget.h"
#include "ActorFreezeManager.h"
#include "RestrictionComponent.h"
#include "RestrictionManager.h"

SkillComponent::SkillComponent()
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

SkillComponent::~SkillComponent() {
  for (HashTableIterator iter = skillTable_.begin(); iter != skillTable_.end();) {
    Skill* pDel = (Skill*)*iter;
    iter = skillTable_.erase(iter);

    delete pDel;
  }

  skillTable_.Cleanup();
}

void SkillComponent::BeginPlay() {
}

void SkillComponent::Tick(unsigned long long deltaTick) {
  UpdateSkill();
}

bool SkillComponent::Initialize(
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

bool SkillComponent::RegistSkill(Skill skill) {
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

void SkillComponent::UpdateSkill() {
  if (nullptr == executingSkill_) {
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
        std::vector<SkillFrameActionConditionData>* conditionDatas = &(*pActions)[j].conditionDatas_;
        bool conditionFlag = true;
        for (int k = 0; k < conditionDatas->size(); ++k) {
          SKILL_FRAME_ACTION_CONDITION_TYPE conditionType = (*conditionDatas)[k].conditionType_;
          SkillFrameActionConditionParams condtionParams = (*conditionDatas)[k].conditionParams_;
          bool ret = CheckFrameActionCondition(conditionType, condtionParams);
          if (false == ret) {
            conditionFlag = false;
            break;
          }
        }
        if (true == conditionFlag) {
          std::vector<SkillFrameActionData>* actionDatas = &(*pActions)[j].actionDatas_;
          for (int l = 0; l < actionDatas->size(); ++l) {
            ExcuteSkillFrameAction((*actionDatas)[l].actionType_, (*actionDatas)[l].actionParams_);
          }
          (*pActions)[j].SetHasExcuted(true);
        }
      }
    }
  }

  if (true == pOwnerRenderer_->IsAnimationEnd()) {
    DeActiveSkill();
    return;
  }
}

void SkillComponent::ExecuteSkill(unsigned long long skillTag) {
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

  SKILL_CASTING_ACTION_TYPE castAction = pInfo->castAction_;
  ExcuteCastingAction(castAction);

  ResetStateMiscFlags(pInfo);

  ResetEventExcutedFlags(pInfo);

  executingSkill_ = pInfo;

  curSkillStateIndex_ = 0;

  unsigned long long animState = executingSkill_->skillStates_[curSkillStateIndex_].animState_;

  pOwnerPlayer_->UpdateAnimState(animState);
}

bool SkillComponent::IsSkillExecuting() {
  return nullptr != executingSkill_;
}

void SkillComponent::ResetEventExcutedFlags(Skill* pSkill) {
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

void SkillComponent::ResetStateMiscFlags(Skill* pSkill) {
  if (nullptr == pSkill) {
    return;
  }
  for (int i = 0; i < pSkill->skillStates_.size(); ++i) {
    pSkill->skillStates_[i].SetMiscFlag(false);
  }
}

bool SkillComponent::CheckCastingCondition(SKILL_CASTING_CONDITION_TYPE castCondition) {
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

bool SkillComponent::HasSkillPoint() const {
  return 1 <= pOwnerMPComponent_->SkillPoint();
}

void SkillComponent::ExcuteCastingAction(SKILL_CASTING_ACTION_TYPE castAction) {
  switch (castAction) {
    case SKILL_CAST_ACTION_None:
      break;
    case SKILL_CAST_ACTION_ReduceSkillPoint:
      ReduceSkillPoint();
      break;
    default:
      break;
  }
}

void SkillComponent::ReduceSkillPoint() {
  if (nullptr == pOwnerMPComponent_) {
    return;
  }
  pOwnerMPComponent_->ReduceSkillPoint();
}

bool SkillComponent::CheckFrameActionCondition(SKILL_FRAME_ACTION_CONDITION_TYPE actionCondition, const SkillFrameActionConditionParams& params) const {
  switch (actionCondition) {
    case SKILL_FRAME_ACTION_COND_None:
      return true;
      break;
    case SKILL_FRAME_ACTION_COND_AnimationEnd:
      return pOwnerRenderer_->IsAnimationEnd();
      break;
    case SKILL_FRAME_ACTION_COND_CheckInputDownA:
      return pOwnerInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_A});
      break;
    case SKILL_FRAME_ACTION_COND_CheckInputDownB:
      return pOwnerInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_B});
      break;
    case SKILL_FRAME_ACTION_COND_CheckInputDownC:
      return pOwnerInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_C});
      break;
    case SKILL_FRAME_ACTION_COND_CheckInputDownD:
      return pOwnerInputController_->IsContainInputBitSet(KEY_STATE_Down, {KEY_D});
      break;
    case SKILL_FRAME_ACTION_COND_HasAttackCollition:
      return pOwnerAttackCollision_->HasHit();
      break;
    case SKILL_FRAME_ACTION_COND_IsStateMiscFlagTrue:
      return GetCurStateMiscFlag();
      break;
    case SKILL_FRAME_ACTION_COND_IsOpponentWithinDistanceThresHold:
      return IsOpponentWithinDistanceThresHold(params);
      break;
    default:
      break;
  }

  return false;
}

bool SkillComponent::GetCurStateMiscFlag() const {
  if (nullptr == executingSkill_) {
    return false;
  }
  return executingSkill_->skillStates_[curSkillStateIndex_].MiscFlag();
}

bool SkillComponent::IsOpponentWithinDistanceThresHold(const SkillFrameActionConditionParams& params) const {
  float opponentDistanceThreshold = params.opponentDistanceThreshold;

  Vector ownerPosition = pOwnerPlayer_->GetPosition();

  Vector opponetPosition = pOwnerPlayer_->GetOpponentPlayer()->GetPosition();

  return opponentDistanceThreshold > std::fabs(ownerPosition.X - opponetPosition.X);
}

void SkillComponent::ExcuteSkillFrameAction(SKILL_FRAME_ACTION_TYPE actionType, const SkillFrameActionParams& params) {
  switch (actionType) {
    case SKILL_FRAME_ACTION_None:
      break;
    case SKILL_FRAME_ACTION_DeactiveSkill:
      DeActiveSkill();
      break;
    case SKILL_FRAME_ACTION_ChangeSkillState:
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
    case SKILL_FRAME_ACTION_ChangeOpponentAnimState:
      ChangeOpponentAnimState(params);
      break;
    case SKILL_FRAME_ACTION_SetPostionOpponentPlayer:
      SetPositionOpponentPlayer(params);
      break;

    case SKILL_FRAME_ACTION_InflictRestrictionOpponentPlayer:
      InflictRestrictionOpponentPlayer(params);
      break;
    case SKILL_FRAME_ACTION_ReleaseRestrictionOpponentPlayer:
      ReleaseRestrictionOpponentPlayer(params);
      break;
    case SKILL_FRAME_ACTION_ClearRestrictionOpponentPlayer:
      ClearRestrictionOpponentPlayer(params);
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
    case SKILL_FRAME_ACTION_FadeInOut:
      ExcuteFadeInOut(params);
      break;
    case SKILL_FRAME_ACTION_SoundPlay:
      ExcuteSoundPlay(params);
      break;
    case SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue:
      SetCurStateMiscFlagTrue(params);
      break;
    case SKILL_FRAME_ACTION_ExecuteNextSkill:
      ExecuteNextSkill(params);
      break;
    default:
      break;
  }
}

void SkillComponent::DeActiveSkill() {
  pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_Idle);
  executingSkill_ = nullptr;
}

void SkillComponent::ChangeSkillState(const SkillFrameActionParams& params) {
  if (nullptr == executingSkill_) {
    DeActiveSkill();
    return;
  }

  unsigned int skillStateIndex = params.ChangeOpponentAnimState.opponentAnimState_;
  if (skillStateIndex >= executingSkill_->skillStates_.size()) {
    return;
  }

  curSkillStateIndex_ = skillStateIndex;

  unsigned long long animState = executingSkill_->skillStates_[curSkillStateIndex_].animState_;

  pOwnerPlayer_->UpdateAnimState(animState);
}

void SkillComponent::ExcuteJump(const SkillFrameActionParams& params) {
  bool facingRight = pOwnerPlayer_->FacingRight();
  Vector jumpForce = params.MovementJump.jumpForce_;
  pOwnerMovementConponent_->Jump(facingRight, jumpForce);
}

void SkillComponent::ExcuteDash(const SkillFrameActionParams& params) {
  bool facingRight = pOwnerPlayer_->FacingRight();
  float dashDuration = params.MovementDash.dashDuration_;
  float dashDistance = params.MovementDash.dashDistance_;

  pOwnerMovementConponent_->Dash(facingRight, dashDuration, dashDistance);
}

void SkillComponent::ExcuteDashStop(const SkillFrameActionParams& params) {
  pOwnerMovementConponent_->StopDash();
}

void SkillComponent::ExcuteSpawnEffect(const SkillFrameActionParams& params) {
  Level* curLevel = pOwnerPlayer_->GetLevel();
  if (nullptr == curLevel) {
    return;
  }

  EFFECT_TYPE effectType = params.SpawnEffect.effectType_;
  Vector playerPosition = pOwnerPlayer_->GetPosition();
  Vector spawnPositionOffset = params.SpawnEffect.spawnEffectPos_;

  if (pOwnerPlayer_->FacingRight()) {
    EffectManager::Instance()->SpawnEffect(curLevel, (effectType | EFMOD_NONE), {playerPosition.X + spawnPositionOffset.X, playerPosition.Y + spawnPositionOffset.Y});
  } else {
    EffectManager::Instance()->SpawnEffect(curLevel, (effectType | EFMOD_FLIPPED), {playerPosition.X - spawnPositionOffset.X, playerPosition.Y + spawnPositionOffset.Y});
  }
}

void SkillComponent::ExcuteFireProjectile(const SkillFrameActionParams& params) {
  PROJECTILE_TYPE projectileType = params.FireProjectile.projectileType_;
  pOwnerProjectileComponent_->FireProjectile(projectileType);
}

void SkillComponent::ExcuteCommand(const SkillFrameActionParams& params) {
}

void SkillComponent::ChangeOpponentAnimState(const SkillFrameActionParams& params) {
  if (nullptr == pOwnerPlayer_) {
    return;
  }
  KOFPlayer* opponentPlayer = pOwnerPlayer_->GetOpponentPlayer();
  if (nullptr == opponentPlayer) {
    return;
  }

  unsigned long long opponentAnimState = params.ChangeOpponentAnimState.opponentAnimState_;

  opponentPlayer->UpdateAnimState(opponentAnimState);
}

void SkillComponent::SetPositionOpponentPlayer(const SkillFrameActionParams& params) {
  if (nullptr == pOwnerPlayer_) {
    return;
  }
  KOFPlayer* opponentPlayer = pOwnerPlayer_->GetOpponentPlayer();
  if (nullptr == opponentPlayer) {
    return;
  }

  const Vector& opponentForcedPos = params.SetPostionOpponentPlayer.opponentForcedPosition_;

  const Vector& ownerPosition = pOwnerPlayer_->GetPosition();

  const Vector& opponentPosition = ownerPosition + Vector{opponentForcedPos.X * pOwnerPlayer_->FacingRightFlag(), opponentForcedPos.Y};

  opponentPlayer->SetPosition(opponentPosition);
}

void SkillComponent::InflictRestrictionOpponentPlayer(const SkillFrameActionParams& params) {
  if (nullptr == pOwnerPlayer_) {
    return;
  }
  KOFPlayer* opponentPlayer = pOwnerPlayer_->GetOpponentPlayer();
  if (nullptr == opponentPlayer) {
    return;
  }
  Level* pLevel = pOwnerPlayer_->GetLevel();
  if (nullptr == pLevel) {
    return;
  }
  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }

  RestrictionManager* pRestrictionManager = pKOFLevel->GetRestrictionManager();
  if (nullptr == pRestrictionManager) {
    return;
  }

  bool isInfinite = params.Restriction.isInfinite_;
  unsigned long long restrictDuration = params.Restriction.restrictDuration_;
  const std::bitset<PR_Max>& restrictions = params.Restriction.restrictions_;

  pRestrictionManager->ApplyExternalRestrict(opponentPlayer->ActorId(), restrictions, isInfinite, restrictDuration);
}

void SkillComponent::ReleaseRestrictionOpponentPlayer(const SkillFrameActionParams& params) {
  if (nullptr == pOwnerPlayer_) {
    return;
  }
  KOFPlayer* opponentPlayer = pOwnerPlayer_->GetOpponentPlayer();
  if (nullptr == opponentPlayer) {
    return;
  }
  Level* pLevel = pOwnerPlayer_->GetLevel();
  if (nullptr == pLevel) {
    return;
  }
  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }

  RestrictionManager* pRestrictionManager = pKOFLevel->GetRestrictionManager();
  if (nullptr == pRestrictionManager) {
    return;
  }

  //std::vector<PLAYER_RESTRICT_TYPE> restrictions = params.Restriction.restrictions_;
  const std::bitset<PR_Max>& restrictions = params.Restriction.restrictions_;

  pRestrictionManager->ReleaseExternalRestrict(opponentPlayer->ActorId(), restrictions);
}

void SkillComponent::ClearRestrictionOpponentPlayer(const SkillFrameActionParams& params) {
  if (nullptr == pOwnerPlayer_) {
    return;
  }
  KOFPlayer* opponentPlayer = pOwnerPlayer_->GetOpponentPlayer();
  if (nullptr == opponentPlayer) {
    return;
  }
  Level* pLevel = pOwnerPlayer_->GetLevel();
  if (nullptr == pLevel) {
    return;
  }
  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }

  RestrictionManager* pRestrictionManager = pKOFLevel->GetRestrictionManager();
  if (nullptr == pRestrictionManager) {
    return;
  }

  pRestrictionManager->ClearExternalRestrict(opponentPlayer->ActorId());
}

void SkillComponent::ExcuteCameraShake(const SkillFrameActionParams& params) {
  if (nullptr == pOwnerPlayer_) {
    return;
  }

  Level* pLevel = pOwnerPlayer_->GetLevel();
  if (nullptr == pLevel) {
    return;
  }
  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }
  CameraTarget* pCameraTarget = pKOFLevel->GetCameraTarget();
  if (nullptr == pCameraTarget) {
    return;
  }
  unsigned long long cameraShakeDuration = params.CameraShake.cameraShakeDuration_;

  pCameraTarget->OnCameraShake(cameraShakeDuration);
}

void SkillComponent::ExcuteFadeIn(const SkillFrameActionParams& params) {
  if (nullptr == pOwnerPlayer_) {
    return;
  }

  Level* pLevel = pOwnerPlayer_->GetLevel();
  if (nullptr == pLevel) {
    return;
  }
  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }

  ScreenMask* pBackGroundMask = pKOFLevel->GetBackGroundMask();
  if (nullptr == pBackGroundMask) {
    return;
  }

  unsigned long long fadeDuration = params.Fade.fadeDuration_;

  pBackGroundMask->FadeIn(fadeDuration);
}

void SkillComponent::ExcuteFadeOut(const SkillFrameActionParams& params) {
  if (nullptr == pOwnerPlayer_) {
    return;
  }

  Level* pLevel = pOwnerPlayer_->GetLevel();
  if (nullptr == pLevel) {
    return;
  }
  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }

  ScreenMask* pBackGroundMask = pKOFLevel->GetBackGroundMask();
  if (nullptr == pBackGroundMask) {
    return;
  }

  IMAGE_TYPE fadeImageType = params.Fade.fadeImageType_;

  unsigned long long fadeDuration = params.Fade.fadeDuration_;

  pBackGroundMask->FadeOut(fadeImageType, fadeDuration);
}

void SkillComponent::ExcuteFadeInOut(const SkillFrameActionParams& params) {
  if (nullptr == pOwnerPlayer_) {
    return;
  }

  Level* pLevel = pOwnerPlayer_->GetLevel();
  if (nullptr == pLevel) {
    return;
  }
  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }

  ScreenMask* pBackGroundMask = pKOFLevel->GetBackGroundMask();
  if (nullptr == pBackGroundMask) {
    return;
  }

  IMAGE_TYPE fadeImageType = params.Fade.fadeImageType_;

  unsigned long long fadeDuration = params.Fade.fadeDuration_;

  pBackGroundMask->FadeInOut(fadeImageType, fadeDuration);
}

void SkillComponent::ExcuteSoundPlay(const SkillFrameActionParams& params) {
  SOUND_TYPE soundType_ = params.SoundPlay.soundType_;

  SoundManager::Instance()->SoundPlay(soundType_);
}

void SkillComponent::SetCurStateMiscFlagTrue(const SkillFrameActionParams& params) {
  if (nullptr == executingSkill_) {
    return;
  }
  executingSkill_->skillStates_[curSkillStateIndex_].SetMiscFlag(true);
}

void SkillComponent::ExecuteNextSkill(const SkillFrameActionParams& params) {
  ExecuteSkill(params.NextSkill.skillTag_);
}
