#pragma once

//enum MovementState
//{
//    MS_None = -1,
//    MS_Idle = 0,
//    MS_Move
//};


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

  void Run(unsigned long long curTick, bool isRightDirection, bool isPushing);

  void Jump();

  void JumpForward(bool isRightDirection, bool isRunning);

  void BackStep(bool isRightDirection);

  void KnockBack(bool isRightDirection);

  void SetKnockBackForce(const Vector& knockBackForce);

  //void StrongKnockBack(bool isRightDirection);

  //void JumpKnockBack(bool isRightDirection);

 private:
  Vector startPosition_;

  // MOVE
  Vector moveDir_;
  const float moveVelocity_ = 0.5f;
  const float runVelocity_ = 1.5f;

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
  const float airResistance_ = 0.12f;

  Vector curJumpVelocity_;
  const Vector normalJumpForce_ = {0.0f, 75.0f};
  const Vector fowardJumpForceInWalking_ = {0.7f, 75.0f};
  const Vector fowardJumpForceInRunning_ = {1.1f, 75.0f};


  // KNOCK BACK 
  bool onKnockBack_;
  Vector knockBackForce_;
  Vector curKnockBackVelocity_;
  

  // ragacy
  //bool onKnockBack_;
  //float knockBackTimer_;
  //const float knockBackDuration_ = 170.0f; // TODO : 넉백 애니메이션의 Duration이랑 맞춰야함.
  //const float knockBackDistance_ = 280.0f;
  //Vector knockBackStartPos_;
  //Vector knockBackEndPos_;
  //bool onStrongKnockBack_;
  //const float strongKnockBackDuration_ = 530.0f; // TODO : 넉백 애니메이션의 Duration이랑 맞춰야함.
  //const float strongKnockBackDistance_ = 800.0f;
  //const float strongKnockBackHeight_ = 350.0f;
  // TODO : 초기화.
  //bool onJumpKnockBack_;
  //Vector curJumpKnockBackVelocity_;
  //const Vector jumpKnockBackForce_ = {30.0f, 0.0f};
  //const float airResistance_ = 0.12f; // 아직 사용안함.
  //const Vector jumpKnockBackForce_ = {30.0f, 0.0f};

};
