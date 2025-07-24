#pragma once
#include <bitset>
#include <initializer_list>

enum MOVEMENT_STATE {
  MOVSTATE_Idle = 0,
  MOVSTATE_Move,
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

  MOVEMENT_STATE GetMovementState() const;

  void UpdateIdle(unsigned long long deltaTick);

  void UpdateMove(unsigned long long deltaTick);

  void Move(bool isRightDirection);

  void MoveBack(bool isRightDirection);

  void Run(bool isRightDirection);

  void UpdateJump(unsigned long long deltaTick);

  void Jump();

  void Jump(bool isRightDirection, const Vector& jumpForce_);

  void JumpForward(bool isRightDirection, bool isRunning);

  void UpdateGroundedState();

  bool IsOnGround() const;

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

  void UpdatePreframePosition();

  bool IsFalling() const;

  bool IsRising() const;

 private:
  Vector startPosition_;

  Vector preFramePosition_;

  MOVEMENT_STATE curMovementState_;

  Vector curVelocity_;

  // MOVE
  Vector moveDir_;
  const float moveVelocity_ = 0.7f;
  const float runVelocity_ = 1.5f;

  // MOVE BACK
  const float moveBackVelocity_ = 0.4f;

  // DASH
  float dashTimer_;
  float dashDuration_;
  float dashDistance_;
  Vector dashStartPos_;
  Vector dashEndPos_;

  // BACK STEP
  float backStepTimer_;
  const float backStepDuration_ = 180.0f;
  const float backStepDistance_ = 340.0f;
  const float backStepHeight_ = -200.0f;
  Vector backStepStartPos_;
  Vector backStepEndPos_;

  // JUMP
  bool isOnGrounded_;
  const float gravity_ = 0.45f;
  const float airResistance_ = 0.09f;

  const Vector normalJumpForce_ = {0.0f, -5.5f};
  const Vector fowardJumpForceInWalking_ = {0.8f, -5.5f};
  const Vector fowardJumpForceInRunning_ = {1.3f, -5.5f};

  // KNOCK BACK
  Vector curKnockBackVelocity_;
  const float knockBackMinVelocity_ = 10.0f;

  // PUSH
  float pushWeight_;
  
  const float pushTriggerDistance_ = 150.0f;

  // ClampOffset
  float clampedWidthOffset_;

  // Sound
  SoundChannel movementSoundChannel_;
};
