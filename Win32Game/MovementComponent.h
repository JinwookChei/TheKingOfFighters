#pragma once
#include <bitset>
#include <initializer_list>

enum MOVEMENT_STATE {
  MOVSTATE_Move = 0,
  MOVSTATE_Dash,
  MOVSTATE_BackStep,
  MOVSTATE_Jump,
  MOVSTATE_KnockBack,
  MOVSTATE_Max
};

class MovementComponent final
    : public ActorComponent {
 public:
  MovementComponent();
  ~MovementComponent();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize(const Vector& startPosition);

  bool EqualMovementState(std::initializer_list<MOVEMENT_STATE> movStateList);
  
  bool ContainMovementState(std::initializer_list<MOVEMENT_STATE> movStateList);

  void UpdateMove(unsigned long long deltaTick);

  void Move(bool isRightDirection);

  void MoveBack(bool isRightDirection);

  void Run(bool isRightDirection);

  void UpdateJump(unsigned long long deltaTick);

  void Jump(bool isRightDirection = true, Vector normalJumpForce = {0.0f, 75.0f});

  void JumpForward(bool isRightDirection, bool isRunning);

  void UpdateGroundedState();

  bool GetIsGround() const;

  void UpdateBackStep(unsigned long long deltaTick);

  void BackStep(bool isRightDirection);

  void UpdateDash(unsigned long long deltaTick);

  void Dash(bool isRightDirection, float dashDuration, float dashDistance);

  void StopDash();

  void UpdateKnockBack(unsigned long long deltaTick);

  void KnockBack(bool isRightDirection, const Vector& knockBackForce);

  float GetPushTriggerDistance() const;

  void ApplyPushWeight(float pushWeight);

  void ClampPositionToLevelBoundary();

  void ClampPositionToScreenBoundary();

  void BroadcastClampedWidthOffset();

  void ApplyClampedWidthOffset(float clampOffset);

 private:
  Vector startPosition_;

  Vector preFramePosition_;

  std::bitset<MOVSTATE_Max> movementStateBitset_;

  // MOVE
  Vector moveDir_;
  const float moveVelocity_ = 0.5f;
  const float runVelocity_ = 1.5f;

  // MOVE BACK
  const float moveBackVelocity_ = 0.3f;

  // DASH
  float dashTimer_;
  float dashDuration_;
  float dashDistance_;
  Vector dashStartPos_;
  Vector dashEndPos_;

  // BACK STEP
  float backstepTimer_;
  const float backstepDuration_ = 170.0f;
  const float backstepDistance_ = 280.0f;
  const float backstepHeight_ = 110.0f;
  Vector backstepStartPos_;
  Vector backstepEndPos_;

  // JUMP
  bool isGrounded_;
  const float gravity_ = 0.36f;
  const float airResistance_ = 0.06f;

  Vector curJumpVelocity_;
  const Vector fowardJumpForceInWalking_ = {0.7f, 75.0f};
  const Vector fowardJumpForceInRunning_ = {1.1f, 75.0f};

  // KNOCK BACK
  Vector curKnockBackVelocity_;
  const float knockBackMinVelocity_ = 10.0f;

  // PUSH
  float pushWeight_;
  
  const float pushTriggerDistance_ = 150.0f;

  // ClampOffset
  float clampedWidthOffset_;
};
