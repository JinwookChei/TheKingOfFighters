#include "stdafx.h"
#include "MovementComponent.h"

// 선형 보간 함수
float Lerp(float a, float b, float t) {
  return a + (b - a) * t;
}

MovementComponent::MovementComponent()
    : startPosition_({0.0f, 0.0f}),
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
  // BACKSTEP
  if (onBackStep_) {
    Actor* owner = GetOwner();
    if (nullptr == owner) {
      return;
    }

    backstepTimer += curTick;
    float t = backstepTimer / backstepDuration;

    if (t >= 1.0f) {
      t = 1.0f;
      onBackStep_ = false;
      // 애니메이션 복귀: PlayAnimation("Idle");
    }

    // x축은 선형 보간
    Vector newPostion;
    newPostion.X = Lerp(backstepStartPos.X, backstepEndPos.X, t);

    // y축은 포물선 곡선으로 위로 떠오르기 -> 떨어지기
    // y(t) = -4h(t-0.5)^2 + h  :  t ∈ [0, 1]
    float height = -4 * backstepHeight * (t - 0.5f) * (t - 0.5f) + backstepHeight;
    newPostion.Y = backstepStartPos.Y - height;

    owner->SetPosition(newPostion);
  }
  // BACKSTEP END

  // JUMP
  if (onJump_) {
    Actor* owner = GetOwner();
    if (nullptr == owner) {
      return;
    }

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

  if (isFoward) {
    const Vector& moveDir = Vector::Right * moveVelocity_ * curTick;
    const Vector& curPosition = owner->GetPosition();
    const Vector& newPosition = curPosition + moveDir;
    owner->SetPosition(newPosition);
  } else {
    const Vector& moveDir = Vector::Left * moveVelocity_ * curTick;
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

  backstepTimer = 0.0f;

  backstepStartPos = owner->GetPosition();
  backstepEndPos = owner->GetPosition();
  backstepEndPos.X -= backstepDistance;

  onBackStep_ = true;
}
