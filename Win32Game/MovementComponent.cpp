#include "stdafx.h"
#include "MovementComponent.h"
#include "KOFPlayer.h"
#include "KOFLevel.h"

float Lerp(float a, float b, float t) {
  return a + (b - a) * t;
}

MovementComponent::MovementComponent()
    : startPosition_({0.0f, 0.0f}),
      velocity_({0.0f, 0.0f}),
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
      pushWeight_(1.0f) {
}

MovementComponent::~MovementComponent() {
}

void MovementComponent::BeginPlay() {
  movementStateBitset_.reset();
}

void MovementComponent::Tick(unsigned long long curTick) {
  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Vector& curPosition = owner->GetPosition();

  // UPDATE
  if (std::abs(curPosition.Y - startPosition_.Y) < 0.0001f) {
    isGrounded_ = true;
  } else {
    isGrounded_ = false;
  }
  // UPDATE END

  // MOVEDIR
  if (movementStateBitset_.test(MOVSTATE_Move)) {
    const Vector& movePosition = curPosition + moveDir_ * pushWeight_ * (float)curTick;
    owner->SetPosition(movePosition);

    if (Vector({0.0f, 0.0f}) == moveDir_) {
      movementStateBitset_.reset(MOVSTATE_Move);
    }
  }
  moveDir_ = {0.0f, 0.0f};
  // MOVEDIR END

  // DASH
  if (movementStateBitset_.test(MOVSTATE_Dash)) {
    dashTimer_ += curTick;
    float t = dashTimer_ / dashDuration_;

    if (t >= 1.0f) {
      t = 1.0f;
      movementStateBitset_.reset(MOVSTATE_Dash);
    }

    Vector dashPostion;
    dashPostion.X = Lerp(dashStartPos_.X, dashEndPos_.X, t);
    dashPostion.Y = startPosition_.Y;

    owner->SetPosition(dashPostion);
  }
  // DASH END

  // BACKSTEP
  if (movementStateBitset_.test(MOVSTATE_BackStep)) {
    backstepTimer_ += curTick;
    float t = backstepTimer_ / backstepDuration_;

    if (t >= 1.0f) {
      t = 1.0f;
      movementStateBitset_.reset(MOVSTATE_BackStep);
    }

    Vector backStepPostion;
    backStepPostion.X = Lerp(backstepStartPos_.X, backstepEndPos_.X, t);

    float height = -4 * backstepHeight_ * (t - 0.5f) * (t - 0.5f) + backstepHeight_;
    backStepPostion.Y = startPosition_.Y - height;

    owner->SetPosition(backStepPostion);
  }
  // BACKSTEP END

  // JUMP
  if (movementStateBitset_.test(MOVSTATE_Jump)) {
    curJumpVelocity_.Y -= gravity_ * curTick;

    const Vector& ownerPosition = owner->GetPosition();

    Vector jumpPosition = {
        ownerPosition.X + curJumpVelocity_.X * curTick,  // X축 앞으로 이동
        ownerPosition.Y - curJumpVelocity_.Y             // Y축 점프
    };

    // 땅에 도착했는지 체크
    if (jumpPosition.Y >= startPosition_.Y) {
      jumpPosition.Y = startPosition_.Y;
      curJumpVelocity_ = {0.0f, 0.0f};
      movementStateBitset_.reset(MOVSTATE_Jump);
    }

    owner->SetPosition(jumpPosition);
  }
  // JUMP END

  // KNOCK BACK
  if (movementStateBitset_.test(MOVSTATE_KnockBack)) {
    curKnockBackVelocity_.Y -= gravity_ * curTick;
    curKnockBackVelocity_.X -= airResistance_ * curTick;
    const Vector& ownerPosition = owner->GetPosition();

    Vector knockBackPosition = {
        ownerPosition.X + curKnockBackVelocity_.X,  // X축 앞으로 이동
        ownerPosition.Y - curKnockBackVelocity_.Y   // Y축 점프
    };

    if (knockBackPosition.Y >= startPosition_.Y) {
      knockBackPosition.Y = startPosition_.Y;
      curKnockBackVelocity_.Y = 0.0f;

      if (curKnockBackVelocity_.X <= knockBackMinVelocity_) {
        curKnockBackVelocity_.X = 0;
        movementStateBitset_.reset(MOVSTATE_KnockBack);
      }
    }

    owner->SetPosition(knockBackPosition);
  }
  // KNOCK BACK END


  // Clamp Level Boundary
  KOFPlayer* pKOFOwner = dynamic_cast<KOFPlayer*>(owner);
  if (nullptr == pKOFOwner) {
    return;
  }

  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(owner->GetLevel());
  if (nullptr == pKOFLevel) {
    return;
  }

  const Vector& newPosition = pKOFOwner->GetPosition();
  float newPositionLeft = newPosition.X - pKOFOwner->CharacterScale().HalfX();
  float newPositionRight = newPosition.X + pKOFOwner->CharacterScale().HalfX();
  if (newPositionLeft < pKOFLevel->GetLevelLeftBoundary()) {
    pKOFOwner->SetPosition({preFramePosition_.X, newPosition.Y});
  } else if (newPositionRight > pKOFLevel->GetLevelRightBoundary()) {
    pKOFOwner->SetPosition({preFramePosition_.X, newPosition.Y});
  }
  // Clamp Level Boundary END

  // Clamp Screen Boundary
  KOFPlayer* oppPlayer = pKOFOwner->GetOpponentPlayer();
  float playerDistance = std::fabs(oppPlayer->GetPosition().X - newPosition.X);
  float screenBoundaryWidth = pKOFLevel->GetScreenBoundaryWidth();
  if (playerDistance > screenBoundaryWidth) {
    pKOFOwner->SetPosition({preFramePosition_.X, newPosition.Y});
  }
  // Clamp Screen Boundary END


  pushWeight_ = 1.0f;
  velocity_ = curPosition - preFramePosition_;
  preFramePosition_ = owner->GetPosition();
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

Vector MovementComponent::GetVelocity() const {
  return velocity_;
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
