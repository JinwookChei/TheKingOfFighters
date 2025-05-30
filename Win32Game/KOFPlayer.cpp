#include "stdafx.h"
#include "CommandComponent.h"
#include "ProjectileComponent.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
#include "GhostEffect.h"
#include "CollisionBox.h"
#include "KOFPlayer.h"
#include "KOFLevel.h"

KOFPlayer::KOFPlayer()
    : pRender_(nullptr),
      pMovementComponent_(nullptr),
      pHealthComponent_(nullptr),
      pHitBoxTop_(nullptr),
      pHitBoxBottom_(nullptr),
      pAttackBox_(nullptr),
      pPushBox_(nullptr),
      pGrabBox_(nullptr),
      pCommandComponent_(nullptr),
      pProjectileComponent_(nullptr),
      pGhostEffect_(nullptr),
      characterScale_({0.0f, 0.0f}),
      animState_(0),
      isFacingRight_(true),
      isAtMapEdge_(false) {
}

KOFPlayer::~KOFPlayer() {
}

void KOFPlayer::BeginPlay() {
}

void KOFPlayer::Tick(unsigned long long deltaTick) {
}

void KOFPlayer::Initialize(const Vector& position, bool useCameraPosition, bool isFacingRight) {
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

  // HEALTH
  pHealthComponent_ = CreateComponent<HealthComponent>();
  if (false == pHealthComponent_->Initialize(100.0f)) {
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

  // DBUG SETTING
  SetDebugParameter({.on_ = true, .linethickness_ = 2.0f});
  pRender_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Cyan});
  pHitBoxTop_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  pHitBoxBottom_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  pAttackBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Red});
  pPushBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::White});
  pGrabBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Yellow});
}

void KOFPlayer::ChangeAnimation(unsigned long long animationTag, int startFrame, unsigned long long time) {
  pRender_->ChangeAnimation(animationTag * FacingRightFlag(), startFrame, time);

  CollisionReset();
}

const HealthComponent* KOFPlayer::GetHealthComponent() const {
  return pHealthComponent_;
}

void KOFPlayer::HitEvent(float damage, const Vector& knockBackForce) {
}

void KOFPlayer::InputUpdate(unsigned long long deltaTick) {
}

void KOFPlayer::CommandUpdate() {
}

void KOFPlayer::CollisionBoundUpdate() {
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

bool KOFPlayer::CheckAttackCollision(CollisionComponent** outTargetCollision) {
  CollisionComponent* pTargetCollision_Top = nullptr;
  if (true == pAttackBox_->Collision(
                  {
                      .targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop,
                      .targetCollisionType = CollisionType::CollisionType_Rect,
                      .myCollisionType = CollisionType::CollisionType_Rect,
                  },
                  &pTargetCollision_Top)) {
    *outTargetCollision = pTargetCollision_Top;
    pAttackBox_->OnCollision();
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
    pAttackBox_->OnCollision();
    return true;
  }

  *outTargetCollision = nullptr;
  return false;
}

bool KOFPlayer::CollisionPushUpdate() {
  CollisionComponent* pTargetPushCollision = nullptr;
  if (true == pPushBox_->Collision(
                  {
                      .targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_PushBox,
                      .targetCollisionType = CollisionType::CollisionType_Rect,
                      .myCollisionType = CollisionType::CollisionType_Rect,
                  },
                  &pTargetPushCollision)) {
    pPushBox_->OnCollision();

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
  pHitBoxTop_->OffCollision();
  pHitBoxBottom_->OffCollision();
  pAttackBox_->OffCollision();
  pPushBox_->OffCollision();
  pGrabBox_->OffCollision();
}

void KOFPlayer::TriggerEventAtAnimationIndex() {
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
