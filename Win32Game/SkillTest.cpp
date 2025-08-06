#include "stdafx.h"
#include "KOFPlayer.h"
#include "SkillTest.h"
#include "MovementComponent.h"

SkillTest::SkillTest()
    : pOwnerPlayer_(nullptr),
      pOwnerRenderer_(nullptr),
      pOwnerMovementConponent_(nullptr),
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
}

bool SkillTest::Initialize(KOFPlayer* pOwnerPlayer, ImageRenderer* pRenderer, MovementComponent* pMovementComponent) {
  if (nullptr == pOwnerPlayer) {
    return false;
  }
  if (nullptr == pRenderer) {
    return false;
  }
  if (nullptr == pMovementComponent) {
    return false;
  }

  pOwnerPlayer_ = pOwnerPlayer;
  pOwnerRenderer_ = pRenderer;
  pOwnerMovementConponent_ = pMovementComponent;

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
          (*pEvents)[j].evnetType_;
          (*pEvents)[j].eventParams_;
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

  unsigned long long animState = activeSkill_->animStates_[currentAnimStateIndex_].animState_;

  pOwnerPlayer_->UpdateAnimState(animState);
}

void SkillTest::ExcuteAction(SkillEventType eventType, const std::vector<int>& params) {
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
      break;
    case SkillEvent_MovementStopDash:
      break;
    case SkillEvent_SpawnEffect:
      break;
    case SkillEvent_FireProjectile:
      break;
    case SkillEvent_CommandExecute:
      break;
    case SkillEvent_SetPostionOppenentPlayer:
      break;
    case SkillEvent_LockControlOppenentPlayer:
      break;
    case SkillEvent_UnLockControlOppenentPlayer:
      break;
    case SkillEvent_FreezeOppenentPlayer:
      break;
    case SkillEvent_DefreezePlayers:
      break;
    case SkillEvent_CameraShake:
      break;
    case SkillEvent_FadeIn:
      break;
    case SkillEvent_FadeOut:
      break;
    case SkillEvent_FadeInout:
      break;
    case SkillEvent_SoundPlay:
      break;
    case SkillEvent_SetMiscTempTrue:
      break;
    default:
      break;
  }
}

void SkillTest::DeActiveSkill() {
  pOwnerPlayer_->UpdateAnimState(PLAYER_ANIMTYPE_Idle);

  activeSkill_ = nullptr;

  currentAnimStateIndex_ = 0;
}

void SkillTest::ChangeSkillState(const std::vector<int>& params) {
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
}

void SkillTest::ExcuteJump(const std::vector<int>& params) {
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

bool SkillTest::CheckEventCondition(SkillEventConditionType eventCondition) const {
  switch (eventCondition) {
    case SkillEventCondition_None:
      return true;
      break;
    case SkillEventCondition_AnimationEnd:
      return pOwnerRenderer_->IsAnimationEnd();
      break;
    case SkillEventCondition_CheckInputDownA:
      return true;
      break;
    case SkillEventCondition_CheckInputDownB:
      return true;
      break;
    case SkillEventCondition_CheckInputDownC:
      return true;
      break;
    case SkillEventCondition_CheckInputDownD:
      return true;
      break;
    case SkillEventCondition_HasAttackCollition:
      return true;
      break;
    case SkillEventCondition_MiscTempTrue:
      return miscTemp_;
      break;
    default:
      break;
  }

  return false;
}
