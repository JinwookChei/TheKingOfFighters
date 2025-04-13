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

  void BackStep();

 private:
  Vector startPosition_;

  // MOVE
  const float moveVelocity_ = 0.5f;

  const float runVelocity_ = 1.0f;

  // BACK STEP
  bool onBackStep_;

  float backstepDuration = 200.0f;
  float backstepTimer = 0.0f;

  float backstepDistance = 250.0f;  // 전체 이동 거리
  float backstepHeight = 120.0f;    // 위로 뜨는 높이

  Vector backstepStartPos;
  Vector backstepEndPos;

  // JUMP
  bool isGrounded_;

  bool onJump_;

  float jumpVelocity_;

  const float gravity_ = 0.26f;

  const float jumpForce_ = 60.0f;
};
