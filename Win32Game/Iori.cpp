#include "stdafx.h"
#include "Iori.h"

Iori::Iori()
    : pRender_(nullptr),
      pBattle_(nullptr) {
}

Iori::~Iori() {
}

void Iori::BeginPlay() {
  pRender_ = CreateImageRender();

  pRender_->CreateAnimation(1, 3, 7, 15, 50, true);     // 아이들
  pRender_->CreateAnimation(2, 3, 16, 23, 50, false);   // 앉기.
  pRender_->CreateAnimation(3, 3, 26, 35, 50, true);    // -> 걷기
  pRender_->CreateAnimation(4, 3, 36, 44, 50, true);    // <- 뒤로가기
  pRender_->CreateAnimation(5, 3, 109, 118, 50, true);  // 발차기

  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->SetTransparentColor(Color8Bit{169, 139, 150, 0});

  pRender_->ChangeAnimation(1);
  pRender_->SetLocalScale({3.0f, 3.0f});

  // pBattle_ = CreateComponent<BattleComponent>();
}

void Iori::Tick(unsigned long long deltaTick) {
  if (false == InputManager::Instance()->IsAnyKeyPress()) {
    pRender_->ChangeAnimation(1);
    return;
  }

  Vector moveDir = {0.0f, 0.0f};

  if (InputManager::Instance()->IsPress('A') || InputManager::Instance()->IsPress('a')) {
    pRender_->ChangeAnimation(4);
    moveDir += Vector::Left;
  }
  if (InputManager::Instance()->IsPress('D') || InputManager::Instance()->IsPress('d')) {
    pRender_->ChangeAnimation(3);
    moveDir += Vector::Right;
  }
  if (InputManager::Instance()->IsPress('W') || InputManager::Instance()->IsPress('w')) {
    moveDir += Vector::Up;
  }
  if (InputManager::Instance()->IsPress('S') || InputManager::Instance()->IsPress('s')) {
    pRender_->ChangeAnimation(2);
  }
  if (InputManager::Instance()->IsPress('F') || InputManager::Instance()->IsPress('f')) {
    pRender_->ChangeAnimation(5);
  }

  if (InputManager::Instance()->IsPress('Q') || InputManager::Instance()->IsPress('q')) {
    // pRender_->SetFlipRendering(true);
  }
  if (InputManager::Instance()->IsPress('E') || InputManager::Instance()->IsPress('e')) {
    // pRender_->SetFlipRendering(false);
  }

  if (moveDir == Vector(0.0f, 0.0f)) {
    // pRender_->ChangeAnimation(1);
  }

  Vector newPosition = moveDir + GetPosition();
  SetPosition(newPosition);




  //
  // if (false == InputManager::Instance()->IsAnyKeyPress()) {
  //   pRender_->ChangeAnimation(1);
  //   return;
  // }

  // Vector moveDir = {0.0f, 0.0f};

  // if (InputManager::Instance()->IsPress('A') || InputManager::Instance()->IsPress('a')) {
  //   if (false == pRender_->GetFlipRendering()) {
  //     pRender_->ChangeAnimation(4);

  //  } else {
  //    pRender_->ChangeAnimation(3);
  //  }

  //  moveDir += Vector::Left;
  //}
  // if (InputManager::Instance()->IsPress('D') || InputManager::Instance()->IsPress('d')) {
  //  if (false == pRender_->GetFlipRendering()) {
  //    pRender_->ChangeAnimation(3);
  //  } else {
  //    pRender_->ChangeAnimation(4);
  //  }

  //  moveDir += Vector::Right;
  //}
  // if (InputManager::Instance()->IsPress('W') || InputManager::Instance()->IsPress('w')) {
  //  moveDir += Vector::Up;
  //}
  // if (InputManager::Instance()->IsPress('S') || InputManager::Instance()->IsPress('s')) {
  //  pRender_->ChangeAnimation(2);
  //}
  // if (InputManager::Instance()->IsPress('F') || InputManager::Instance()->IsPress('f')) {
  //  pRender_->ChangeAnimation(5);
  //}

  // if (InputManager::Instance()->IsPress('Q') || InputManager::Instance()->IsPress('q')) {
  //   pRender_->SetFlipRendering(true);
  // }
  // if (InputManager::Instance()->IsPress('E') || InputManager::Instance()->IsPress('e')) {
  //   pRender_->SetFlipRendering(false);
  // }

  // if (moveDir == Vector(0.0f, 0.0f)) {
  //   // pRender_->ChangeAnimation(1);
  // }

  // Vector newPosition = moveDir + GetPosition();
  // SetPosition(newPosition);
}