#include "stdafx.h"
#include "MovementComponent.h"
#include "KOFPlayer.h"
#include "KOFLevel.h"
#include "StateComponent.h"

float CalculateParabolaHeight(float height, float duration, unsigned long long t) {
  float result = -(height / ((duration / 2.0f) * (duration / 2.0f))) * (t - (duration / 2.0f)) * (t - (duration / 2.0f)) + height;
  return result;
}

MovementComponent::MovementComponent()
    : startPosition_({0.0f, 0.0f}),
      preFramePosition_({0.0f, 0.0f}),
      curMovementState_(MOVEMENT_STATE::MOVSTATE_Idle),
      curVelocity_({0.0f, 0.0f}),
      // MOVE
      moveDir_({0.0f, 0.0f}),
      // DASH
      dashTimer_(0.0f),
      dashDuration_(0.0f),
      dashDistance_(0.0f),
      dashStartPos_({0.0f, 0.0f}),
      dashEndPos_({0.0f, 0.0f}),
      // BACK STEP
      backStepTimer_(0.0f),
      backStepStartPos_({0.0f, 0.0f}),
      backStepEndPos_({0.0f, 0.0f}),
      // JUMP
      isOnGrounded_(true),
      // KNOCK BACK
      curKnockBackVelocity_({0.0f, 0.0f}),
      // PUSH
      pushWeight_(1.0f),
      clampedWidthOffset_(0.0f) {
}

MovementComponent::~MovementComponent() {
}

void MovementComponent::BeginPlay() {
  curMovementState_ = MOVEMENT_STATE::MOVSTATE_Idle;
}

void MovementComponent::Tick(unsigned long long deltaTick) {
  switch (curMovementState_) {
    case MOVSTATE_Idle:
      UpdateIdle(deltaTick);
      break;
    case MOVSTATE_Walk:
      UpdateMove(deltaTick);
      break;
    case MOVSTATE_WalkBack:
      UpdateMove(deltaTick);
      break;
    case MOVSTATE_Run:
      UpdateMove(deltaTick);
      break;
    case MOVSTATE_Dash:
      UpdateDash(deltaTick);
      break;
    case MOVSTATE_BackStep:
      UpdateBackStep(deltaTick);
      break;
    case MOVSTATE_Jump:
      UpdateJump(deltaTick);
      break;
    case MOVSTATE_KnockBack:
      UpdateKnockBack(deltaTick);
      break;
    case MOVSTATE_Max:
    default:
      break;
  }

  UpdateGroundedState();

  BroadcastClampedWidthOffset();

  ClampPositionToLevelBoundary();

  ClampPositionToScreenBoundary();

  pushWeight_ = 1.0f;

  UpdatePreframePosition();
}

bool MovementComponent::Initialize(const Vector& startPosition) {
  startPosition_ = startPosition;
  return true;
}

MOVEMENT_STATE MovementComponent::GetMovementState() const {
  return curMovementState_;
}

void MovementComponent::UpdateIdle(unsigned long long deltaTick) {
  if (true == isOnGrounded_) {
    curVelocity_ = {0.0f, 0.0f};
    moveDir_ = {0.0f, 0.0f};
  } else {
    Actor* pOwner = GetOwner();
    if (nullptr == pOwner) {
      return;
    }
    const Vector& curPosition = pOwner->GetPosition();

    curVelocity_.Y += gravity_ * deltaTick;
    const Vector& movePosition = curPosition + curVelocity_;

    pOwner->SetPosition(movePosition);
  }
}

void MovementComponent::UpdateMove(unsigned long long deltaTick) {
  if (curMovementState_ != MOVSTATE_Walk && curMovementState_ != MOVSTATE_Run && curMovementState_ != MOVSTATE_WalkBack) {
    return;
  }

  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }
  const Vector& curPosition = pOwner->GetPosition();

  curVelocity_ = moveDir_ * pushWeight_ * (float)deltaTick;

  const Vector& movePosition = curPosition + curVelocity_;

  pOwner->SetPosition(movePosition);

  if (Vector({0.0f, 0.0f}) == moveDir_) {
    curMovementState_ = MOVSTATE_Idle;
  }

  moveDir_ = {0.0f, 0.0f};
}

void MovementComponent::Walk(bool isRightDirection) {
  if (false == isOnGrounded_) {
    return;
  }
  curMovementState_ = MOVSTATE_Walk;

  if (isRightDirection) {
    moveDir_ = Vector::Right * moveVelocity_;
  } else {
    moveDir_ = Vector::Left * moveVelocity_;
  }
}

void MovementComponent::WalkBack(bool isRightDirection) {
  if (false == isOnGrounded_) {
    return;
  }

  curMovementState_ = MOVSTATE_WalkBack;

  if (isRightDirection) {
    moveDir_ = Vector::Left * moveBackVelocity_;
  } else {
    moveDir_ = Vector::Right * moveBackVelocity_;
  }
}

void MovementComponent::Run(bool isRightDirection) {
  if (false == isOnGrounded_) {
    return;
  }

  curMovementState_ = MOVSTATE_Run;

  if (isRightDirection) {
    moveDir_ = Vector::Right * runVelocity_;
  } else {
    moveDir_ = Vector::Left * runVelocity_;
  }
}

void MovementComponent::UpdateJump(unsigned long long deltaTick) {
  if (curMovementState_ != MOVSTATE_Jump) {
    return;
  }
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }

  moveDir_.Y = (moveDir_.Y + gravity_);
  curVelocity_.X = moveDir_.X * (float)deltaTick;
  curVelocity_.Y = moveDir_.Y * (float)deltaTick;

  const Vector& ownerPosition = pOwner->GetPosition();

  Vector jumpPosition = {
      ownerPosition.X + curVelocity_.X,
      ownerPosition.Y + curVelocity_.Y};

  // ¶¥¿¡ µµÂøÇß´ÂÁö Ã¼Å©
  if (jumpPosition.Y >= startPosition_.Y) {
    jumpPosition.Y = startPosition_.Y;
    curVelocity_ = {0.0f, 0.0f};
    moveDir_ = {0.0f, 0.0f};
    curMovementState_ = MOVSTATE_Idle;
    movementSoundChannel_ = SoundManager::Instance()->SoundPlay(SOUNDTYPE_COMMON_Land);
  }

  pOwner->SetPosition(jumpPosition);
}

void MovementComponent::Jump() {
  if (isOnGrounded_) {
    curMovementState_ = MOVSTATE_Jump;
    moveDir_ = normalJumpForce_;
  }
}

void MovementComponent::Jump(bool isRightDirection, const Vector& jumpForce_) {
  if (isOnGrounded_) {
    curMovementState_ = MOVSTATE_Jump;
    moveDir_ = isRightDirection ? jumpForce_ : Vector{-jumpForce_.X, jumpForce_.Y};
  }
}

void MovementComponent::JumpForward(bool isRightDirection, bool isRunning) {
  if (isOnGrounded_) {
    curMovementState_ = MOVSTATE_Jump;
    if (isRightDirection) {
      if (isRunning) {
        moveDir_ = fowardJumpForceInRunning_;
      } else {
        moveDir_ = fowardJumpForceInWalking_;
      }
    } else {
      if (isRunning) {
        moveDir_ = {-fowardJumpForceInRunning_.X, fowardJumpForceInRunning_.Y};
      } else {
        moveDir_ = {-fowardJumpForceInWalking_.X, fowardJumpForceInWalking_.Y};
      }
    }
  }
}

void MovementComponent::UpdateGroundedState() {
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }
  const Vector& curPosition = pOwner->GetPosition();
  if (startPosition_.Y - curPosition.Y <= 0.0f) {
    isOnGrounded_ = true;
    pOwner->SetPosition({curPosition.X, startPosition_.Y});
  } else {
    isOnGrounded_ = false;
  }
}

bool MovementComponent::IsOnGround() const {
  return isOnGrounded_;
}

void MovementComponent::UpdateBackStep(unsigned long long deltaTick) {
  if (curMovementState_ != MOVSTATE_BackStep) {
    return;
  }

  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }

  backStepTimer_ += deltaTick;
  if (backStepTimer_ >= backStepDuration_) {
    backStepTimer_ = 0.0f;
    moveDir_ = {0.0f, 0.0f};
    curMovementState_ = MOVSTATE_Idle;
    return;
  }

  const Vector& ownerPosition = pOwner->GetPosition();

  curVelocity_.X = moveDir_.X * (float)deltaTick;
  curVelocity_.Y = CalculateParabolaHeight(backStepHeight_, backStepDuration_, backStepTimer_) - moveDir_.Y;
  moveDir_.Y = CalculateParabolaHeight(backStepHeight_, backStepDuration_, backStepTimer_);

  Vector backstepPosition = {ownerPosition.X + curVelocity_.X, ownerPosition.Y + curVelocity_.Y};
  pOwner->SetPosition(backstepPosition);
}

void MovementComponent::BackStep(bool isRightDirection) {
  if (false == isOnGrounded_) {
    return;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  curMovementState_ = MOVSTATE_BackStep;
  backStepTimer_ = 0.0f;

  if (isRightDirection) {
    moveDir_.X = -backStepDistance_ / backStepDuration_;
    moveDir_.Y = 0.0f;
  } else {
    moveDir_.X = backStepDistance_ / backStepDuration_;
    moveDir_.Y = 0.0f;
  }
}

void MovementComponent::UpdateDash(unsigned long long deltaTick) {
  if (curMovementState_ != MOVSTATE_Dash) {
    return;
  }
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }

  dashTimer_ += deltaTick;
  if (dashTimer_ >= dashDuration_) {
    dashTimer_ = 0.0f;
    moveDir_ = {0.0f, 0.0f};
    curMovementState_ = MOVSTATE_Idle;
    return;
  }

  const Vector& ownerPosition = pOwner->GetPosition();

  curVelocity_.X = moveDir_.X * (float)deltaTick;
  curVelocity_.Y = moveDir_.Y * (float)deltaTick;

  Vector dashPosition = {ownerPosition.X + curVelocity_.X, ownerPosition.Y + curVelocity_.Y};
  pOwner->SetPosition(dashPosition);
}

void MovementComponent::Dash(bool isRightDirection, float dashDuration, float dashDistance) {
  if (false == isOnGrounded_) {
    return;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  curMovementState_ = MOVSTATE_Dash;
  dashTimer_ = 0.0f;
  dashDuration_ = dashDuration;
  dashDistance_ = dashDistance;

  if (isRightDirection) {
    moveDir_.X = dashDistance_ / dashDuration_;
    moveDir_.Y = 0.0f;
  } else {
    moveDir_.X = -dashDistance_ / dashDuration_;
    moveDir_.Y = 0.0f;
  }
}

void MovementComponent::StopDash() {
  curMovementState_ = MOVSTATE_Idle;
}

void MovementComponent::UpdateKnockBack(unsigned long long deltaTick) {
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }
  if (moveDir_.X > 0) {
    moveDir_.X = max(0.0f, moveDir_.X - airResistance_);
  } else if (moveDir_.X < 0) {
    moveDir_.X = min(0.0f, moveDir_.X + airResistance_);
  }

  moveDir_.Y += gravity_;

  if ((curVelocity_.X > 0.0f && moveDir_.X < 0.0f) || (curVelocity_.X < 0.0f && moveDir_.X > 0.0f)) {
    moveDir_.X = 0.0f;
    curMovementState_ = MOVSTATE_Idle;
  }

  curVelocity_.X = moveDir_.X * (float)deltaTick;
  curVelocity_.Y = moveDir_.Y * (float)deltaTick;

  Vector ownerPosition = pOwner->GetPosition();
  ownerPosition.X += curVelocity_.X;
  ownerPosition.Y += curVelocity_.Y;

  pOwner->SetPosition(ownerPosition);
}

void MovementComponent::KnockBack(bool isRightDirection, const Vector& knockBackForce) {
  if (isRightDirection) {
    moveDir_ = {-knockBackForce.X, knockBackForce.Y};
  } else {
    moveDir_ = {knockBackForce.X, knockBackForce.Y};
  }

  curVelocity_ = {0.0f, 0.0f};
  curMovementState_ = MOVSTATE_KnockBack;
}

float MovementComponent::GetPushTriggerDistance() const {
  return pushTriggerDistance_;
}

void MovementComponent::ApplyPushWeight(float pushWeight) {
  pushWeight_ = pushWeight;
}

void MovementComponent::ClampPositionToLevelBoundary() {
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }

  KOFPlayer* pKOFOwner = dynamic_cast<KOFPlayer*>(pOwner);
  if (nullptr == pKOFOwner) {
    return;
  }

  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pOwner->GetLevel());
  if (nullptr == pKOFLevel) {
    return;
  }

  const Vector& newPosition = pKOFOwner->GetPosition();
  float newPositionLeft = newPosition.X - pKOFOwner->CharacterScale().HalfX();
  float newPositionRight = newPosition.X + pKOFOwner->CharacterScale().HalfX();
  if (newPositionLeft < pKOFLevel->GetLevelLeftBoundary()) {
    pKOFOwner->SetPosition({pKOFLevel->GetLevelLeftBoundary() + pKOFOwner->CharacterScale().X * 0.5f, newPosition.Y});
  } else if (newPositionRight > pKOFLevel->GetLevelRightBoundary()) {
    pKOFOwner->SetPosition({pKOFLevel->GetLevelRightBoundary() - pKOFOwner->CharacterScale().X * 0.5f, newPosition.Y});
  }
}

void MovementComponent::ClampPositionToScreenBoundary() {
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }
  KOFPlayer* pKOFOwner = dynamic_cast<KOFPlayer*>(pOwner);
  if (nullptr == pKOFOwner) {
    return;
  }
  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pOwner->GetLevel());
  if (nullptr == pKOFLevel) {
    return;
  }

  Vector ownerPosition = pKOFOwner->GetPosition();
  KOFPlayer* opponentPlayer = pKOFOwner->GetOpponentPlayer();
  float playerDistance = std::fabs(opponentPlayer->GetPosition().X - ownerPosition.X);
  float screenBoundaryWidth = pKOFLevel->GetScreenBoundaryWidth();
  if (playerDistance > screenBoundaryWidth) {
    pKOFOwner->SetPosition({preFramePosition_.X, ownerPosition.Y});
  }
}

void MovementComponent::BroadcastClampedWidthOffset() {
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }
  KOFPlayer* pKOFOwner = dynamic_cast<KOFPlayer*>(pOwner);
  if (nullptr == pKOFOwner) {
    return;
  }
  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pOwner->GetLevel());
  if (nullptr == pKOFLevel) {
    return;
  }

  const Vector& ownerPosition = pKOFOwner->GetPosition();
  float ownerPositionLeft = ownerPosition.X - pKOFOwner->CharacterScale().HalfX();
  float ownerPositionRight = ownerPosition.X + pKOFOwner->CharacterScale().HalfX();

  float clampedWidthOffset = 0.0f;

  if (true == pKOFOwner->GetPlayerStateComponent()->ContainPlayerState({PS_Hit})) {
    if (ownerPositionLeft < pKOFLevel->GetLevelLeftBoundary()) {
      clampedWidthOffset = pKOFLevel->GetLevelLeftBoundary() - ownerPositionLeft;
    } else if (ownerPositionRight > pKOFLevel->GetLevelRightBoundary()) {
      clampedWidthOffset = pKOFLevel->GetLevelRightBoundary() - ownerPositionRight;
    }
  }

  KOFPlayer* oppenPlayer = pKOFOwner->GetOpponentPlayer();
  if (nullptr == oppenPlayer) {
    return;
  }
  oppenPlayer->ReceiveClampedWidthOffset(clampedWidthOffset);
}

void MovementComponent::ApplyClampedWidthOffset(float clampOffset) {
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }

  Vector curPosition = pOwner->GetPosition();
  pOwner->SetPosition({curPosition.X + clampOffset, curPosition.Y});
}

void MovementComponent::UpdatePreframePosition() {
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }
  const Vector& curPosition = pOwner->GetPosition();
  preFramePosition_ = pOwner->GetPosition();
}

bool MovementComponent::IsFalling() const {
  bool result = curVelocity_.Y > 0.0f ? true : false;

  return result;
}

bool MovementComponent::IsRising() const {
  bool result = curVelocity_.Y < 0.0f ? true : false;

  return result;
}
