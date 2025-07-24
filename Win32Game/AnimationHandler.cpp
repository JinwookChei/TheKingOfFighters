#include "stdafx.h"
#include "AnimationHandler.h"

AnimationHandler::AnimationHandler()
    : pOwnerPlayer_(nullptr),
      pOwnerRenderer_(nullptr),
      pOwnerStateComponent_(nullptr),
      pOwnerMovementComponent_(nullptr),
      curAnimationState_(PLAYER_ANIMTYPE_None),
      curAnimationModifier_(ANIMMOD_NONE),
      prevImageIndex_(0) {
}

AnimationHandler::~AnimationHandler() {
}

void AnimationHandler::BeginPlay() {
}

void AnimationHandler::Tick(unsigned long long deltaTick) {

}

bool AnimationHandler::Initialize(KOFPlayer* ownerPlayer, ImageRenderer* imageRenderer_, StateComponent* stateComponent, MovementComponent* movementComponent) {
  if (nullptr == ownerPlayer) {
    return false;
  }
  if (nullptr == imageRenderer_) {
    return false;
  }
  if (nullptr == stateComponent) {
    return false;
  }
  if (nullptr == movementComponent) {
    return false;
  }

  pOwnerPlayer_ = ownerPlayer;
  pOwnerRenderer_ = imageRenderer_;
  pOwnerStateComponent_ = stateComponent;
  pOwnerMovementComponent_ = movementComponent;
  return true;
}

bool AnimationHandler::CallCreateAnimation(
    unsigned long long animationTag,
    unsigned long long imageIndex,
    unsigned int startIndex,
    unsigned int endIndex,
    unsigned long long interval,
    bool loop,
    unsigned long long loopStartFrame) {
  if (nullptr == pOwnerRenderer_) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_NONE, imageIndex | IMGMOD_NONE, startIndex, endIndex, interval, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_FLIPPED, imageIndex | IMGMOD_FLIPPED, startIndex, endIndex, interval, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_BLUEFLAME, startIndex, endIndex, interval, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME, startIndex, endIndex, interval, loop, loopStartFrame)) {
    return false;
  }
}

bool AnimationHandler::CallCreateAnimation(
    unsigned long long animationTag,
    unsigned long long imageIndex,
    const std::vector<unsigned int>& indices,
    unsigned long long interval,
    bool loop,
    unsigned long long loopStartFrame) {
  if (nullptr == pOwnerRenderer_) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_NONE, imageIndex | IMGMOD_NONE, indices, interval, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_FLIPPED, imageIndex | IMGMOD_FLIPPED, indices, interval, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_BLUEFLAME, indices, interval, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME, indices, interval, loop, loopStartFrame)) {
    return false;
  }
}

bool AnimationHandler::CallCreateAnimation(
    unsigned long long animationTag,
    unsigned long long imageIndex,
    const std::vector<unsigned int>& indices,
    const std::vector<unsigned long long> intervals,
    bool loop,
    unsigned long long loopStartFrame) {
  if (nullptr == pOwnerRenderer_) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_NONE, imageIndex | IMGMOD_NONE, indices, intervals, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_FLIPPED, imageIndex | IMGMOD_FLIPPED, indices, intervals, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_BLUEFLAME, indices, intervals, loop, loopStartFrame)) {
    return false;
  }
  if (false == pOwnerRenderer_->CreateAnimation(animationTag | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME, indices, intervals, loop, loopStartFrame)) {
    return false;
  }
}

unsigned long long AnimationHandler::CurrentAnimationState() const {
  return curAnimationState_;
}

void AnimationHandler::SetCurrentAnimationState(unsigned long long animationState) {
  curAnimationState_ = animationState;
}

unsigned long long AnimationHandler::CurrentAnimationModifier() const {
  return curAnimationModifier_;
}

void AnimationHandler::SetCurrentAnimationModifier(unsigned long long animationModifier) {
  curAnimationModifier_ = animationModifier;
}

void AnimationHandler::UpdatePrevImageIndex() {
  if (nullptr == pOwnerRenderer_) {
    return;
  }

  unsigned int curImageIndex = pOwnerRenderer_->GetImageIndex();
  if (curImageIndex != prevImageIndex_) {
    prevImageIndex_ = curImageIndex;
  }
}

unsigned int AnimationHandler::CurrentImageIndex() const {
  return pOwnerRenderer_->GetImageIndex();
}

unsigned int AnimationHandler::PrevImageIndex() const {
  return prevImageIndex_;
}
