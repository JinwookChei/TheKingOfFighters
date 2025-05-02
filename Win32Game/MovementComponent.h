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

  float jumpVelocity_;

  const float gravity_ = 0.26f;

  const float jumpForce_ = 60.0f;
};
