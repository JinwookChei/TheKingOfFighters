#pragma once
#include "KOFPlayer.h"
#include "StateComponent.h"
#include "MovementComponent.h"

enum TRANSITION_CONDITION : unsigned int {
  None = 0,
  AnimationEnd = 1 << 0,
  MovementRising = 1 << 1,
  MovementFalling = 1 << 2,
  MovementOnGround = 1 << 3,
  OpponentPlayerAttackFinished = 1 << 4
};

struct AnimTransitionRule {
  unsigned long long curAnimState_ = 0;

  unsigned int transCondition1_ = TRANSITION_CONDITION::None;

  bool equalCondition1_ = true;

  unsigned long long nextAnimState1_ = 0;

  unsigned int transCondition2_ = TRANSITION_CONDITION::None;

  bool equalCondition2_ = true;

  unsigned long long nextAnimState2_ = 0;

  unsigned int transCondition3_ = TRANSITION_CONDITION::None;

  bool equalCondition3_ = true;

  unsigned long long nextAnimState3_ = 0;

  void* searchHandle_ = nullptr;
};

class AnimationHandler
    : public ActorComponent {
 public:
  AnimationHandler();

  ~AnimationHandler();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize(KOFPlayer* ownerPlayer, ImageRenderer* imageRenderer_, StateComponent* stateComponent, MovementComponent* movementComponent);

  bool CallCreateAnimation(
      unsigned long long animationTag,
      unsigned long long imageIndex,
      unsigned int startIndex,
      unsigned int endIndex,
      unsigned long long interval,
      bool loop,
      unsigned long long loopStartFrame);

  bool CallCreateAnimation(
      unsigned long long animationTag,
      unsigned long long imageIndex,
      const std::vector<unsigned int>& indices,
      unsigned long long interval,
      bool loop,
      unsigned long long loopStartFrame);

  bool CallCreateAnimation(
      unsigned long long animationTag,
      unsigned long long imageIndex,
      const std::vector<unsigned int>& indices,
      const std::vector<unsigned long long> intervals,
      bool loop,
      unsigned long long loopStartFrame);

  virtual bool RegistAnimations() = 0;

  unsigned long long CurrentAnimationState() const;

  void SetCurrentAnimationState(unsigned long long animationState);

  unsigned long long CurrentAnimationModifier() const;

  void SetCurrentAnimationModifier(unsigned long long animationModifier);

  void UpdatePrevImageIndex();

  unsigned int CurrentImageIndex() const;

  unsigned int PrevImageIndex() const;

  bool RegistAnimTransition(
      unsigned long long curAnimState,
      unsigned int transCondition1, bool equalCondition1, unsigned long long nextAnimState1,
      unsigned int transCondition2 = None, bool equalCondition2 = true, unsigned long long nextAnimState2 = 0,
      unsigned int transCondition3 = None, bool equalCondition3 = true, unsigned long long nextAnimState3 = 0);

  void InitCondition();

  void UpdateAnimation();


 protected:
  KOFPlayer* pOwnerPlayer_;

  ImageRenderer* pOwnerRenderer_;

  StateComponent* pOwnerStateComponent_;

  MovementComponent* pOwnerMovementComponent_;

  unsigned long long curAnimationState_;

  unsigned long long curAnimationModifier_;

  unsigned int prevImageIndex_;

  HashTable animTransitionTable_;

  unsigned int transCondition_;
};
