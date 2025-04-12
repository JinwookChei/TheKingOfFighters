#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent()
    : startPosition_({0.0f, 0.0f}),
      jumpVelocity_(0.0f),
      gravity_(260.0f),
      jumpForce_(60.0f),
      isGrounded_(true) {
}

MovementComponent::~MovementComponent() {
}

void MovementComponent::BeginPlay() {
}

void MovementComponent::Tick(unsigned long long curTick) {
  float deltaTime = curTick * 0.001f;

  if (!isGrounded_) {
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
      isGrounded_ = true;
    }

    owner->SetPosition(newPosition);
  }
}

void MovementComponent::Initialize(const Vector& startPosition) {
  startPosition_ = startPosition;
  jumpVelocity_ = 0.0f;
}

void MovementComponent::Jump() {
  if (isGrounded_) {
    jumpVelocity_ = jumpForce_;
    isGrounded_ = false;
  }
}
