#include "stdafx.h"
#include "MovementComponent.h"
#include "KOFPlayer.h"
#include "KOFLevel.h"
#include "StateComponent.h"

float Lerp(float a, float b, float t) {
  return a + (b - a) * t;
}

MovementComponent::MovementComponent()
    : startPosition_({0.0f, 0.0f}),
      preFramePosition_({0.0f, 0.0f}),
      // MOVE
      moveDir_({0.0f, 0.0f}),
      // DASH
      dashTimer_(0.0f),
      dashDuration_(0.0f),
      dashDistance_(0.0f),
      dashStartPos_({0.0f, 0.0f}),
      dashEndPos_({0.0f, 0.0f}),
      // BACK STEP
      backstepTimer_(0.0f),
      backstepStartPos_({0.0f, 0.0f}),
      backstepEndPos_({0.0f, 0.0f}),
      // JUMP
      isGrounded_(true),
      curJumpVelocity_({0.0f, 0.0f}),
      // KNOCK BACK
      curKnockBackVelocity_({0.0f, 0.0f}),
      // PUSH
      pushWeight_(1.0f),
      clampedWidthOffset_(0.0f) {
}

MovementComponent::~MovementComponent() {
}

void MovementComponent::BeginPlay() {
  movementStateBitset_.reset();
}

void MovementComponent::Tick(unsigned long long deltaTick) {
  UpdateGroundedState();

  UpdateMove(deltaTick);

  UpdateDash(deltaTick);

  UpdateBackStep(deltaTick);

  UpdateJump(deltaTick);

  UpdateKnockBack(deltaTick);

  BroadcastClampedWidthOffset();

  ClampPositionToLevelBoundary();

  ClampPositionToScreenBoundary();

  pushWeight_ = 1.0f;
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }
  const Vector& curPosition = pOwner->GetPosition();
  preFramePosition_ = pOwner->GetPosition();
}

bool MovementComponent::Initialize(const Vector& startPosition) {
  startPosition_ = startPosition;
  return true;
}

bool MovementComponent::EqualMovementState(std::initializer_list<MOVEMENT_STATE> movStateList) {
  std::bitset<MOVSTATE_Max> temp;
  for (auto state : movStateList) {
    temp.set(state);
  }
  return movementStateBitset_ == temp;
}

bool MovementComponent::ContainMovementState(std::initializer_list<MOVEMENT_STATE> movStateList) {
  for (auto state : movStateList) {
    if (movementStateBitset_.test(state)) {
      return true;
    }
  }
  return false;
}

void MovementComponent::UpdateMove(unsigned long long deltaTick) {
  if (false == movementStateBitset_.test(MOVSTATE_Move)) {
    return;
  }
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }
  const Vector& curPosition = pOwner->GetPosition();

  const Vector& movePosition = curPosition + moveDir_ * pushWeight_ * (float)deltaTick;
  pOwner->SetPosition(movePosition);

  if (Vector({0.0f, 0.0f}) == moveDir_) {
    movementStateBitset_.reset(MOVSTATE_Move);
  }

  moveDir_ = {0.0f, 0.0f};
}

void MovementComponent::Move(bool isRightDirection) {
  if (false == isGrounded_) {
    return;
  }

  movementStateBitset_.set(MOVSTATE_Move);

  if (isRightDirection) {
    moveDir_ = Vector::Right * moveVelocity_;
  } else {
    moveDir_ = Vector::Left * moveVelocity_;
  }
}

void MovementComponent::MoveBack(bool isRightDirection) {
  if (false == isGrounded_) {
    return;
  }

  movementStateBitset_.set(MOVSTATE_Move);

  if (isRightDirection) {
    moveDir_ = Vector::Left * moveBackVelocity_;
  } else {
    moveDir_ = Vector::Right * moveBackVelocity_;
  }
}

void MovementComponent::Run(bool isRightDirection) {
  if (false == isGrounded_) {
    return;
  }
  movementStateBitset_.set(MOVSTATE_Move);

  if (isRightDirection) {
    moveDir_ = Vector::Right * runVelocity_;
  } else {
    moveDir_ = Vector::Left * runVelocity_;
  }
}

void MovementComponent::UpdateJump(unsigned long long deltaTick) {
  if (false == movementStateBitset_.test(MOVSTATE_Jump)) {
    return;
  }
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }

  curJumpVelocity_.Y -= gravity_ * deltaTick;

  const Vector& ownerPosition = pOwner->GetPosition();

  Vector jumpPosition = {
      ownerPosition.X + curJumpVelocity_.X * deltaTick,  // X축 앞으로 이동
      ownerPosition.Y - curJumpVelocity_.Y               // Y축 점프
  };

  // 땅에 도착했는지 체크
  if (jumpPosition.Y >= startPosition_.Y) {
    jumpPosition.Y = startPosition_.Y;
    curJumpVelocity_ = {0.0f, 0.0f};
    movementStateBitset_.reset(MOVSTATE_Jump);
    movementSoundChannel_ = SoundManager::Instance()->SoundPlay(SOUNDTYPE_COMMON_Land);
  }

  pOwner->SetPosition(jumpPosition);
}

void MovementComponent::Jump(bool isRightDirection, Vector normalJumpForce) {
  if (isGrounded_) {
    movementStateBitset_.set(MOVSTATE_Jump);
    if (isRightDirection == true) {
      curJumpVelocity_ = normalJumpForce;
    } else {
      curJumpVelocity_.X = -normalJumpForce.X;
      curJumpVelocity_.Y = normalJumpForce.Y;
    }
  }
}

void MovementComponent::JumpForward(bool isRightDirection, bool isRunning) {
  if (isGrounded_) {
    movementStateBitset_.set(MOVSTATE_Jump);
    if (isRightDirection) {
      if (isRunning) {
        curJumpVelocity_ = fowardJumpForceInRunning_;
      } else {
        curJumpVelocity_ = fowardJumpForceInWalking_;
      }
    } else {
      if (isRunning) {
        curJumpVelocity_ = {-fowardJumpForceInRunning_.X, fowardJumpForceInRunning_.Y};
      } else {
        curJumpVelocity_ = {-fowardJumpForceInWalking_.X, fowardJumpForceInWalking_.Y};
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
  if (std::abs(curPosition.Y - startPosition_.Y) < 0.0001f) {
    isGrounded_ = true;
  } else {
    isGrounded_ = false;
  }
}

bool MovementComponent::GetIsGround() const {
  return isGrounded_;
}

void MovementComponent::UpdateBackStep(unsigned long long deltaTick) {
  if (false == movementStateBitset_.test(MOVSTATE_BackStep)) {
    return;
  }
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }

  backstepTimer_ += deltaTick;
  float t = backstepTimer_ / backstepDuration_;

  if (t >= 1.0f) {
    t = 1.0f;
    movementStateBitset_.reset(MOVSTATE_BackStep);
  }

  Vector backStepPostion;
  backStepPostion.X = Lerp(backstepStartPos_.X, backstepEndPos_.X, t);

  float height = -4 * backstepHeight_ * (t - 0.5f) * (t - 0.5f) + backstepHeight_;
  backStepPostion.Y = startPosition_.Y - height;

  pOwner->SetPosition(backStepPostion);
}

void MovementComponent::BackStep(bool isRightDirection) {
  if (false == isGrounded_) {
    return;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  movementStateBitset_.set(MOVSTATE_BackStep);
  backstepTimer_ = 0.0f;

  if (isRightDirection) {
    backstepStartPos_ = owner->GetPosition();
    backstepEndPos_ = owner->GetPosition();
    backstepEndPos_.X -= backstepDistance_;
  } else {
    backstepStartPos_ = owner->GetPosition();
    backstepEndPos_ = owner->GetPosition();
    backstepEndPos_.X += backstepDistance_;
  }
}

void MovementComponent::UpdateDash(unsigned long long deltaTick) {
  if (false == movementStateBitset_.test(MOVSTATE_Dash)) {
    return;
  }
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }

  dashTimer_ += deltaTick;
  float t = dashTimer_ / dashDuration_;

  if (t >= 1.0f) {
    t = 1.0f;
    movementStateBitset_.reset(MOVSTATE_Dash);
  }

  Vector dashPostion;
  dashPostion.X = Lerp(dashStartPos_.X, dashEndPos_.X, t);
  dashPostion.Y = startPosition_.Y;

  pOwner->SetPosition(dashPostion);
}

void MovementComponent::Dash(bool isRightDirection, float dashDuration, float dashDistance) {
  if (false == isGrounded_) {
    return;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  movementStateBitset_.set(MOVSTATE_Dash);
  dashTimer_ = 0.0f;
  dashDuration_ = dashDuration;
  dashDistance_ = dashDistance;

  if (isRightDirection) {
    dashStartPos_ = owner->GetPosition();
    dashEndPos_ = owner->GetPosition();
    dashEndPos_.X += dashDistance_;
  } else {
    dashStartPos_ = owner->GetPosition();
    dashEndPos_ = owner->GetPosition();
    dashEndPos_.X -= dashDistance_;
  }
}

void MovementComponent::StopDash() {
  movementStateBitset_.reset(MOVSTATE_Dash);
}

void MovementComponent::UpdateKnockBack(unsigned long long deltaTick) {
  Actor* pOwner = GetOwner();
  if (nullptr == pOwner) {
    return;
  }

  if (movementStateBitset_.test(MOVSTATE_KnockBack)) {
    if (curKnockBackVelocity_.X > 0) {
      curKnockBackVelocity_.X -= airResistance_ * deltaTick;
      curKnockBackVelocity_.Y -= gravity_ * deltaTick;
    } else if (curKnockBackVelocity_.X <= 0) {
      curKnockBackVelocity_.X += airResistance_ * deltaTick;
      curKnockBackVelocity_.Y -= gravity_ * deltaTick;
    }

    const Vector& ownerPosition = pOwner->GetPosition();

    Vector knockBackPosition = {
        ownerPosition.X + curKnockBackVelocity_.X,  // X축 앞으로 이동
        ownerPosition.Y - curKnockBackVelocity_.Y   // Y축 점프
    };

    if (knockBackPosition.Y >= startPosition_.Y) {
      knockBackPosition.Y = startPosition_.Y;
      curKnockBackVelocity_.Y = 0.0f;
      if (std::fabs(curKnockBackVelocity_.X) <= knockBackMinVelocity_) {
        curKnockBackVelocity_.X = 0;
        movementStateBitset_.reset(MOVSTATE_KnockBack);
      }
    }

    pOwner->SetPosition(knockBackPosition);
  }
}

void MovementComponent::KnockBack(bool isRightDirection, const Vector& knockBackForce) {
  if (isRightDirection) {
    curKnockBackVelocity_ = {-knockBackForce.X, knockBackForce.Y};
  } else {
    curKnockBackVelocity_ = {knockBackForce.X, knockBackForce.Y};
  }

  if (movementStateBitset_.test(MOVSTATE_Jump)) {
    movementStateBitset_.reset(MOVSTATE_Jump);
  }

  movementStateBitset_.set(MOVSTATE_KnockBack);
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
