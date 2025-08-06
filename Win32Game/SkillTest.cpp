#include "stdafx.h"
#include "KOFPlayer.h"
#include "SkillTest.h"
#include "MovementComponent.h"
#include "InputController.h"

SkillTest::SkillTest()
    : pOwnerPlayer_(nullptr),
      pOwnerRenderer_(nullptr),
      pOwnerMovementConponent_(nullptr),
      pOwnerInputController_(nullptr),
      pOwnerAttackCollision_(nullptr),
      activeSkill_(nullptr),
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
    CollisionComponent* pAttackCollision) {
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

  pOwnerPlayer_ = pOwnerPlayer;
  pOwnerRenderer_ = pRenderer;
  pOwnerMovementConponent_ = pMovementComponent;
  pOwnerInputController_ = pInputController;
  pOwnerAttackCollision_ = pAttackCollision;

  return skillTable_.Initialize(8, 8);
}

bool SkillTest::RegistSkill(Skill skill) {
  Skill* pFind;
  if (0 != skillTable_.Select((void**)&pFind, 1, &skill.skillTag_, 8)) {
    return false;
  }

  Skill* pInfo = new Skill;
  pInfo->skillTag_ = skill.skillTag_;
  pInfo->animStates_ = skill.animStates_;
  const void* c = &pInfo->skillTag_;
  pInfo->searchHandle_ = skillTable_.Insert(pInfo, &pInfo->skillTag_, 8);

  return nullptr != pInfo->searchHandle_;
}

void SkillTest::UpdateSkill() {
  if (nullptr == activeSkill_) {
    return;
  }

  if (true == pOwnerRenderer_->IsAnimationEnd())
  {
    DeActiveSkill();
    return;
  }

  SkillState* pCurState = &activeSkill_->animStates_[currentAnimStateIndex_];

  std::vector<SkillFrame>* pCurSkillFrame = &pCurState->frames_;

  unsigned long long curImageIndex = pOwnerRenderer_->GetImageIndex();

  for (int i = 0; i < pCurSkillFrame->size(); ++i) {
    unsigned long long startIndex = (*pCurSkillFrame)[i].startIndex_;
    unsigned long long endIndex = (*pCurSkillFrame)[i].endIndex_;

    if (curImageIndex >= startIndex && curImageIndex <= endIndex) {
      std::vector<SkillEvent>* pEvents = &(*pCurSkillFrame)[i].events;
      for (int j = 0; j < pEvents->size(); ++j) {
        std::vector<SkillEventConditionType>* conditions = &(*pEvents)[j].conditionTypes_;
        bool b = true;
        for (int k = 0; k < conditions->size(); ++k) {
          SkillEventConditionType conditionType = (*conditions)[k];
          bool ret = CheckEventCondition(conditionType);
          if (false == ret) {
            b = false;
            break;
          }
        }
        if (true == b) {
          ExcuteAction((*pEvents)[j].evnetType_, (*pEvents)[j].eventParams_);
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

  activeSkill_ = pInfo;

  currentAnimStateIndex_ = 0;

  miscTemp_ = false;

  unsigned long long animState = activeSkill_->animStates_[currentAnimStateIndex_].animState_;

  pOwnerPlayer_->UpdateAnimState(animState);
}

void SkillTest::ExcuteAction(SkillEventType eventType, const std::vector<float>& params) {
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
      ExcuteSpawEffect(params);
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

  currentAnimStateIndex_ = 0;

  miscTemp_ = false;
}

void SkillTest::ChangeSkillState(const std::vector<float>& params) {
  if (nullptr == activeSkill_) {
    DeActiveSkill();
    return;
  }

  if (1 < params.size()) {
    return;
  }

  int skillStateIndex = params[0];

  if (skillStateIndex >= activeSkill_->animStates_.size()) {
    return;
  }

  currentAnimStateIndex_ = skillStateIndex;

  unsigned long long animState = activeSkill_->animStates_[currentAnimStateIndex_].animState_;

  pOwnerPlayer_->UpdateAnimState(animState);

  miscTemp_ = false;
}

void SkillTest::ExcuteJump(const std::vector<float>& params) {
  if (2 < params.size()) {
    DeActiveSkill();
    return;
  }

  bool facingRight = pOwnerPlayer_->FacingRight();
  Vector jumpForce;
  jumpForce.X = params[0];
  jumpForce.Y = params[1];
  pOwnerMovementConponent_->Jump(facingRight, jumpForce);
}

void SkillTest::ExcuteDash(const std::vector<float>& params) {
  if (2 < params.size()) {
    DeActiveSkill();
    return;
  }
  bool facingRight = pOwnerPlayer_->FacingRight();
  float dashDuration = params[0];
  float dashDistance = params[1];

  pOwnerMovementConponent_->Dash(facingRight, dashDuration, dashDistance);
}

void SkillTest::ExcuteDashStop(const std::vector<float>& params) {
  pOwnerMovementConponent_->StopDash();
}

void SkillTest::ExcuteSpawEffect(const std::vector<float>& params) {
}

void SkillTest::ExcuteFireProjectile(const std::vector<float>& params) {
}

void SkillTest::ExcuteCommand(const std::vector<float>& params) {
}

void SkillTest::SetPositionOppenentPlayer(const std::vector<float>& params) {
}

void SkillTest::LockControlOppenentPlayer(const std::vector<float>& params) {
}

void SkillTest::UnLockControlOppenentPlayer(const std::vector<float>& params) {
}

void SkillTest::FreezeOppenentPlayer(const std::vector<float>& params) {
}

void SkillTest::DefreezePlayers(const std::vector<float>& params) {
}

void SkillTest::ExcuteCameraShake(const std::vector<float>& params) {
}

void SkillTest::ExcuteFadeIn(const std::vector<float>& params) {
}

void SkillTest::ExcuteFadeOut(const std::vector<float>& params) {
}

void SkillTest::ExcuteFadeInout(const std::vector<float>& params) {
}

void SkillTest::ExcuteSoundPlay(const std::vector<float>& params) {
}

void SkillTest::ExcuteSetMiscTempTrue(const std::vector<float>& params) {
  miscTemp_ = true;
}

bool SkillTest::CheckEventCondition(SkillEventConditionType eventCondition) const {
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