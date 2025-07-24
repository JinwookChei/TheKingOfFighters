#pragma once

class AnimationHandler;
class MovementComponent;
class CommandComponent;
class CommandHandler;
class SkillComponent;
class SkillHandler;
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

  void UpdateAnimState(unsigned long long animState, unsigned long long modifier = ANIMMOD_NONE, bool isForce = false, int startFrame = 0, unsigned long long time = 0.0f);

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

  //void UpdatePrevAnimationIndex();

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

  const std::bitset<8>& InputPressBitSet() const;

  const std::bitset<8>& InputDownBitSet() const;

  const std::bitset<8>& InputUpsBitSet() const;

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

    const float GetCloseDistance() const;

 protected:
  std::array<int, 8> playerKeySet_;

  ImageRenderer* pRender_;

  AnimationHandler* pAnimationHandler_;

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

  SkillHandler* pSkillHandler_;

  CommandComponent* pCommandComponent_;

  CommandHandler* pCommandHandler_;

  ProjectileComponent* pProjectileComponent_;

  GhostEffect* pGhostEffect_;

  Vector characterScale_;

  std::bitset<8> inputPressBitSet_;

  std::bitset<8> inputDownBitSet_;

  std::bitset<8> inputUpBitSet_;

  KOFPlayer* pOpponentPlayer_;
  
  // TODO
  public:
  //unsigned int prevImageIndex_;

  private:
  bool isPlayer1_;

  bool isPlayerOnLeft_;

  bool isFacingRight_;

  bool isAtMapEdge_;

  bool isControlLocked_;

  const float closeDistance_ = 260.0f;
};