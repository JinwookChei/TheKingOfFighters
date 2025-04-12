#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent()
    : startPosition_({0.0f, 0.0f}),
      onBackStep_(false),
      backStepAccumulation_(0.0f),
      jumpVelocity_(0.0f),
      isGrounded_(true),
      onJump_(false) {
}

MovementComponent::~MovementComponent() {
}

void MovementComponent::BeginPlay() {
}

void MovementComponent::Tick(unsigned long long curTick) {
  float deltaTime = curTick * 0.001f;

  // BACKSTEP
  if (onBackStep_) {
    Actor* owner = GetOwner();
    if (nullptr == owner) {
      return;
    }

    const float moveAmount = backStepVelocity_ * deltaTime;

    // 누적 이동 거리 업데이트
    backStepAccumulation_ += moveAmount;

    // 이동
    const Vector& ownerPosition = owner->GetPosition();
    Vector newPosition = {
        ownerPosition.X - moveAmount,  // ← 방향으로 이동
        ownerPosition.Y};
    owner->SetPosition(newPosition);

    // 총 이동 거리 초과 시 백스텝 종료
    if (backStepAccumulation_ >= backStepTotalDistance_) {
      onBackStep_ = false;
      backStepAccumulation_ = 0.0f;

      // 백스텝 종료 후 위치 보정 필요 시 여기서 처리 가능
    }
  }
  // BACKSTEP END

  // JUMP
  if (onJump_) {
    Actor* owner = GetOwner();
    if (nullptr == owner) {
      return;
    }

    jumpVelocity_ -= gravity_ * deltaTime;
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
}

void MovementComponent::Initialize(const Vector& startPosition) {
  startPosition_ = startPosition;
  jumpVelocity_ = 0.0f;
}

void MovementComponent::Move(unsigned long long curTick, bool isFoward) {
  if (false == isGrounded_) {
    return;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  float deltaTime = curTick / 1000.0f;

  if (isFoward) {
    const Vector& moveDir = Vector::Right * moveVelocity_ * deltaTime;
    const Vector& curPosition = owner->GetPosition();
    const Vector& newPosition = curPosition + moveDir;
    owner->SetPosition(newPosition);
  } else {
    const Vector& moveDir = Vector::Left * moveVelocity_ * deltaTime;
    const Vector& curPosition = owner->GetPosition();
    const Vector& newPosition = curPosition + moveDir;
    owner->SetPosition(newPosition);
  }
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

  onBackStep_ = true;
}
