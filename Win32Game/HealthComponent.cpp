#include "stdafx.h"
#include "HealthComponent.h"

HealthComponent::HealthComponent()
    : maxHealth_(0.0f),
      health_(0.0f) {
}

HealthComponent::~HealthComponent() {
}

void HealthComponent::BeginPlay() {
}

bool HealthComponent::Initialize(float maxHealth) {
  if (maxHealth < 0.0f) {
    return false;
  }

  maxHealth_ = maxHealth;
  health_ = maxHealth_;
  return true;
}

void HealthComponent::Tick(unsigned long long curTick) {
}

void HealthComponent::SetHealth(float health) {
  health_ = health;
}

float HealthComponent::Health() const {
  return health_;
}

float HealthComponent::MaxHealth() const {
  return maxHealth_;
}

void HealthComponent::Heel(float heel) {
  if (heel < 0.0f) {
    return;
  }

  health_ += heel;
  if (health_ > maxHealth_) {
    health_ = maxHealth_;
  }
}

void HealthComponent::TakeDamage(float damage) {
  if (damage < 0.0f) {
    return;
  }

  health_ -= damage;
}
