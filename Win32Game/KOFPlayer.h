#pragma once
#include <vector>
#include <array>
#include <bitset>

class MovementComponent;
class CommandComponent;
class SkillComponent;
class ProjectileComponent;
class AttackTable;
struct AttackInfo;
class HealthComponent;
class StateComponent;
class HitHandlerComponent;
class GhostEffect;

class KOFPlayer
    : public Player {
 public:
  KOFPlayer();

  ~KOFPlayer();

  virtual void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  virtual void Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer);

  void UpdateAnimState(unsigned long long animState, PLAYER_ANIM_MODIFIER modifier = ANIMMOD_NONE, int startFrame = 0, unsigned long long time = 0.0f);

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

  void SetPlayerOnLeft(bool isPlayerOnLeft);

  bool PlayerOnLeft() const;

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

  StateComponent* GetPlayerStateComponent() const;
    
  bool IsControlLocked() const;

  void SetControlLocked(bool bLocked);

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

  public:
  bool isPlayer1_;

  unsigned long long animState_;

  unsigned int prevImageIndex_;

  bool isPlayerOnLeft_;

  bool isFacingRight_;

  bool isAtMapEdge_;

  std::bitset<8> inputPressBitSet_;

  std::bitset<8> inputUpBitSet_;

  KOFPlayer* pOpponentPlayer_;

  bool isControlLocked_;
};