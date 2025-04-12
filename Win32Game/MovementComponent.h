#pragma once

class MovementComponent final
    : public ActorComponent {
 public:
  MovementComponent();
  ~MovementComponent();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void Initialize(const Vector& startPosition);

  void Jump();

 private:
  Vector startPosition_;

  float jumpVelocity_;

  const float gravity_;

  const float jumpForce_;
  
  bool isGrounded_;
};
