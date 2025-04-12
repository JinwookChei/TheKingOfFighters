#include "stdafx.h"
#include "CommandComponent.h"
#include "ProjectileComponent.h"
#include "MovementComponent.h"
#include "CollisionBox.h"
#include "Player.h"

Player::Player()
    : pRender_(nullptr),
      pMovementComponent_(nullptr),
      pHitBoxTop_(nullptr),
      pHitBoxBottom_(nullptr),
      pAttackBox_(nullptr),
      pPushBox_(nullptr),
      pGrabBox_(nullptr),
      pCommandComponent_(nullptr),
      pProjectileComponent_(nullptr),
      animState_(0),
      characterScale_({0.0f, 0.0f}),
      isFlip_(1){
}

Player::~Player() {
}

void Player::BeginPlay() {
}

void Player::Tick(unsigned long long curTick) {
}

void Player::Initialize(const Vector& position, bool useCameraPosition, bool flip) {
  SetPosition(position);
  SetUseCameraposition(useCameraPosition);
  if (true == flip) {
    Flip();
  }

  // RENDERER
  pRender_ = CreateImageRender();
  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->SetLocalScale({4.5f, 4.5f});


  // MOVEMENT
  pMovementComponent_ = CreateComponent<MovementComponent>();
  pMovementComponent_->Initialize(position);

  // COLLISION
  pHitBoxTop_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop);
  pHitBoxBottom_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxBottom);
  pAttackBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_AttackBox);
  pPushBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_PushBox);
  pGrabBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_GrabBox);

  // COMMEND
  pCommandComponent_ = CreateComponent<CommandComponent>();
  pCommandComponent_->SetTimeOutThreshold(80);

  // PROJECTILE
  pProjectileComponent_ = CreateComponent<ProjectileComponent>();
  if (false == pProjectileComponent_->Initialize(GetLevel())) {
    return;
  }

  // DBUG SETTING
  SetDebugParameter({.on_ = true, .linethickness_ = 2.0f});
  pRender_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Cyan});
  pHitBoxTop_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  pHitBoxBottom_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  pAttackBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Red});
  pPushBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::White});
  pGrabBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Yellow});
}

void Player::InputUpdate() {
}

void Player::CommendUpdate() {
}

void Player::CollisionBoundUpdate() {
}

bool Player::CollisionHitUpdate() {
  return false;
}

Vector Player::CharacterScale() const {
  return characterScale_;
}

void Player::SetCharacterScale(const Vector& scale) {
  characterScale_ = scale;
}

void Player::Flip() {
}