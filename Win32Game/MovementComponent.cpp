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
      knockBackTimer_(0.0f),
      knockBackStartPos_({0.0f, 0.0f}),
      knockBackEndPos_({0.0f, 0.0f}),
      onStrongKnockBack_(false),
      onJumpKnockBack_(false) {
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
    knockBackTimer_ += curTick;
    float t = knockBackTimer_ / knockBackDuration_;

    if (t >= 1.0f) {
      t = 1.0f;
      onKnockBack_ = false;
    }

    Vector newPostion = owner->GetPosition();
    newPostion.X = Lerp(knockBackStartPos_.X, knockBackEndPos_.X, t);
    owner->SetPosition(newPostion);
  }

  if (onStrongKnockBack_) {
    knockBackTimer_ += curTick;
    float t = knockBackTimer_ / strongKnockBackDuration_;

    if (t >= 1.0f) {
      t = 1.0f;

      onStrongKnockBack_ = false;
    }

    Vector newPostion;
    newPostion.X = Lerp(knockBackStartPos_.X, knockBackEndPos_.X, t);

    float height = -4 * strongKnockBackHeight_ * (t - 0.5f) * (t - 0.5f) + strongKnockBackHeight_;
    newPostion.Y = startPosition_.Y - height;

    owner->SetPosition(newPostion);
  }

  if (onJumpKnockBack_)
  {
    curJumpKnockBackVelocity_.Y -= gravity_ * curTick;
    const Vector& ownerPosition = owner->GetPosition();

    Vector newPosition = {
        ownerPosition.X + curJumpVelocity_.X * curTick,  // X축 앞으로 이동
        ownerPosition.Y - curJumpVelocity_.Y             // Y축 점프
    };

    if (newPosition.Y >= startPosition_.Y)
    {
      newPosition.Y = startPosition_.Y;
      curJumpVelocity_ = {0.0f, 0.0f};
      onJumpKnockBack_ = false;
    }

    owner->SetPosition(newPosition);
  }
  // KNOCK BACK END

  moveDir_ = {0.0f, 0.0f};
}

void MovementComponent::Initialize(const Vector& startPosition) {
  startPosition_ = startPosition;
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
    curJumpVelocity_ = normalJumpForce_;
    // curJumpFowardVelocity_ = 0.0f;
    onJump_ = true;
  }
}

void MovementComponent::JumpForward(bool isRightDirection, bool isRunning) {
  if (isGrounded_) {
    // curJumpVelocity_ = jumpForce_;
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


  if (isRightDirection)
  {
    backstepStartPos_ = owner->GetPosition();
    backstepEndPos_ = owner->GetPosition();
    backstepEndPos_.X -= backstepDistance_;
  }
  else
  {
    backstepStartPos_ = owner->GetPosition();
    backstepEndPos_ = owner->GetPosition();
    backstepEndPos_.X += backstepDistance_;
  }
  
  onBackStep_ = true;
}

void MovementComponent::KnockBack(bool isRightDirection) {
  if (false == isGrounded_) {
    return;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  knockBackTimer_ = 0.0f;

  if (isRightDirection)
  {
    knockBackStartPos_ = owner->GetPosition();
    knockBackEndPos_ = owner->GetPosition();
    knockBackEndPos_.X -= knockBackDistance_;
  }
  else
  {
    knockBackStartPos_ = owner->GetPosition();
    knockBackEndPos_ = owner->GetPosition();
    knockBackEndPos_.X += knockBackDistance_;
  }

  onKnockBack_ = true;
}

void MovementComponent::StrongKnockBack(bool isRightDirection) {
  if (false == isGrounded_) {
    return;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  knockBackTimer_ = 0.0f;


  if (isRightDirection)
  {
    knockBackStartPos_ = owner->GetPosition();
    knockBackEndPos_ = owner->GetPosition();
    knockBackEndPos_.X -= strongKnockBackDistance_;
  }
  else
  {
    knockBackStartPos_ = owner->GetPosition();
    knockBackEndPos_ = owner->GetPosition();
    knockBackEndPos_.X += strongKnockBackDistance_;
  }
  
  onStrongKnockBack_ = true;
}

void MovementComponent::JumpKnockBack(bool isRightDirection) {
  if (isGrounded_) {
    return;
  }

  if (isRightDirection)
  {
    curJumpKnockBackVelocity_ = {-jumpKnockBackForce_.X, jumpKnockBackForce_.Y};
  } else {
    curJumpKnockBackVelocity_ = {jumpKnockBackForce_.X, jumpKnockBackForce_.Y};
  }

  onJump_ = false;
  onJumpKnockBack_ = true;
}
