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
class SoundTable;
class HealthComponent;
class MPComponent;
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

  void CallCreateAnimation(
      unsigned long long animationTag,
      unsigned long long imageIndex,
      unsigned int startIndex,
      unsigned int endIndex,
      unsigned long long interval,
      bool loop,
      unsigned long long loopStartFrame);

  void CallCreateAnimation(
      unsigned long long animationTag,
      unsigned long long imageIndex,
      const std::vector<unsigned int>&indices,
      unsigned long long interval,
      bool loop,
      unsigned long long loopStartFrame);

  void CallCreateAnimation(
      unsigned long long animationTag,
      unsigned long long imageIndex,
      const std::vector<unsigned int>& indices,
      const std::vector<unsigned long long> intervals,
      bool loop,
      unsigned long long loopStartFrame);
      

  void UpdateAnimState(unsigned long long animState, PLAYER_ANIM_MODIFIER modifier = ANIMMOD_NONE, bool isForce = false, int startFrame = 0, unsigned long long time = 0.0f);

  const HealthComponent* GetHealthComponent() const;

  const MPComponent* GetMPComponent() const;

  virtual void UpdateInput();

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

  int PlayerOnLeftFlag() const;

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

  MovementComponent* GetMovementComponent() const;

  bool IsControlLocked() const;

  void SetControlLocked(bool bLocked);

  void ReceiveClampedWidthOffset(float clampOffset);

 protected:
  std::array<int, 8> playerKeySet_;

  ImageRenderer* pRender_;

  ImageRenderer* pUI_;

  SoundChannel soundChannel_;

  MovementComponent* pMovementComponent_;

  SoundTable* pSoundTable_;

  AttackTable* pAttackTable_;

  HealthComponent* pHealthComponent_;

  MPComponent* pMPComponent_;

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

  std::bitset<8> inputDownBitSet_;

  std::bitset<8> inputUpBitSet_;

  KOFPlayer* pOpponentPlayer_;

  bool isControlLocked_;
};