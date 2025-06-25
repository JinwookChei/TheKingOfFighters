#pragma once
#include <vector>
#include <array>
#include <bitset>

class MovementComponent;
class CommandComponent;
class SkillComponent;
class ProjectileComponent;
class AttackTable;
class AttackInfo;
class HealthComponent;
class StateComponent;
class HitHandlerComponent;
class GhostEffect;

enum PLAYER_ANIM_STATE {
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
  PAS_MAX
};

class KOFPlayer
    : public Player {
 public:
  KOFPlayer();

  ~KOFPlayer();

  virtual void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  virtual void Initialize(const Vector& position, bool useCameraPosition, bool isFacingRight, KOFPlayer* opponentPlayer);

  void UpdateAnimState(int animState /*unsigned long long animationTag, int startFrame = 0, unsigned long long time = 0.0f*/);

  const HealthComponent* GetHealthComponent() const;

  void UpdateInput();

  void UpdateCommand();

  void UpdateCollisionBoundScale();

  void UpdateAttack();

  bool CheckAttackCollision(CollisionComponent** outTargetCollision);

  void HitEvent(const AttackInfo* damageInfo);

  bool CheckPushCollision();

  void CollisionReset();

  void UpdatePrevAnimationIndex();

  virtual Vector CharacterScale() const;

  virtual void SetCharacterScale(const Vector& scale);

  void PushOverlappingPlayer();

  int FacingRightFlag() const;

  bool FacingRight() const;

  void SetFacingRight(bool isFacingRight);

  void SetIsAtMapEdge(bool isAtEdge);

  bool IsAtMapEdge() const;

  virtual void CompareInputBitset();

  void ResetInputBitSet();

  bool IsEqualInputBitSet(const std::bitset<8>& myBitSet, const std::bitset<8>& compareTarget);

  bool IsContainInputBitSet(const std::bitset<8>& myBitSet, const std::bitset<8>& compareTarget);

  KOFPlayer* GetOpponentPlayer() const;

 protected:
  std::array<int, 8> playerKeySet_;

  ImageRenderer* pRender_;

  MovementComponent* pMovementComponent_;

  AttackTable* pAttackTable_;

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
  unsigned long long animState_;

  unsigned int prevImageIndex_;

  bool isFacingRight_;

  bool isAtMapEdge_;

  std::bitset<8> inputPressBitSet_;

  std::bitset<8> inputUpBitSet_;

  KOFPlayer* opponentPlayer_;
};