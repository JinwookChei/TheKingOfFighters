#pragma once


class MovementComponent final
    : public ActorComponent {
 public:
  MovementComponent();
  ~MovementComponent();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  bool Initialize(const Vector& startPosition);

  Vector GetMoveDir() const;

  void Move(unsigned long long curTick, bool isRightDirection, bool isPushing);

  void MoveBack(unsigned long long curTick, bool isRightDirection, bool isPushing);

  void Run(unsigned long long curTick, bool isRightDirection, bool isPushing);

  void Jump();

  void JumpForward(bool isRightDirection, bool isRunning);

  void BackStep(bool isRightDirection);

  void KnockBack(bool isRightDirection, const Vector& knockBackForce);

 private:
  Vector startPosition_;

  // MOVE
  Vector moveDir_;
  const float moveVelocity_ = 0.5f;
  const float runVelocity_ = 1.5f;

  // MOVE BACK
  const float moveBackVelocity_ = 0.3f;


  // BACK STEP
  bool onBackStep_;
  float backstepTimer_;
  const float backstepDuration_ = 170.0f;
  const float backstepDistance_ = 280.0f;
  const float backstepHeight_ = 110.0f;
  Vector backstepStartPos_;
  Vector backstepEndPos_;

  // JUMP
  bool isGrounded_;
  bool onJump_;
  const float gravity_ = 0.36f;
  const float airResistance_ = 0.06f;

  Vector curJumpVelocity_;
  const Vector normalJumpForce_ = {0.0f, 75.0f};
  const Vector fowardJumpForceInWalking_ = {0.7f, 75.0f};
  const Vector fowardJumpForceInRunning_ = {1.1f, 75.0f};


  // KNOCK BACK 
  bool onKnockBack_;
  Vector curKnockBackVelocity_;
  const float knockBackMinVelocity_ = 15.0f;
};
