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
      curJumpVelocity_(0.0f),
      curJumpFowardVelocity_(0.0f),
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

  //// JUMP
  // if (onJump_) {
  //   jumpVelocity_ -= gravity_ * curTick;
  //   const Vector& ownerPosition = owner->GetPosition();
  //   Vector newPosition = {ownerPosition.X, ownerPosition.Y - jumpVelocity_};

  //  if (newPosition.Y >= startPosition_.Y) {
  //    newPosition.Y = startPosition_.Y;
  //    jumpVelocity_ = 0.0f;
  //    onJump_ = false;
  //    isGrounded_ = true;
  //  }
  //  owner->SetPosition(newPosition);
  //}
  //// JUMP END

  // JUMP
  if (onJump_) {
    curJumpVelocity_ -= gravity_ * curTick;

    const Vector& ownerPosition = owner->GetPosition();

    // 앞으로 이동할 속도 지정
    // float forwardSpeed = 0.5f;  // 필요에 따라 속도 조절

    // 새 위치 계산: X축은 앞으로 이동, Y축은 점프 곡선
    Vector newPosition = {
        ownerPosition.X + curJumpFowardVelocity_ * curTick,  // X축 앞으로 이동
        ownerPosition.Y - curJumpVelocity_                   // Y축 점프
    };

    // 땅에 도착했는지 체크
    if (newPosition.Y >= startPosition_.Y) {
      newPosition.Y = startPosition_.Y;
      curJumpVelocity_ = 0.0f;
      onJump_ = false;
      isGrounded_ = true;
    }

    owner->SetPosition(newPosition);
  }

  // JUMP

  moveDir_ = {0.0f, 0.0f};
}

void MovementComponent::Initialize(const Vector& startPosition) {
  startPosition_ = startPosition;
  // curJumpVelocity_ = 0.0f;
}

Vector MovementComponent::GetMoveDir() const {
  return moveDir_;
}

void MovementComponent::Move(unsigned long long curTick, bool isRightDirection, bool isPushing) {
  if (false == isGrounded_) {
    return;
  }

  float weight = 1.0f;
  if (true == isPushing) {
    weight = 0.8f;
  }

  if (isRightDirection) {
    moveDir_ = Vector::Right * moveVelocity_ * curTick * weight;
  } else {
    moveDir_ = Vector::Left * moveVelocity_ * curTick * weight;
  }
}

void MovementComponent::Run(unsigned long long curTick, bool isRightDirection, bool isPushing) {
  if (false == isGrounded_) {
    return;
  }

  float weight = 1.0f;
  if (true == isPushing) {
    weight = 0.5f;
  }

  if (isRightDirection) {
    moveDir_ = Vector::Right * runVelocity_ * curTick * weight;
  } else {
    moveDir_ = Vector::Left * runVelocity_ * curTick * weight;
  }
}

void MovementComponent::Jump() {
  if (isGrounded_) {
    curJumpVelocity_ = jumpForce_;
    curJumpFowardVelocity_ = 0.0f;
    onJump_ = true;
    isGrounded_ = false;
  }
}

void MovementComponent::JumpForward(bool isRightDirection, bool isRunning) {
  if (isGrounded_) {
    curJumpVelocity_ = jumpForce_;
    onJump_ = true;
    isGrounded_ = false;

    if (isRightDirection) {
      if (isRunning) {
        curJumpFowardVelocity_ = jumpFowardVelocityInRunning_;
      } else {
        curJumpFowardVelocity_ = jumpFowardVelocityInWalking_;
      }
    } else {
      if (isRunning) {
        curJumpFowardVelocity_ = -jumpFowardVelocityInRunning_;
      } else {
        curJumpFowardVelocity_ = -jumpFowardVelocityInWalking_;
      }
    }
  }
}

void MovementComponent::BackStep(int facingDirection) {
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
  backstepEndPos.X -= backstepDistance * facingDirection;

  onBackStep_ = true;
}
