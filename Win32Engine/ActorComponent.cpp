#include "stdafx.h"
#include "ActorComponent.h"

ActorComponent::ActorComponent()
    : isActive_(false),
      enableTick_(true),
      owner_(nullptr),
      actorLink_({nullptr, nullptr, this}) {
}

ActorComponent::~ActorComponent() {
}

Actor* ActorComponent::GetOwner() const {
  return owner_;
}

void ActorComponent::BeginPlay() {
}

void ActorComponent::Tick(unsigned long long deltaTick) {
}

bool ActorComponent::IsActive() const {
  return isActive_;
}

void ActorComponent::SetActive(bool active) {
  isActive_ = active;
}

void ActorComponent::SetEnableTick(bool enable) {
  enableTick_ = enable;
}

bool ActorComponent::EnableTick() const {
  return enableTick_;
}

void ActorComponent::SetDebugParameter(const ActorComponentSetDebugParameter& parameter) {
  parameter_ = parameter;
  parameter_.color_.A = 255;
}

const ActorComponentSetDebugParameter& ActorComponent::GetDebugParameter() const {
  return parameter_;
}

void ActorComponent::DebugRender(IRenderTexture* renderTexture) {
}

void ActorComponent::CollisionRender(IRenderTexture* renderTexture) {
}

void ActorComponent::OnBeginPlay() {
  BeginPlay();
}

void ActorComponent::OnTick(unsigned long long curTick) {
  Tick(curTick);
}

void ActorComponent::SetOwner(Actor* owner) {
  owner_ = owner;
}

LINK_ITEM* ActorComponent::GetActorLink() {
  return &actorLink_;
}
