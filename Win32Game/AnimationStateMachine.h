#pragma once

class KOFPlayer;
class ImageRenderer;
class StateComponent;
class RestrictionComponent;
class MovementComponent;

enum TRANSITION_CONDITION : unsigned int {
  None = 0,
  AnimationEnd = 1 << 0,
  MovementRising = 1 << 1,
  MovementFalling = 1 << 2,
  MovementOnGround = 1 << 3,
  OpponentPlayerAttackFinished = 1 << 4
};

struct AnimTransitionRule {
  unsigned long long fromAnimState_ = 0;

  unsigned int transCondition1_ = TRANSITION_CONDITION::None;

  bool isEqualCondition1_ = true;

  unsigned long long toAnimState1_ = 0;

  unsigned int transCondition2_ = TRANSITION_CONDITION::None;

  bool isEqualCondition2_ = true;

  unsigned long long toAnimState2_ = 0;

  unsigned int transCondition3_ = TRANSITION_CONDITION::None;

  bool isEqualCondition3_ = true;

  unsigned long long toAnimState3_ = 0;

  void* searchHandle_ = nullptr;
};

class AnimationStateMachine
    : public ActorComponent {
 public:
  AnimationStateMachine();

  ~AnimationStateMachine();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize(
      KOFPlayer* pOwnerPlayer, 
      ImageRenderer* pImageRenderer, 
      StateComponent* pStateComponent, 
      MovementComponent* pMovementComponent,
      RestrictionComponent* pRestrictionComponent);

  bool RegistAnimTransition(
      unsigned long long fromAnimState,
      unsigned int transCondition1, bool isEqualCondition1, unsigned long long toAnimState1,
      unsigned int transCondition2 = None, bool isEqualCondition2 = true, unsigned long long toAnimState2 = 0,
      unsigned int transCondition3 = None, bool isEqualCondition3 = true, unsigned long long toAnimState3 = 0);

  void InitCondition();

  void UpdateAnimation();

  unsigned long long ExtractAnimationModifier();

 protected:
  KOFPlayer* pOwnerPlayer_;

  ImageRenderer* pOwnerRenderer_;

  StateComponent* pOwnerStateComponent_;

  RestrictionComponent* pOwnerRestrictionComponent_;

  MovementComponent* pOwnerMovementComponent_;

  HashTable animTransitionTable_;

  unsigned int transCondition_;
};
