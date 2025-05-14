#pragma once
#include <vector>

class MovementComponent;
class CommandComponent;
class ProjectileComponent;
class HealthComponent;
class HitHandlerComponent;
class GhostEffect;

enum PlayerAnimState {
  PAS_Start = 0,
  PAS_Idle,
  PAS_SeatDown,
  PAS_SeatUp,
  PAS_FrontWalk,
  PAS_BackWalk,
  PAS_BackStep,
  PAS_Run,
  PAS_RunEnd,
  PAS_Jump,
  PAS_HeavyPunch,
  PAS_LightPunch,
  PAS_HeavyKick,
  PAS_LightKick,
  PAS_HitTop,
  PAS_HitBottom,
  PAS_HitStrong,
  PAS_HitWhileJumping,
  PAS_Skill1,
  PAS_MAX
};

class KOFPlayer
    : public Player {
 public:
  KOFPlayer();

  ~KOFPlayer();

  virtual void BeginPlay() override;
  
  void Tick(unsigned long long deltaTick) override;

  virtual void Initialize(const Vector& position, bool useCameraPosition, bool isFacingRight);

  const HealthComponent* GetHealthComponent() const;

  virtual void HitEvent(float damage, const Vector& knockBackForce);

  virtual void InputUpdate(unsigned long long deltaTick);

  virtual void CommendUpdate();

  void CollisionBoundUpdate();

  virtual bool CheckAttackCollision(CollisionComponent** outTargetCollision);

  virtual bool CollisionPushUpdate();

  void CollisionReset();

  virtual void TriggerEventAtAnimationIndex();

  virtual Vector CharacterScale() const;

  virtual void SetCharacterScale(const Vector& scale);

  void PushOverlappingPlayer();

  int FacingRightFlag() const;

  bool FacingRight() const;

  void SetFacingRight(bool isFacingRight);

  void SetIsAtMapEdge(bool isAtEdge);

  bool IsAtMapEdge() const;

 protected:
  ImageRenderer* pRender_;

  MovementComponent* pMovementComponent_;

  HealthComponent* pHealthComponent_;

  CollisionComponent* pHitBoxTop_;

  CollisionComponent* pHitBoxBottom_;

  CollisionComponent* pAttackBox_;

  CollisionComponent* pPushBox_;

  CollisionComponent* pGrabBox_;

  CommandComponent* pCommandComponent_;

  ProjectileComponent* pProjectileComponent_;

  GhostEffect* pGhostEffect_;

  Vector characterScale_;

 public:
  int animState_;

  bool isFacingRight_;

  bool isAtMapEdge_;
};