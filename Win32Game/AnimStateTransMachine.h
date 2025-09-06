#pragma once

class KOFPlayer;
class ImageRenderer;
class StateComponent;
class RestrictionComponent;
class MovementComponent;

enum ANIM_TRANS_COND : unsigned int {
  None = 0,
  AnimationEnd = 1 << 0,
  MovementRising = 1 << 1,
  MovementFalling = 1 << 2,
  MovementOnGround = 1 << 3,
  OpponentPlayerAttackFinished = 1 << 4
};

struct AnimTransRule {
  unsigned int transCondition_ = ANIM_TRANS_COND::None;

  unsigned long long toAnimState_ = 0;

  void* searchHandle_ = nullptr;
};


struct AnimTransState {
  unsigned long long fromAnimState_ = 0;

  std::vector<AnimTransRule> animTransRules_;

  void* searchHandle_ = nullptr;
};

class AnimaStateTransMachine
    : public ActorComponent {
 public:
  AnimaStateTransMachine();

  ~AnimaStateTransMachine();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize(
      KOFPlayer* pOwnerPlayer, 
      ImageRenderer* pImageRenderer, 
      StateComponent* pStateComponent, 
      MovementComponent* pMovementComponent,
      RestrictionComponent* pRestrictionComponent);

  bool RegistAnimTransition(const AnimTransState& animTransState);

  void ClearCurrentTransCondition();

  void UpdateTransition();

  unsigned long long ExtractAnimationModifier();

 protected:
  KOFPlayer* pOwnerPlayer_;

  ImageRenderer* pOwnerRenderer_;

  StateComponent* pOwnerStateComponent_;

  RestrictionComponent* pOwnerRestrictionComponent_;

  MovementComponent* pOwnerMovementComponent_;

  HashTable animTransStateTable_;

  unsigned int curTickTransCond;
};
