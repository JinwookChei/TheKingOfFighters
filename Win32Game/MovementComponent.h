#pragma once

class MovementComponent final
    : public ActorComponent {
 public:
  MovementComponent();
  ~MovementComponent();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void Initialize(const Vector& startPosition);

  Vector GetMoveDir() const;

  void Move(unsigned long long curTick, bool isRightDirection, bool isPushing);

  void Run(unsigned long long curTick, bool isRightDirection, bool isPushing);

  void Jump();

  void JumpForward(bool isRightDirection, bool isRunning);

  void BackStep(int facingDirection);

 private:
  Vector startPosition_;

  // MOVE
  Vector moveDir_;

  const float moveVelocity_ = 0.5f;

  const float runVelocity_ = 1.5f;

  // BACK STEP
  bool onBackStep_;

  float backstepDuration = 170.0f;
  float backstepTimer = 0.0f;

  float backstepDistance = 280.0f;
  float backstepHeight = 110.0f;

  Vector backstepStartPos;
  Vector backstepEndPos;

  // JUMP
  bool isGrounded_;

  bool onJump_;

  float curJumpVelocity_;

  const float gravity_ = 0.36f;

  const float jumpForce_ = 75.0f;

  // JUMP FOWARD
  float curJumpFowardVelocity_;

  const float jumpFowardVelocityInWalking_ = 0.7f;

  const float jumpFowardVelocityInRunning_ = 1.1f;
};
