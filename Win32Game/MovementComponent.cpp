#include "stdafx.h"
#include "MovementComponent.h"

// 선형 보간 함수
float Lerp(float a, float b, float t) {
  return a + (b - a) * t;
}

MovementComponent::MovementComponent()
    : startPosition_({0.0f, 0.0f}),
      // MOVE
      moveDir_({0.0f, 0.0f}),
      // DASH
      onDash_(false),
      dashTimer_(0.0f),
      dashDuration_(0.0f),
      dashDistance_(0.0f),
      dashStartPos_({0.0f, 0.0f}),
      dashEndPos_({0.0f, 0.0f}),
      // BACK STEP
      onBackStep_(false),
      backstepTimer_(0.0f),
      backstepStartPos_({0.0f, 0.0f}),
      backstepEndPos_({0.0f, 0.0f}),
      // JUMP
      isGrounded_(true),
      onJump_(false),
      curJumpVelocity_({0.0f, 0.0f}),
      // KNOCK BACK
      onKnockBack_(false),
      curKnockBackVelocity_({0.0f, 0.0f}) {
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

  // UPDATE
  if (std::abs(curPosition.Y - startPosition_.Y) < 0.0001f) {
    isGrounded_ = true;
  } else {
    isGrounded_ = false;
  }
  // UPDATE END


  // DASH
  if (onDash_) {
    dashTimer_ += curTick;
    float t = dashTimer_ / dashDuration_;

    if (t >= 1.0f) {
      t = 1.0f;
      onDash_ = false;
    }

    Vector newPostion;
    newPostion.X = Lerp(dashStartPos_.X, dashEndPos_.X, t);
    newPostion.Y = startPosition_.Y;

    owner->SetPosition(newPostion);
  }
  // DASH END
  

  // BACKSTEP
  if (onBackStep_) {
    backstepTimer_ += curTick;
    float t = backstepTimer_ / backstepDuration_;

    if (t >= 1.0f) {
      t = 1.0f;
      onBackStep_ = false;
    }

    Vector newPostion;
    newPostion.X = Lerp(backstepStartPos_.X, backstepEndPos_.X, t);

    float height = -4 * backstepHeight_ * (t - 0.5f) * (t - 0.5f) + backstepHeight_;
    newPostion.Y = startPosition_.Y - height;

    owner->SetPosition(newPostion);
  }
  // BACKSTEP END

  // JUMP
  if (onJump_) {
    curJumpVelocity_.Y -= gravity_ * curTick;

    const Vector& ownerPosition = owner->GetPosition();

    Vector newPosition = {
        ownerPosition.X + curJumpVelocity_.X * curTick,  // X축 앞으로 이동
        ownerPosition.Y - curJumpVelocity_.Y             // Y축 점프
    };

    // 땅에 도착했는지 체크
    if (newPosition.Y >= startPosition_.Y) {
      newPosition.Y = startPosition_.Y;
      curJumpVelocity_ = {0.0f, 0.0f};
      onJump_ = false;
    }

    owner->SetPosition(newPosition);
  }
  // JUMP END

  // KNOCK BACK
  if (onKnockBack_) {

    curKnockBackVelocity_.Y -= gravity_ * curTick;
    curKnockBackVelocity_.X -= airResistance_ * curTick;
    const Vector& ownerPosition = owner->GetPosition();

    Vector newPosition = {
        ownerPosition.X + curKnockBackVelocity_.X,  // X축 앞으로 이동
        ownerPosition.Y - curKnockBackVelocity_.Y   // Y축 점프
    };

    if (newPosition.Y >= startPosition_.Y) {
      newPosition.Y = startPosition_.Y;
      curKnockBackVelocity_.Y = 0.0f;

      if (curKnockBackVelocity_.X <= knockBackMinVelocity_) {
        curKnockBackVelocity_.X = 0;
        onKnockBack_ = false;
      }
    }

    owner->SetPosition(newPosition);
  }
  // KNOCK BACK END

  moveDir_ = {0.0f, 0.0f};
}

bool MovementComponent::Initialize(const Vector& startPosition) {
  startPosition_ = startPosition;
  return true;
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

void MovementComponent::MoveBack(unsigned long long curTick, bool isRightDirection, bool isPushing) {
  if (false == isGrounded_) {
    return;
  }

  /*float weight = 1.0f;
  if (true == isPushing) {
    weight = 0.8f;
  }*/

  if (isRightDirection) {
    moveDir_ = Vector::Left * moveBackVelocity_ * curTick; /** weight;*/
  } else {
    moveDir_ = Vector::Right * moveBackVelocity_ * curTick; /** weight;*/
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
    curJumpVelocity_ = normalJumpForce_;
    onJump_ = true;
  }
}

void MovementComponent::JumpForward(bool isRightDirection, bool isRunning) {
  if (isGrounded_) {
    onJump_ = true;

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

  onBackStep_ = true;
}

void MovementComponent::Dash(bool isRightDirection, float dashDuration, float dashDistance) {
  if (false == isGrounded_) {
    return;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  onDash_ = true;
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

void MovementComponent::KnockBack(bool isRightDirection, const Vector& knockBackForce) {
  if (isRightDirection) {
    curKnockBackVelocity_ = {-knockBackForce.X, knockBackForce.Y};
  } else {
    curKnockBackVelocity_ = {knockBackForce.X, knockBackForce.Y};
  }

  if (onJump_) {
    onJump_ = false;
  }

  onKnockBack_ = true;
}
