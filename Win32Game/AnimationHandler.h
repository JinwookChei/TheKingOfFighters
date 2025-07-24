#pragma once
#include "KOFPlayer.h"
#include "StateComponent.h"
#include "MovementComponent.h"

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

protected:
  KOFPlayer* pOwnerPlayer_;

  ImageRenderer* pOwnerRenderer_;

  StateComponent* pOwnerStateComponent_;

  MovementComponent* pOwnerMovementComponent_;

  unsigned long long curAnimationState_;

  unsigned long long curAnimationModifier_;

  unsigned int prevImageIndex_;

};
