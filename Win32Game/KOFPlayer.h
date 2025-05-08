#pragma once
#include <vector>

class MovementComponent;
class CommandComponent;
class ProjectileComponent;
class HealthComponent;


enum PlayerAnimState {
  PAS_Start = 0,
  PAS_Idle,
  PAS_Seat,
  PAS_FrontWalk,
  PAS_BackWalk,
  PAS_BackStep,
  PAS_Run,
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

  void Tick(unsigned long long curTick) override;

  virtual void Initialize(const Vector& position, bool useCameraPosition, bool isFacingRight);

  virtual void InputUpdate(unsigned long long curTick);

  HealthComponent* GetHealthComponent() const;

  virtual void CommendUpdate();

  virtual void CollisionBoundUpdate();

  virtual bool CollisionHitUpdate();

  virtual bool CollisionAttackUpdate(Actor** outTarget);

  virtual bool CollisionPushUpdate();

  void CollisionReset();

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

  Vector characterScale_;

 public:
  int animState_;

  bool isFacingRight_;

  bool isAtMapEdge_;
};