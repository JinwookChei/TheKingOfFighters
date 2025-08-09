#pragma once

class InputController;
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
class RestrictionComponent;
class HitHandlerComponent;
class GhostEffect;


class SkillTest;


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

  void UpdateCollisionBoundScale();

  void UpdateAttack();

  bool CheckAttackCollision(CollisionComponent** outTargetCollision);

  void HitEvent(const AttackInfo* damageInfo);

  bool CheckPushCollision();

  void CollisionReset();

  virtual Vector CharacterScale() const;

  virtual void SetCharacterScale(const Vector& scale);

  void PushOverlappingPlayer();

  bool IsPlayer1() const;

  void SetPlayerOnLeft(bool isPlayerOnLeft);

  bool PlayerOnLeft() const;

  int PlayerOnLeftFlag() const;

  int FacingRightFlag() const;

  bool FacingRight() const;

  void SetFacingRight(bool isFacingRight);

  void SetIsAtMapEdge(bool isAtEdge);

  bool IsAtMapEdge() const;

  virtual void CompareInputBitset();

  KOFPlayer* GetOpponentPlayer() const;

  StateComponent* GetPlayerStateComponent() const;

  MovementComponent* GetMovementComponent() const;

  void ReceiveClampedWidthOffset(float clampOffset);

  const float GetCloseDistance() const;

 protected:

  ImageRenderer* pRender_;

  AnimationHandler* pAnimationHandler_;

  InputController* pInputController_;

  ImageRenderer* pUI_;

  SoundChannel soundChannel_;

  MovementComponent* pMovementComponent_;

  SoundTable* pSoundTable_;

  AttackTable* pAttackTable_;

  HealthComponent* pHealthComponent_;

  MPComponent* pMPComponent_;

  StateComponent* pStateComponent_;

  RestrictionComponent* pRestrictionComponent_;

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

  KOFPlayer* pOpponentPlayer_;
  
  SkillTest* skillTest_;

  private:
  bool isPlayer1_;

  bool isPlayerOnLeft_;

  bool isFacingRight_;

  bool isAtMapEdge_;

  const float closeDistance_ = 260.0f;
};