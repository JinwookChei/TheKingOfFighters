#include "stdafx.h"
#include "KOFPlayer.h"
#include "SkillTest.h"
#include "MovementComponent.h"
#include "InputController.h"
#include "ProjectileComponent.h"

SkillTest::SkillTest()
    : pOwnerPlayer_(nullptr),
      pOwnerRenderer_(nullptr),
      pOwnerMovementConponent_(nullptr),
      pOwnerInputController_(nullptr),
      pOwnerAttackCollision_(nullptr),
      pOwnerProjectileComponent_(nullptr),
      activeSkill_(nullptr),
      curSkillStateIndex_(0),
      miscTemp_(false) {
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
    ProjectileComponent* pProjectileComponent) {
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

  pOwnerPlayer_ = pOwnerPlayer;
  pOwnerRenderer_ = pRenderer;
  pOwnerMovementConponent_ = pMovementComponent;
  pOwnerInputController_ = pInputController;
  pOwnerAttackCollision_ = pAttackCollision;
  pOwnerProjectileComponent_ = pProjectileComponent;

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
  const void* c = &pInfo->skillTag_;
  pInfo->searchHandle_ = skillTable_.Insert(pInfo, &pInfo->skillTag_, 8);

  return nullptr != pInfo->searchHandle_;
}

void SkillTest::UpdateSkill() {
  if (nullptr == activeSkill_) {
    return;
  }

  if (true == pOwnerRenderer_->IsAnimationEnd()) {
    DeActiveSkill();
    return;
  }

  SkillState* pCurState = &activeSkill_->skillStates_[curSkillStateIndex_];

  std::vector<SkillFrame>* pCurSkillFrame = &pCurState->frames_;

  unsigned long long curImageIndex = pOwnerRenderer_->GetImageIndex();

  for (int i = 0; i < pCurSkillFrame->size(); ++i) {
    unsigned long long startIndex = (*pCurSkillFrame)[i].startIndex_;
    unsigned long long endIndex = (*pCurSkillFrame)[i].endIndex_;

    if (curImageIndex >= startIndex && curImageIndex <= endIndex) {
      std::vector<SkillEvent>* pEvents = &(*pCurSkillFrame)[i].events;
      for (int j = 0; j < pEvents->size(); ++j) {
        if (true == (*pEvents)[j].hasExecuted_) {
          continue;
        }
        std::vector<SKILL_EVENT_CONDITION_TYPE>* conditions = &(*pEvents)[j].conditionTypes_;
        bool conditionFlag = true;
        for (int k = 0; k < conditions->size(); ++k) {
          SKILL_EVENT_CONDITION_TYPE conditionType = (*conditions)[k];
          bool ret = CheckEventCondition(conditionType);
          if (false == ret) {
            conditionFlag = false;
            break;
          }
        }
        if (true == conditionFlag) {
          ExcuteAction((*pEvents)[j].evnetType_, (*pEvents)[j].eventParams_);
          (*pEvents)[j].hasExecuted_ = true;
        }
      }
    }
  }
}

void SkillTest::ActiveSkill(unsigned long long skillTag) {
  Skill* pInfo;
  if (0 == skillTable_.Select((void**)&pInfo, 1, &skillTag, 8)) {
    return;
  }

  ResetEventExcutedFlags(pInfo);

  activeSkill_ = pInfo;

  curSkillStateIndex_ = 0;

  miscTemp_ = false;

  unsigned long long animState = activeSkill_->skillStates_[curSkillStateIndex_].animState_;

  pOwnerPlayer_->UpdateAnimState(animState);
}

void SkillTest::ResetEventExcutedFlags(Skill* pSkill) {
  if (nullptr == pSkill) {
    return;
  }
  for (int i = 0; i < pSkill->skillStates_.size(); ++i) {
    for (int j = 0; j < pSkill->skillStates_[i].frames_.size(); ++j) {
      for (int k = 0; k < pSkill->skillStates_[i].frames_[j].events.size(); ++k) {
        pSkill->skillStates_[i].frames_[j].events[k].ResetHasExecutedFlag();
      }
    }
  }
}

void SkillTest::ExcuteAction(SKILL_EVENT_TYPE eventType, const SkillEvnetParams& params) {
  switch (eventType) {
    case SkillEvent_None:
      break;
    case SkillEvent_DeactiveSkill:
      DeActiveSkill();
      break;
    case SkillEvent_UpdateSkillState:
      ChangeSkillState(params);
      break;
    case SkillEvent_MovementJump:
      ExcuteJump(params);
      break;
    case SkillEvent_MovementDash:
      ExcuteDash(params);
      break;
    case SkillEvent_MovementStopDash:
      ExcuteDashStop(params);
      break;
    case SkillEvent_SpawnEffect:
      ExcuteSpawnEffect(params);
      break;
    case SkillEvent_FireProjectile:
      ExcuteFireProjectile(params);
      break;
    case SkillEvent_CommandExecute:
      ExcuteCommand(params);
      break;
    case SkillEvent_SetPostionOppenentPlayer:
      SetPositionOppenentPlayer(params);
      break;
    case SkillEvent_LockControlOppenentPlayer:
      LockControlOppenentPlayer(params);
      break;
    case SkillEvent_UnLockControlOppenentPlayer:
      UnLockControlOppenentPlayer(params);
      break;
    case SkillEvent_FreezeOppenentPlayer:
      FreezeOppenentPlayer(params);
      break;
    case SkillEvent_DefreezePlayers:
      DefreezePlayers(params);
      break;
    case SkillEvent_CameraShake:
      ExcuteCameraShake(params);
      break;
    case SkillEvent_FadeIn:
      ExcuteFadeIn(params);
      break;
    case SkillEvent_FadeOut:
      ExcuteFadeOut(params);
      break;
    case SkillEvent_FadeInout:
      ExcuteFadeInout(params);
      break;
    case SkillEvent_SoundPlay:
      ExcuteSoundPlay(params);
      break;
    case SkillEvent_SetMiscTempTrue:
      ExcuteSetMiscTempTrue(params);
      break;
    default:
      break;
  }
}

void SkillTest::DeActiveSkill() {
  pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_Idle);

  activeSkill_ = nullptr;

  curSkillStateIndex_ = 0;

  miscTemp_ = false;
}

void SkillTest::ChangeSkillState(const SkillEvnetParams& params) {
  if (nullptr == activeSkill_) {
    DeActiveSkill();
    return;
  }

  unsigned int skillStateIndex = params.changeStateIndex_;
  if (skillStateIndex >= activeSkill_->skillStates_.size()) {
    return;
  }

  curSkillStateIndex_ = skillStateIndex;

  unsigned long long animState = activeSkill_->skillStates_[curSkillStateIndex_].animState_;

  pOwnerPlayer_->UpdateAnimState(animState);

  miscTemp_ = false;
}

void SkillTest::ExcuteJump(const SkillEvnetParams& params) {
  bool facingRight = pOwnerPlayer_->FacingRight();
  Vector jumpForce = params.jumpForce_;
  pOwnerMovementConponent_->Jump(facingRight, jumpForce);
}

void SkillTest::ExcuteDash(const SkillEvnetParams& params) {
  bool facingRight = pOwnerPlayer_->FacingRight();
  float dashDuration = params.dashDuration_;
  float dashDistance = params.dashDistance_;

  pOwnerMovementConponent_->Dash(facingRight, dashDuration, dashDistance);
}

void SkillTest::ExcuteDashStop(const SkillEvnetParams& params) {
  pOwnerMovementConponent_->StopDash();
}

void SkillTest::ExcuteSpawnEffect(const SkillEvnetParams& params) {
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

void SkillTest::ExcuteFireProjectile(const SkillEvnetParams& params) {
  PROJECTILE_TYPE projectileType = params.projectileType_;
  pOwnerProjectileComponent_->FireProjectile(projectileType);
}

void SkillTest::ExcuteCommand(const SkillEvnetParams& params) {
}

void SkillTest::SetPositionOppenentPlayer(const SkillEvnetParams& params) {
}

void SkillTest::LockControlOppenentPlayer(const SkillEvnetParams& params) {
}

void SkillTest::UnLockControlOppenentPlayer(const SkillEvnetParams& params) {
}

void SkillTest::FreezeOppenentPlayer(const SkillEvnetParams& params) {
}

void SkillTest::DefreezePlayers(const SkillEvnetParams& params) {
}

void SkillTest::ExcuteCameraShake(const SkillEvnetParams& params) {
}

void SkillTest::ExcuteFadeIn(const SkillEvnetParams& params) {
}

void SkillTest::ExcuteFadeOut(const SkillEvnetParams& params) {
}

void SkillTest::ExcuteFadeInout(const SkillEvnetParams& params) {
}

void SkillTest::ExcuteSoundPlay(const SkillEvnetParams& params) {
}

void SkillTest::ExcuteSetMiscTempTrue(const SkillEvnetParams& params) {
  miscTemp_ = true;
}

bool SkillTest::CheckEventCondition(SKILL_EVENT_CONDITION_TYPE eventCondition) const {
  switch (eventCondition) {
    case SkillEventCondition_None:
      return true;
      break;
    case SkillEventCondition_AnimationEnd:
      return pOwnerRenderer_->IsAnimationEnd();
      break;
    case SkillEventCondition_CheckInputDownA:
      return pOwnerInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_A});
      break;
    case SkillEventCondition_CheckInputDownB:
      return pOwnerInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_B});
      break;
    case SkillEventCondition_CheckInputDownC:
      return pOwnerInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_C});
      break;
    case SkillEventCondition_CheckInputDownD:
      return pOwnerInputController_->IsContainInputBitSet(KEY_STATE_Press, {KEY_D});
      break;
    case SkillEventCondition_HasAttackCollition:
      return pOwnerAttackCollision_->HasHit();
      break;
    case SkillEventCondition_MiscTempTrue:
      return GetMiscTemp();
      break;
    default:
      break;
  }

  return false;
}

bool SkillTest::GetMiscTemp() const {
  return miscTemp_;
}