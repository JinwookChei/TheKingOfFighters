#include "stdafx.h"
#include "ActorFreezeManager.h"
#include "AnimationHandler.h"
#include "CommandComponent.h"
#include "InputController.h"
#include "CommandHandler.h"
#include "SkillComponent.h"
#include "ProjectileComponent.h"
#include "MovementComponent.h"
#include "StateComponent.h"
#include "RestrictionComponent.h"
#include "RestrictionManager.h"
#include "AttackTable.h"
#include "SoundTable.h"
#include "HealthComponent.h"
#include "MPComponent.h"
#include "GhostEffect.h"
#include "CollisionBox.h"
#include "KOFPlayer.h"
#include "KOFLevel.h"

KOFPlayer::KOFPlayer()
    : pInputController_(nullptr),
      pRender_(nullptr),
      pAnimationHandler_(nullptr),
      pUI_(nullptr),
      pMovementComponent_(nullptr),
      pSoundTable_(nullptr),
      pAttackTable_(nullptr),
      pHealthComponent_(nullptr),
      pMPComponent_(nullptr),
      pStateComponent_(nullptr),
      pRestrictionComponent_(nullptr),
      pHitBoxTop_(nullptr),
      pHitBoxBottom_(nullptr),
      pAttackBox_(nullptr),
      pPushBox_(nullptr),
      pGrabBox_(nullptr),
      pSkillComponent_(nullptr),
      pCommandComponent_(nullptr),
      pCommandHandler_(nullptr),
      pProjectileComponent_(nullptr),
      pGhostEffect_(nullptr),
      characterScale_({0.0f, 0.0f}),
      isPlayer1_(true),
      isPlayerOnLeft_(true),
      isFacingRight_(true),
      isAtMapEdge_(false),
      pOpponentPlayer_(nullptr),
      skillTest_(nullptr) {
}

KOFPlayer::~KOFPlayer() {
  Level* pLevel = GetLevel();
  if (nullptr == pLevel) {
    return;
  }
  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }
}

void KOFPlayer::BeginPlay() {

}

void KOFPlayer::Tick(unsigned long long deltaTick) {
  UpdateCollisionBoundScale();

  CheckPushCollision();


  if (true == pStateComponent_->ContainPlayerState({PS_Attack})) {
    UpdateAttack();
  }

  pInputController_->UpdateCommand();

  
  if (true == pRestrictionComponent_->CanExecuteCommand()) {
    pCommandComponent_->ExcuteTask();
  }
  
  pInputController_->ResetInputBitSet();

  pInputController_->UpdateInput();

  if (true == pRestrictionComponent_->CanInput()) {
    CompareInputBitset();
  }

  if (pProjectileComponent_->GetActiveProjectilesCount() > 0) {
    pStateComponent_->AddState({PS_Attack});
  }
}

void KOFPlayer::Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) {
  SetPosition(position);
  SetUseCameraposition(useCameraPosition);
  isPlayer1_ = isPlayer1;

  // RENDERER
  pRender_ = CreateImageRenderFIFO();
  pRender_->SetImageRenderType(ImageRenderType::Bottom);
  pRender_->SetLocalScale({4.2f, 4.2f});
  pRender_->SetAlpha(1.0f);

  // UI
  pUI_ = CreateImageRenderFIFO();
  pUI_->SetImageRenderType(ImageRenderType::Center);
  pUI_->SetLocalScale({3.0f, 3.0f});
  pUI_->SetPosition({0.0f, -510.0f});
  pUI_->SetTransparentColor({0, 0, 0, 0});
  IFileImage* youUiPlayer = nullptr;
  youUiPlayer = ImgManager::GetIntance()->GetImg(IMGTYPE_PlayerLabel);
  if (isPlayer1) {
    pUI_->SetImage(youUiPlayer, 0);
  } else {
    pUI_->SetImage(youUiPlayer, 2);
  }

  // SOUND
  pSoundTable_ = CreateComponent<SoundTable>();
  if (false == pSoundTable_->Initailize()) {
    return;
  }

  // ATTACK
  pAttackTable_ = CreateComponent<AttackTable>();
  if (false == pAttackTable_->Initailize()) {
    return;
  }

  // HEALTH
  pHealthComponent_ = CreateComponent<HealthComponent>();
  if (false == pHealthComponent_->Initialize(100.0f)) {
    return;
  }

  // MP
  pMPComponent_ = CreateComponent<MPComponent>();
  if (false == pHealthComponent_->Initialize(100.0f)) {
    return;
  }

  // STATE
  pStateComponent_ = CreateComponent<StateComponent>();
  if (false == pStateComponent_->Initialize()) {
    return;
  }

  // RESTRICKTION
  pRestrictionComponent_ = CreateComponent<RestrictionComponent>();
  if (false == pRestrictionComponent_->Initialize()) {
    return;
  }

  // MOVEMENT
  pMovementComponent_ = CreateComponent<MovementComponent>();
  if (false == pMovementComponent_->Initialize(pRestrictionComponent_, position)) {
    return;
  }


  // COLLISION
  pHitBoxTop_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop);
  pHitBoxBottom_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxBottom);
  pAttackBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_AttackBox);
  pPushBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_PushBox);
  pGrabBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_GrabBox);

  // COMMEND
  pCommandComponent_ = CreateComponent<CommandComponent>();
  pCommandComponent_->SetTimeOutThreshold(150, 400);

  // INPUT
  pInputController_ = CreateComponent<InputController>();
  pInputController_->Initialize(this, pCommandComponent_);

  // PROJECTILE
  pProjectileComponent_ = CreateComponent<ProjectileComponent>();
  if (false == pProjectileComponent_->Initialize(GetLevel())) {
    return;
  }

  // GHOST EFFECT
  pGhostEffect_ = CreateComponent<GhostEffect>();
  if (false == pGhostEffect_->Initialize(pRender_, 4, 30, 0.7f)) {
    return;
  }

  // OPPONENT PLAYER
  if (nullptr == opponentPlayer) {
    return;
  }
  pOpponentPlayer_ = opponentPlayer;

  // INPUT BIT SET
  // ResetInputBitSet();

  // DBUG SETTING
  SetDebugParameter({.on_ = true, .linethickness_ = 2.0f});
  pRender_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Cyan});
  pHitBoxTop_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  pHitBoxBottom_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  pAttackBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Red});
  pPushBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::White});
  pGrabBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Yellow});

  //  SKILL
  pSkillComponent_ = CreateComponent<SkillComponent>();
  if (false == pSkillComponent_->Initialize(
                   this,
                   pRender_,
                   pMovementComponent_,
                   pInputController_,
                   pCommandComponent_,
                   pAttackBox_,
                   pProjectileComponent_,
                   pMPComponent_)) {
    return;
  }
}

void KOFPlayer::UpdateAnimState(unsigned long long animState, unsigned long long modifier /* = ANIMMOD_NONE*/, bool isForce, int startFrame /*= 0*/, unsigned long long time /*= 0.0f*/) {
  if (true == PlayerOnLeft()) {
    isFacingRight_ = true;
    pAnimationHandler_->SetCurrentAnimationState(animState);
    pAnimationHandler_->SetCurrentAnimationModifier(modifier);
    pRender_->ChangeAnimation((animState | modifier), isForce, startFrame, time);
  } else {
    isFacingRight_ = false;
    pAnimationHandler_->SetCurrentAnimationState(animState);
    pAnimationHandler_->SetCurrentAnimationModifier(modifier | ANIMMOD_FLIPPED);
    pRender_->ChangeAnimation((animState | modifier | ANIMMOD_FLIPPED), isForce, startFrame, time);
  }

  pStateComponent_->ChangeState(animState);
  pRestrictionComponent_->ChangeAnimStateRestrict(animState);

  SoundInfo* pSoundInfo;
  if (true == pSoundTable_->SearchSoundInfo(animState, &pSoundInfo)) {
    soundChannel_ = SoundManager::Instance()->SoundPlay(pSoundInfo->soundType_);
  }

  CollisionReset();
}

const HealthComponent* KOFPlayer::GetHealthComponent() const {
  return pHealthComponent_;
}

const MPComponent* KOFPlayer::GetMPComponent() const {
  return pMPComponent_;
}

void KOFPlayer::HitEvent(const AttackInfo* damageInfo) {
  if (true == pStateComponent_->ContainPlayerState({PS_Guard})) {
    pHealthComponent_->TakeDamage(damageInfo->damage_ * 0.1f);
    pMPComponent_->ChargeMP(damageInfo->damage_);
    pMovementComponent_->KnockBack(FacingRight(), {damageInfo->knockBackForce_.X * 0.9f, 0.0f});

  } else if (pMovementComponent_->GetMovementState() == MOVSTATE_Jump) {
    pHealthComponent_->TakeDamage(damageInfo->damage_);
    pMPComponent_->ChargeMP(damageInfo->damage_ * 2.0f);
    pMovementComponent_->KnockBack(PlayerOnLeft(), {3.0f, -5.0f});
    UpdateAnimState(PLAYER_ANIMTYPE_Hit_JumpUp, ANIMMOD_NONE, true);
  } else if (true == pStateComponent_->ContainPlayerState({PS_Seat})) {
    pHealthComponent_->TakeDamage(damageInfo->damage_ * 0.1f);
    pMPComponent_->ChargeMP(damageInfo->damage_ * 2.0f);
    pMovementComponent_->KnockBack(FacingRight(), {damageInfo->knockBackForce_.X * 0.9f, 0.0f});
    UpdateAnimState(PLAYER_ANIMTYPE_Hit_Seat, ANIMMOD_NONE, true);
  } else {
    pHealthComponent_->TakeDamage(damageInfo->damage_);
    pMPComponent_->ChargeMP(damageInfo->damage_ * 2.0f);
    switch (damageInfo->attackType_) {
      case ATTYPE_HighAttack: {
        if (ELMTTYPE_BlueFlame == damageInfo->elementType_) {
          UpdateAnimState(PLAYER_ANIMTYPE_Hit_High, ANIMMOD_BLUEFLAME, true);
        } else {
          UpdateAnimState(PLAYER_ANIMTYPE_Hit_High, ANIMMOD_NONE, true);
        }
        pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
      } break;

      case ATTYPE_LowAttack: {
        if (ELMTTYPE_BlueFlame == damageInfo->elementType_) {
          UpdateAnimState(PLAYER_ANIMTYPE_Hit_Low, ANIMMOD_BLUEFLAME, true);
        } else {
          UpdateAnimState(PLAYER_ANIMTYPE_Hit_Low, ANIMMOD_NONE, true);
        }
        pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
      } break;
      case ATTYPE_StrongAttack: {
        if (ELMTTYPE_BlueFlame == damageInfo->elementType_) {
          UpdateAnimState(PLAYER_ANIMTYPE_Hit_Strong, ANIMMOD_BLUEFLAME, true);
        } else {
          UpdateAnimState(PLAYER_ANIMTYPE_Hit_Strong, ANIMMOD_NONE, true);
        }
        pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
      } break;
      case ATTYPE_NormalAttack: {
        if (pHitBoxTop_->HasHit()) {
          if (ELMTTYPE_BlueFlame == damageInfo->elementType_) {
            UpdateAnimState(PLAYER_ANIMTYPE_Hit_High, ANIMMOD_BLUEFLAME, true);
            pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
          } else {
            UpdateAnimState(PLAYER_ANIMTYPE_Hit_High, ANIMMOD_NONE, true);
            pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
          }
        }
        if (pHitBoxBottom_->HasHit()) {
          if (ELMTTYPE_BlueFlame == damageInfo->elementType_) {
            UpdateAnimState(PLAYER_ANIMTYPE_Hit_Low, ANIMMOD_BLUEFLAME, true);
            pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
          } else {
            UpdateAnimState(PLAYER_ANIMTYPE_Hit_Low, ANIMMOD_NONE, true);
            pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
          }
        }
      } break;
      case ATTYPE_Airborne: {
        if (ELMTTYPE_BlueFlame == damageInfo->elementType_) {
          UpdateAnimState(PLAYER_ANIMTYPE_Hit_AirborneUp, ANIMMOD_BLUEFLAME, true);
        } else {
          UpdateAnimState(PLAYER_ANIMTYPE_Hit_AirborneUp, ANIMMOD_NONE, true);
        }
        pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
      } break;
      default:
        break;
    }
  }

  if (0 > pHealthComponent_->Health()) {
    Level* pLevel = GetLevel();
    if (nullptr == pLevel) {
      return;
    }
    KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
    if (nullptr == pKOFLevel) {
      return;
    }

    pKOFLevel->InitEndGame();
  }
}

void KOFPlayer::UpdateCollisionBoundScale() {
  if (nullptr == pHitBoxTop_ || nullptr == pHitBoxBottom_ || nullptr == pAttackBox_ || nullptr == pPushBox_ || nullptr == pGrabBox_) {
    return;
  }

  unsigned int imageIndex = pRender_->GetImageIndex();
  IImage* pImage = pRender_->GetImage();
  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  CollisionInfo* pCollisionInfo;

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_HitBoxTop, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pHitBoxTop_->SetActive(true);
      pHitBoxTop_->SetPosition(pCollisionInfo->position_);
      pHitBoxTop_->SetScale(pCollisionInfo->scale_);
    } else {
      pHitBoxTop_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_HitBoxBottom, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pHitBoxBottom_->SetActive(true);
      pHitBoxBottom_->SetPosition(pCollisionInfo->position_);
      pHitBoxBottom_->SetScale(pCollisionInfo->scale_);
    } else {
      pHitBoxBottom_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_AttackBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pAttackBox_->SetActive(true);
      pAttackBox_->SetPosition(pCollisionInfo->position_);
      pAttackBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pAttackBox_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_PushBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pPushBox_->SetActive(true);
      pPushBox_->SetPosition(pCollisionInfo->position_);
      pPushBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pPushBox_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_GrabBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pGrabBox_->SetActive(true);
      pGrabBox_->SetPosition(pCollisionInfo->position_);
      pGrabBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pGrabBox_->SetActive(false);
    }
  }
}

void KOFPlayer::UpdateAttack() {
  AttackInfo* pAttackInfo;
  unsigned long long animState = pAnimationHandler_->CurrentAnimationState();

  if (false == pAttackTable_->SearchAttackInfo(animState, &pAttackInfo)) {
    return;
  }

  if (true == pAttackInfo->isMultiHit_) {
    if (true == pRender_->HasIndexChange()) {
      pAttackBox_->ResetHit();
    }
  }

  CollisionComponent* pTargetCollision = nullptr;
  if (CheckAttackCollision(&pTargetCollision)) {
    if (nullptr != pTargetCollision) {
      Actor* pTargetOwner = pTargetCollision->GetOwner();
      if (nullptr == pTargetOwner) {
        return;
      }
      KOFPlayer* pTargetPlayer = dynamic_cast<KOFPlayer*>(pTargetOwner);
      if (nullptr == pTargetPlayer) {
        return;
      }

      Level* pLevel = GetLevel();
      if (nullptr == pLevel) {
        return;
      }
      KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
      if (nullptr == pKOFLevel) {
        return;
      }

      pTargetPlayer->HitEvent(pAttackInfo);

      RestrictionManager* restrictManager = pKOFLevel->GetRestrictionManager();
      if (nullptr != restrictManager) {
        restrictManager->ApplyExternalRestrict(ActorId(), {PR_LockInput, PR_StopAnim, PR_StopMove}, false, pAttackInfo->freezeTime_);
        restrictManager->ApplyExternalRestrict(pTargetPlayer->ActorId(), {PR_LockInput, PR_StopAnim, PR_StopMove}, false, pAttackInfo->freezeTime_);
      }

      // Calculate Effect Position.
      Vector collisionSectionLeftTop = {
          pAttackBox_->GetCollisionInfo().Left() > pTargetCollision->GetCollisionInfo().Left() ? pAttackBox_->GetCollisionInfo().Left() : pTargetCollision->GetCollisionInfo().Left(),
          pAttackBox_->GetCollisionInfo().Top() > pTargetCollision->GetCollisionInfo().Top() ? pAttackBox_->GetCollisionInfo().Top() : pTargetCollision->GetCollisionInfo().Top(),
      };

      Vector collisionSectionRightBottom = {
          pAttackBox_->GetCollisionInfo().Right() < pTargetCollision->GetCollisionInfo().Right() ? pAttackBox_->GetCollisionInfo().Right() : pTargetCollision->GetCollisionInfo().Right(),
          pAttackBox_->GetCollisionInfo().Bottom() < pTargetCollision->GetCollisionInfo().Bottom() ? pAttackBox_->GetCollisionInfo().Bottom() : pTargetCollision->GetCollisionInfo().Bottom(),
      };

      Vector effectPosition = {
          (collisionSectionRightBottom.X + collisionSectionLeftTop.X) / 2,
          (collisionSectionRightBottom.Y + collisionSectionLeftTop.Y) / 2};

      // TODO EFFECT ·ÎÁ÷
      if (pAttackInfo->effectType_ == EFTYPE_Iori_Explosion) {
        EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, {effectPosition.X + 150.0f, effectPosition.Y + 90.0f});
        EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, {effectPosition.X - 50.0f, effectPosition.Y + 110.0f});
        EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, {effectPosition.X - 30.0f, effectPosition.Y - 170.0f});
        EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, {effectPosition.X + 170.0f, effectPosition.Y - 190.0f});
        EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, {effectPosition.X + 110.0f, effectPosition.Y + 80.0f});
        EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, {effectPosition.X + 130.0f, effectPosition.Y - 200.0f});
        return;
      }

      // Spawn Effect
      if (true == pTargetPlayer->GetPlayerStateComponent()->ContainPlayerState({PS_Guard})) {
        if (true == FacingRight()) {
          EffectManager::Instance()->SpawnEffect(GetLevel(), EFTYPE_Guard_1, effectPosition);
        } else {
          EffectManager::Instance()->SpawnEffect(GetLevel(), EFTYPE_Guard_1 | EFMOD_FLIPPED, effectPosition);
        }
      } else {
        if (true == FacingRight()) {
          EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, effectPosition);
        } else {
          EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_ | EFMOD_FLIPPED, effectPosition);
        }
      }
    }
  }
}
bool KOFPlayer::CheckAttackCollision(CollisionComponent** outTargetCollision) {
  if (true == pAttackBox_->HasHit()) {
    return false;
  }
  CollisionComponent* pTargetCollision_Top = nullptr;
  if (true == pAttackBox_->Collision(
                  {
                      .targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop,
                      .targetCollisionType = CollisionType::CollisionType_Rect,
                      .myCollisionType = CollisionType::CollisionType_Rect,
                  },
                  &pTargetCollision_Top)) {
    *outTargetCollision = pTargetCollision_Top;
    pTargetCollision_Top->MarkAsHit();
    pAttackBox_->MarkAsHit();
    return true;
  }

  CollisionComponent* pTargetCollision_Bottom = nullptr;
  if (true == pAttackBox_->Collision(
                  {
                      .targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_HitBoxBottom,
                      .targetCollisionType = CollisionType::CollisionType_Rect,
                      .myCollisionType = CollisionType::CollisionType_Rect,
                  },
                  &pTargetCollision_Bottom)) {
    *outTargetCollision = pTargetCollision_Bottom;
    pTargetCollision_Bottom->MarkAsHit();
    pAttackBox_->MarkAsHit();
    return true;
  }

  *outTargetCollision = nullptr;
  return false;
}

bool KOFPlayer::CheckPushCollision() {
  CollisionComponent* pTargetPushCollision = nullptr;
  if (true == pPushBox_->Collision(
                  {
                      .targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_PushBox,
                      .targetCollisionType = CollisionType::CollisionType_Rect,
                      .myCollisionType = CollisionType::CollisionType_Rect,
                  },
                  &pTargetPushCollision)) {
    pPushBox_->MarkAsHit();

    Actor* pTarget = pTargetPushCollision->GetOwner();
    if (nullptr == pTarget) {
      return false;
    }

    KOFPlayer* pTargetPlayer = dynamic_cast<KOFPlayer*>(pTarget);
    if (nullptr == pTargetPlayer) {
      return false;
    }

    Vector TargetPostion = pTargetPlayer->GetPosition();
    Vector myPosition = GetPosition();

    float absPlayerDistance = std::abs(TargetPostion.X - myPosition.X);
    float pushTriggerDistance = pMovementComponent_->GetPushTriggerDistance();
    if (absPlayerDistance <= pushTriggerDistance) {
      pMovementComponent_->ApplyPushWeight(0.3f);

      pTargetPlayer->SetPosition({(myPosition.X + pushTriggerDistance * PlayerOnLeftFlag()), TargetPostion.Y});
    }
  }

  pPushBox_->ResetHit();
  return false;
}

void KOFPlayer::CollisionReset() {
  pHitBoxTop_->ResetHit();
  pHitBoxBottom_->ResetHit();
  pAttackBox_->ResetHit();
  pPushBox_->ResetHit();
  pGrabBox_->ResetHit();
}

Vector KOFPlayer::CharacterScale() const {
  return characterScale_;
}

void KOFPlayer::SetCharacterScale(const Vector& scale) {
  characterScale_ = scale;
}

void KOFPlayer::PushOverlappingPlayer() {
}

bool KOFPlayer::IsPlayer1() const {
  return isPlayer1_;
}

void KOFPlayer::SetPlayerOnLeft(bool isPlayerOnLeft) {
  isPlayerOnLeft_ = isPlayerOnLeft;
}

bool KOFPlayer::PlayerOnLeft() const {
  return isPlayerOnLeft_;
}

int KOFPlayer::PlayerOnLeftFlag() const {
  if (isPlayerOnLeft_) {
    return 1;
  }

  return -1;
}

int KOFPlayer::FacingRightFlag() const {
  if (isFacingRight_) {
    return 1;
  }

  return -1;
}

bool KOFPlayer::FacingRight() const {
  return isFacingRight_;
}

void KOFPlayer::SetFacingRight(bool isFacingRight) {
  isFacingRight_ = isFacingRight;
}

void KOFPlayer::SetIsAtMapEdge(bool isAtEdge) {
  isAtMapEdge_ = isAtEdge;
}

bool KOFPlayer::IsAtMapEdge() const {
  return isAtMapEdge_;
}

void KOFPlayer::CompareInputBitset() {
}

KOFPlayer* KOFPlayer::GetOpponentPlayer() const {
  return pOpponentPlayer_;
}

StateComponent* KOFPlayer::GetPlayerStateComponent() const {
  return pStateComponent_;
}

RestrictionComponent* KOFPlayer::GetPlayerRestrictComponent() const {
  return pRestrictionComponent_;
}

MovementComponent* KOFPlayer::GetMovementComponent() const {
  return pMovementComponent_;
}

void KOFPlayer::ReceiveClampedWidthOffset(float clampOffset) {
  if (true == pStateComponent_->ContainPlayerState({PS_EnableClampOffset})) {
    pMovementComponent_->ApplyClampedWidthOffset(clampOffset);
  }
}

const float KOFPlayer::GetCloseDistance() const {
  return closeDistance_;
}
