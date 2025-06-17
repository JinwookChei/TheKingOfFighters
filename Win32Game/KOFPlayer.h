#pragma once
#include <vector>
#include <bitset>

class MovementComponent;
class CommandComponent;
class SkillComponent;
class ProjectileComponent;
class HealthComponent;
class StateComponent;
class HitHandlerComponent;
class GhostEffect;



enum PlayerAnimState {
  PAS_None = -1,
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

  void ChangeAnimState(/*unsigned long long animationTag, int startFrame = 0, unsigned long long time = 0.0f*/);

  const HealthComponent* GetHealthComponent() const;

  virtual void HitEvent(float damage, const Vector& knockBackForce);

  virtual void InputUpdate(unsigned long long deltaTick);

  virtual void CommandUpdate();

  void CollisionBoundScaleUpdate();

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

  virtual void CompareInputBitset(unsigned long long curTick);
  
  void ResetInputBitSet();

  bool IsEqualInputBitSet(const std::bitset<8>& myBitSet, const std::bitset<8>& compareTarget);

  bool IsContainInputBitSet(const std::bitset<8>& myBitSet, const std::bitset<8>& compareTarget);

 protected:
  ImageRenderer* pRender_;

  MovementComponent* pMovementComponent_;

  HealthComponent* pHealthComponent_;
  
  StateComponent* pStateComponent_;

  CollisionComponent* pHitBoxTop_;

  CollisionComponent* pHitBoxBottom_;

  CollisionComponent* pAttackBox_;

  CollisionComponent* pPushBox_;

  CollisionComponent* pGrabBox_;

  SkillComponent* pSkillComponent_;

  CommandComponent* pCommandComponent_;

  ProjectileComponent* pProjectileComponent_;

  GhostEffect* pGhostEffect_;


  Vector characterScale_;

protected:
  int animState_;

  int reservedAnimState_;

  bool isFacingRight_;

  bool isAtMapEdge_;

  std::bitset<8> inputPressBitSet_;

  std::bitset<8> inputUpBitSet_;
};