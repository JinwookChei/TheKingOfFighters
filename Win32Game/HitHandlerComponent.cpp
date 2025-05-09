#include "stdafx.h"
#include "HitHandlerComponent.h"
#include "HealthComponent.h"
#include "MovementComponent.h"

HitHandlerComponent::HitHandlerComponent()
    : pOwnerHealthComponent_(nullptr),
      pOwnerMovementComponent_(nullptr) {
}

HitHandlerComponent::~HitHandlerComponent() {
}

void HitHandlerComponent::BeginPlay() {
}

void HitHandlerComponent::Tick(unsigned long long curTick) {
}

bool HitHandlerComponent::Initialize(HealthComponent* ownerHealthComponent, MovementComponent* pOwnerMovementComponent) {
  if (nullptr == ownerHealthComponent) {
    return false;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return false;
  }

  if (owner != ownerHealthComponent->GetOwner()) {
    return false;
  }


  if (owner != pOwnerMovementComponent->GetOwner()) {
    return false;
  }
  
  pOwnerHealthComponent_ = ownerHealthComponent;
  pOwnerMovementComponent_ = pOwnerMovementComponent;

  return true;
}


//void HitHandlerComponent::BroadcastHitPacket(const HitPacket& hitPacket) {
//  pOwnerHealthComponent_->TakeDamage(hitPacket.damage_);
//  pOwnerMovementComponent_->SetKnockBackForce(hitPacket.knockBackForce_);
//}
