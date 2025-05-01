#include "stdafx.h"
#include "MovementComponent.h"

// 선형 보간 함수
float Lerp(float a, float b, float t) {
  return a + (b - a) * t;
}

MovementComponent::MovementComponent()
    : moveDir_({0.0f, 0.0f}),
      startPosition_({0.0f, 0.0f}),
      onBackStep_(false),
      jumpVelocity_(0.0f),
      isGrounded_(true),
      onJump_(false) {
}

MovementComponent::~MovementComponent() {
}

void MovementComponent::BeginPlay() {
}

void MovementComponent::Tick(unsigned long long curTick) {
  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  // MOVEDIR
  const Vector& curPosition = owner->GetPosition();
  const Vector& newPosition = curPosition + moveDir_;
  owner->SetPosition(newPosition);
  // MOVEDIR END
  
  // BACKSTEP
  if (onBackStep_) {
    backstepTimer += curTick;
    float t = backstepTimer / backstepDuration;

    if (t >= 1.0f) {
      t = 1.0f;
      onBackStep_ = false;
    }

    Vector newPostion;
    newPostion.X = Lerp(backstepStartPos.X, backstepEndPos.X, t);

    float height = -4 * backstepHeight * (t - 0.5f) * (t - 0.5f) + backstepHeight;
    newPostion.Y = backstepStartPos.Y - height;

    owner->SetPosition(newPostion);
  }
  // BACKSTEP END

  // JUMP
  if (onJump_) {
    jumpVelocity_ -= gravity_ * curTick;
    const Vector& ownerPosition = owner->GetPosition();
    Vector newPosition = {ownerPosition.X, ownerPosition.Y - jumpVelocity_};

    if (newPosition.Y >= startPosition_.Y) {
      newPosition.Y = startPosition_.Y;
      jumpVelocity_ = 0.0f;
      onJump_ = false;
      isGrounded_ = true;
    }
    owner->SetPosition(newPosition);
  }
  // JUMP END

  moveDir_ = {0.0f, 0.0f};
}

void MovementComponent::Initialize(const Vector& startPosition) {
  startPosition_ = startPosition;
  jumpVelocity_ = 0.0f;
}

Vector MovementComponent::GetMoveDir() const {
  return moveDir_;
}

void MovementComponent::Move(unsigned long long curTick, bool isFoward, bool isPushing) {
  if (false == isGrounded_) {
    return;
  }

  float weight = 1.0f;
  if (true == isPushing) {
    weight = 0.8f;
  }

  if (isFoward) {
    moveDir_ = Vector::Right * moveVelocity_ * curTick * weight;
  } else {
    moveDir_ = Vector::Left * moveVelocity_ * curTick * weight;
  }
}

void MovementComponent::Run(unsigned long long curTick, bool isPushing) {
  if (false == isGrounded_) {
    return;
  }

  float weight = 1.0f;
  if (true == isPushing) {
    weight = 0.5f;
  }

  // if (isFoward) {
  moveDir_ = Vector::Right * runVelocity_ * curTick * weight;
  /*} else {
    moveDir_ = Vector::Left * moveVelocity_ * curTick;
  }*/
}

void MovementComponent::Jump() {
  if (isGrounded_) {
    jumpVelocity_ = jumpForce_;
    onJump_ = true;
    isGrounded_ = false;
  }
}

void MovementComponent::BackStep() {
  if (false == isGrounded_) {
    return;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  backstepTimer = 0.0f;

  backstepStartPos = owner->GetPosition();
  backstepEndPos = owner->GetPosition();
  backstepEndPos.X -= backstepDistance;

  onBackStep_ = true;
}
