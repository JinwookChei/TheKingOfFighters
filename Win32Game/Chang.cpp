#include "stdafx.h"
#include "Chang.h"

Chang::Chang()
    : pRender_(nullptr),
      pBattle_(nullptr) {
}

Chang::~Chang() {
}

void Chang::BeginPlay() {
  pRender_ = CreateImageRender();

  pRender_->CreateAnimation(1, 4, 8, 13, 50, true);  // ¾ÆÀÌµé
  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->SetTransparentColor(Color8Bit{17, 91, 124, 0});

  pRender_->ChangeAnimation(1);
  pRender_->SetLocalScale({3.0f, 3.0f});
}

void Chang::Tick(unsigned long long deltaTick) {
  if (false == InputManager::Instance()->IsAnyKeyPress()) {
    pRender_->ChangeAnimation(1);
    return;
  }

  Vector moveDir = {0.0f, 0.0f};

  if (InputManager::Instance()->IsPress('J') || InputManager::Instance()->IsPress('j')) {
    pRender_->ChangeAnimation(3);
    moveDir += Vector::Left;
  }
  if (InputManager::Instance()->IsPress('L') || InputManager::Instance()->IsPress('l')) {
    pRender_->ChangeAnimation(4);
    moveDir += Vector::Right;
  }
  if (InputManager::Instance()->IsPress('I') || InputManager::Instance()->IsPress('i')) {
    moveDir += Vector::Up;
  }
  if (InputManager::Instance()->IsPress('K') || InputManager::Instance()->IsPress('k')) {
    pRender_->ChangeAnimation(2);
  }
  /*if (InputManager::Instance()->IsPress('F') || InputManager::Instance()->IsPress('f')) {
    pRender_->ChangeAnimation(5);
  }*/

  if (InputManager::Instance()->IsPress('U') || InputManager::Instance()->IsPress('u')) {
    // pRender_->SetFlipRendering(true);
  }
  if (InputManager::Instance()->IsPress('O') || InputManager::Instance()->IsPress('o')) {
    // pRender_->SetFlipRendering(false);
  }

  if (moveDir == Vector(0.0f, 0.0f)) {
    // pRender_->ChangeAnimation(1);
  }

  Vector newPosition = moveDir + GetPosition();
  SetPosition(newPosition);
}