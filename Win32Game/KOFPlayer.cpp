#include "stdafx.h"
#include "CommandComponent.h"
#include "SkillComponent.h"
#include "ProjectileComponent.h"
#include "MovementComponent.h"
#include "StateComponent.h"
#include "AttackTable.h"
#include "HealthComponent.h"
#include "GhostEffect.h"
#include "CollisionBox.h"
#include "KOFPlayer.h"
#include "KOFLevel.h"

KOFPlayer::KOFPlayer()
    : pRender_(nullptr),
      pMovementComponent_(nullptr),
      pAttackTable_(nullptr),
      pHealthComponent_(nullptr),
      pStateComponent_(nullptr),
      pHitBoxTop_(nullptr),
      pHitBoxBottom_(nullptr),
      pAttackBox_(nullptr),
      pPushBox_(nullptr),
      pGrabBox_(nullptr),
      pSkillComponent_(nullptr),
      pCommandComponent_(nullptr),
      pProjectileComponent_(nullptr),
      pGhostEffect_(nullptr),
      characterScale_({0.0f, 0.0f}),
      animState_(PAS_Idle),
      prevImageIndex_(0),
      isFacingRight_(true),
      isAtMapEdge_(false),
      opponentPlayer_(nullptr) {
}

KOFPlayer::~KOFPlayer() {
}

void KOFPlayer::BeginPlay() {
}

void KOFPlayer::Tick(unsigned long long deltaTick) {
}

void KOFPlayer::Initialize(const Vector& position, bool useCameraPosition, bool isFacingRight, KOFPlayer* opponentPlayer) {
  SetPosition(position);

  SetUseCameraposition(useCameraPosition);
  SetFacingRight(isFacingRight);

  // RENDERER
  pRender_ = CreateImageRenderFIFO();
  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->SetLocalScale({4.5f, 4.5f});

  // MOVEMENT
  pMovementComponent_ = CreateComponent<MovementComponent>();
  if (false == pMovementComponent_->Initialize(position)) {
    return;
  }

  // DAMAGE
  pAttackTable_ = CreateComponent<AttackTable>();
  if (false == pAttackTable_->Initailize()) {
    return;
  }

  // HEALTH
  pHealthComponent_ = CreateComponent<HealthComponent>();
  if (false == pHealthComponent_->Initialize(100.0f)) {
    return;
  }

  // STATE
  pStateComponent_ = CreateComponent<StateComponent>();
  if (false == pStateComponent_->Initialize()) {
    return;
  }

  // COLLISION
  pHitBoxTop_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop);
  pHitBoxBottom_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxBottom);
  pAttackBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_AttackBox);
  pPushBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_PushBox);
  pGrabBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_GrabBox);

  // SKILL
  pSkillComponent_ = CreateComponent<SkillComponent>();
  if (false == pSkillComponent_->Initialize()) {
    return;
  }

  // COMMEND
  pCommandComponent_ = CreateComponent<CommandComponent>();
  pCommandComponent_->SetTimeOutThreshold(150, 400);

  // PROJECTILE
  pProjectileComponent_ = CreateComponent<ProjectileComponent>();
  if (false == pProjectileComponent_->Initialize(GetLevel())) {
    return;
  }

  // GHOST EFFECT
  pGhostEffect_ = CreateComponent<GhostEffect>();
  if (false == pGhostEffect_->Initialize(pRender_, 5, 30)) {
    return;
  }

  // INPUT BIT SET
  ResetInputBitSet();

  // OPPONENT PLAYER
  if (nullptr == opponentPlayer) {
    return;
  }
  opponentPlayer_ = opponentPlayer;

  // DBUG SETTING
  SetDebugParameter({.on_ = true, .linethickness_ = 2.0f});
  pRender_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Cyan});
  pHitBoxTop_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  pHitBoxBottom_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  pAttackBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Red});
  pPushBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::White});
  pGrabBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Yellow});
}

void KOFPlayer::UpdateAnimState(int animState) {
  animState_ = animState;
  pRender_->ChangeAnimation(animState_ * FacingRightFlag());
  pStateComponent_->ChangeState(animState_);

  CollisionReset();
}

const HealthComponent* KOFPlayer::GetHealthComponent() const {
  return pHealthComponent_;
}

void KOFPlayer::HitEvent(const AttackInfo* damageInfo) {
  pHealthComponent_->TakeDamage(damageInfo->damage_);

  if (pHitBoxTop_->HasHit()) {
    animState_ = PAS_HitTop;
    pRender_->ChangeAnimation(animState_ * FacingRightFlag());
    pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
  }

  if (pHitBoxBottom_->HasHit()) {
    animState_ = PAS_HitBottom;
    pRender_->ChangeAnimation(animState_ * FacingRightFlag());
    pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
  }
}

void KOFPlayer::UpdateInput() {
}

void KOFPlayer::UpdateCommand() {
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

      AttackInfo* pAttackInfo;
      if (false == pAttackTable_->SearchAttackInfo(animState_, &pAttackInfo)) {
        return;
      }

      pTargetPlayer->HitEvent(pAttackInfo);

      Level* pLevel = GetLevel();
      if (nullptr == pLevel) {
        return;
      }
      KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
      if (nullptr == pKOFLevel) {
        return;
      }
      pKOFLevel->FreezeActors({this, pTargetPlayer}, false, 150);

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

      // 이펙트도 여기서 스폰.
      EffectManager::Instance()->SpawnEffect(GetLevel(), EFKEY_Hit_2, effectPosition);
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

bool KOFPlayer::UpdateCollisionPush() {
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

    // TODO : Push 충돌시 최소 거리보장해야함. 앞으로 가기 버튼에서 press가 아니면 보간해서 조금씩 Position 조정.
    // TODO : 벽에서 서로 밀고있는 상황. 한쪽캐릭터가 대쉬 이동 중이면, 뒤로 밀려나는 현상 해결.
    // TODO : 우측 캐릭터는 뒤로 가고 있는데, 좌측 캐릭터가 대쉬 이동으로 밀고 있는 상황 -> 뭔가 뒤로 밀림.
    if (std::abs(TargetPostion.X - myPosition.X) < 400.0f) {
      const Vector& moveDir = pMovementComponent_->GetMoveDir();
      if (moveDir.X > 0 && FacingRight() == true) {
        pTargetPlayer->SetPosition({TargetPostion.X + moveDir.X, TargetPostion.Y});
      } else if (moveDir.X < 0 && FacingRight() == false) {
        pTargetPlayer->SetPosition({TargetPostion.X + moveDir.X, TargetPostion.Y});
      }
      if (pTargetPlayer->IsAtMapEdge()) {
        SetPosition({myPosition.X - moveDir.X, myPosition.Y});
      }
    }

    return true;
  }

  return false;
}

void KOFPlayer::CollisionReset() {
  pHitBoxTop_->ResetHit();
  pHitBoxBottom_->ResetHit();
  pAttackBox_->ResetHit();
  pPushBox_->ResetHit();
  pGrabBox_->ResetHit();
}

void KOFPlayer::UpdatePrevAnimationIndex() {
  if (nullptr == pRender_) {
    return;
  }
  unsigned int curImageIndex = pRender_->GetImageIndex();

  if (curImageIndex != prevImageIndex_) {
    prevImageIndex_ = curImageIndex;
  }
}

Vector KOFPlayer::CharacterScale() const {
  return characterScale_;
}

void KOFPlayer::SetCharacterScale(const Vector& scale) {
  characterScale_ = scale;
}

void KOFPlayer::PushOverlappingPlayer() {
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

void KOFPlayer::ResetInputBitSet() {
  inputPressBitSet_.reset();
  inputUpBitSet_.reset();
}

bool KOFPlayer::IsEqualInputBitSet(const std::bitset<8>& myBitSet, const std::bitset<8>& compareTarget) {
  return myBitSet == compareTarget;
}

bool KOFPlayer::IsContainInputBitSet(const std::bitset<8>& myBitSet, const std::bitset<8>& compareTarget) {
  return (myBitSet & compareTarget) == compareTarget;
}

KOFPlayer* KOFPlayer::GetOpponentPlayer_() const {
  return opponentPlayer_;
}
