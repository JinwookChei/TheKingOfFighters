#include "stdafx.h"
#include "Effect.h"
#include "CollisionComponent.h"
#include "ImageRenderer.h"

Effect::Effect()
    : pRender_(nullptr),
      pCollision_(nullptr),
      velocity_({0.0f, 0.0f}),
      reach_({0.0f, 0.0f})
{
}

Effect::~Effect() {
}

void Effect::BeginPlay() {
  pRender_ = CreateImageRender();
  pRender_->CreateAnimation();

  pCollision_ = CreateCollision(CollisionGroupEngineType_None);
}

void Effect::Tick(unsigned long long curTick) {
}

Vector Effect::GetVelocity() const {
  return velocity_;
}

void Effect::SetVelocity(Vector velocity) {
  velocity_ = velocity;
}