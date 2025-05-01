#include "stdafx.h"
#include "CommandComponent.h"
#include "ProjectileComponent.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
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
      characterScale_({0.0f, 0.0f}),
      animState_(0),
      isFlip_(1),
      isAtMapEdge_(false) {
}

KOFPlayer::~KOFPlayer() {
}

void KOFPlayer::BeginPlay() {
}

void KOFPlayer::Tick(unsigned long long curTick) {
}

void KOFPlayer::Initialize(const Vector& position, bool useCameraPosition, bool flip) {
  SetPosition(position);

  SetUseCameraposition(useCameraPosition);
  Flip(flip);

  // RENDERER
  pRender_ = CreateImageRender();
  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->SetLocalScale({4.5f, 4.5f});

  // MOVEMENT
  pMovementComponent_ = CreateComponent<MovementComponent>();
  pMovementComponent_->Initialize(position);

  // HEALTH
  pHealthComponent_ = CreateComponent<HealthComponent>();
  pHealthComponent_->Initialize(100.0f);

  // COLLISION
  pHitBoxTop_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop);
  pHitBoxBottom_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxBottom);
  pAttackBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_AttackBox);
  pPushBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_PushBox);
  pGrabBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_GrabBox);

  // COMMEND
  pCommandComponent_ = CreateComponent<CommandComponent>();
  pCommandComponent_->SetTimeOutThreshold(100);

  // PROJECTILE
  pProjectileComponent_ = CreateComponent<ProjectileComponent>();
  if (false == pProjectileComponent_->Initialize(GetLevel())) {
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

void KOFPlayer::InputUpdate(unsigned long long deltaTick) {
}

HealthComponent* KOFPlayer::GetHealthComponent() const {
  return pHealthComponent_;
}

void KOFPlayer::CommendUpdate() {
}

void KOFPlayer::CollisionBoundUpdate() {
}

bool KOFPlayer::CollisionHitUpdate() {
  return false;
}

bool KOFPlayer::CollisionAttackUpdate() {
  CollisionComponent* pTargetCollision_Top = nullptr;
  if (true == pAttackBox_->Collision(
                  {
                      .targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop,
                      .targetCollisionType = CollisionType::CollisionType_Rect,
                      .myCollisionType = CollisionType::CollisionType_Rect,
                  },
                  &pTargetCollision_Top)) {
    pTargetCollision_Top->OnHit();
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
    pTargetCollision_Bottom->OnHit();
    return true;
  }

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
    pPushBox_->OnHit();
    Actor* pTarget = pTargetPushCollision->GetOwner();

    if (nullptr == pTarget) {
      return false;
    }
    // TODO : Casting
    KOFPlayer* pTargetPlayer = (KOFPlayer*)pTarget;


    Vector TargetPostion = pTarget->GetPosition();

    Vector myPosition = GetPosition();

    if (std::abs(TargetPostion.X - myPosition.X) < 400.0f) {
      const Vector& moveDir = pMovementComponent_->GetMoveDir();
      if (moveDir.X > 0 && isFlip_ == 1) {
        pTarget->SetPosition({TargetPostion.X + moveDir.X, TargetPostion.Y});

      } else if (moveDir.X < 0 && isFlip_ == -1) {
        pTarget->SetPosition({TargetPostion.X + moveDir.X, TargetPostion.Y});
      }

      //if (pTarget->i)
    }

    return true;
  }

  return false;
}

void KOFPlayer::CollisionReset() {
  pHitBoxTop_->OffHit();
  pHitBoxBottom_->OffHit();
  pAttackBox_->OffHit();
  pPushBox_->OffHit();
  pGrabBox_->OffHit();
}

Vector KOFPlayer::CharacterScale() const {
  return characterScale_;
}

void KOFPlayer::SetCharacterScale(const Vector& scale) {
  characterScale_ = scale;
}

void KOFPlayer::PushOverlappingPlayer() {
}

void KOFPlayer::Flip(bool flip) {
  if (flip) {
    isFlip_ = -1;
  } else {
    isFlip_ = 1;
  }
}

void KOFPlayer::SetIsAtMapEdge(bool isAtEdge) {
  isAtMapEdge_ = isAtEdge;
}

bool KOFPlayer::IsAtMapEdge() const {
  return isAtMapEdge_;
}
