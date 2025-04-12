#pragma once

class MovementComponent final
    : public ActorComponent {
 public:
  MovementComponent();
  ~MovementComponent();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void Initialize(const Vector& startPosition);

  void Move(unsigned long long curTick, bool isFoward);

  void Jump();

 private:
  Vector startPosition_;

  // MOVE
  const float moveVelocity_ = 500.0f;

  const float runVelocity_ = 1000.0f;

  const float backStepVelocity_ = 3000.0f;

  // JUMP
  bool isGrounded_;

  float jumpVelocity_;

  const float gravity_ = 260.0f;

  const float jumpForce_ = 60.0f;
  
};
