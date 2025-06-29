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

enum PLAYER_ANIM_TYPE : unsigned long long{
  PLAYER_ANIMTYPE_None = 0ULL,
  PLAYER_ANIMTYPE_Start,
  PLAYER_ANIMTYPE_Idle,
  PLAYER_ANIMTYPE_SeatDown,
  PLAYER_ANIMTYPE_SeatUp,
  PLAYER_ANIMTYPE_FrontWalk,
  PLAYER_ANIMTYPE_BackWalk,
  PLAYER_ANIMTYPE_BackStep,
  PLAYER_ANIMTYPE_Run,
  PLAYER_ANIMTYPE_RunEnd,
  PLAYER_ANIMTYPE_Jump,
  PLAYER_ANIMTYPE_HeavyPunch,
  PLAYER_ANIMTYPE_LightPunch,
  PLAYER_ANIMTYPE_HeavyKick,
  PLAYER_ANIMTYPE_LightKick,
  PLAYER_ANIMTYPE_HeavyPunch_Seat,
  PLAYER_ANIMTYPE_LightPunch_Seat,
  PLAYER_ANIMTYPE_HeavyKick_Seat,
  PLAYER_ANIMTYPE_LightKick_Seat,
  PLAYER_ANIMTYPE_HitHigh,
  PLAYER_ANIMTYPE_HitLow,
  PLAYER_ANIMTYPE_HitStrong,
  PLAYER_ANIMTYPE_HitWhileJumping,
  PLAYER_ANIMTYPE_Max
};

enum PLAYER_ANIM_MODIFIER : unsigned long long {
  ANIMMOD_NONE = 0,
  ANIMMOD_FLIPPED = 1ULL << 63,
  ANIMMOD_COLOR_CHANGED = 1ULL << 62
};

class KOFPlayer
    : public Player {
 public:
  KOFPlayer();

  ~KOFPlayer();

  virtual void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  virtual void Initialize(const Vector& position, bool useCameraPosition, bool isFacingRight, KOFPlayer* opponentPlayer);

  void UpdateAnimState(unsigned long long animState, int startFrame = 0, unsigned long long time = 0.0f);

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
    
  bool IsControlLocked() const;

  void SetControlLocked(bool bLocked);


  //void TestMakeIMGKey(IMAGE_KEY key, IMAGE_MODIFIER mod);


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

  unsigned long long animState_;

  unsigned int prevImageIndex_;

  bool isFacingRight_;

  bool isAtMapEdge_;

  std::bitset<8> inputPressBitSet_;

  std::bitset<8> inputUpBitSet_;

  KOFPlayer* pOpponentPlayer_;

  bool isControlLocked_;
};