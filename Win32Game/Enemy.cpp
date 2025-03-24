#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
}

void Enemy::BeginPlay() {
  CollisionComponent* newComponent = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_None);
  newComponent->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 1.0f});
  newComponent->SetScale({100.0f, 100.0f});
}

void Enemy::Tick(unsigned long long curTick) {
}
