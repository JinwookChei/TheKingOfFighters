#include "stdafx.h"
#include "Iori.h"
#include "CollisionBox.h"

Iori::Iori()
    : pRender_(nullptr),
      pBattle_(nullptr),
      hitBoxTop_(nullptr),
      hitBoxBottom_(nullptr),
      attackBox_(nullptr),
      pushBox_(nullptr),
      grabBox_(nullptr) {
}

Iori::~Iori() {
}

void Iori::BeginPlay() {
  // RENDERER
  pRender_ = CreateImageRender();

  pRender_->CreateAnimation(1, 3, 7, 15, 50, true);     // 아이들
  pRender_->CreateAnimation(2, 3, 16, 23, 50, false);   // 앉기.
  pRender_->CreateAnimation(3, 3, 26, 35, 50, true);    // -> 걷기
  pRender_->CreateAnimation(4, 3, 36, 44, 50, true);    // <- 뒤로가기
  pRender_->CreateAnimation(5, 3, 109, 118, 50, true);  // 발차기

  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->SetTransparentColor(Color8Bit{169, 139, 150, 0});

  pRender_->ChangeAnimation(1);
  pRender_->SetLocalScale({4.0f, 4.0f});

  // COLLISION
  hitBoxTop_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop);
  hitBoxBottom_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxBottom);
  attackBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_AttackBox);
  pushBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_PushBox);
  grabBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_GrabBox);

  CollisionUpdate();

  SetDebugParameter({.on_ = true, .linethickness_ = 2.0f});

  pRender_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Cyan});
  hitBoxTop_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  hitBoxBottom_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  attackBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Red});
  pushBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::White});
  grabBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Yellow});
}

void Iori::Tick(unsigned long long deltaTick) {
  do {
    if (false == InputManager::Instance()->IsAnyKeyPress()) {
      pRender_->ChangeAnimation(1);
      break;
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

  } while (false);

  CollisionUpdate();
}
//{
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
//}

void Iori::CollisionUpdate() {
  if (nullptr == hitBoxTop_ || nullptr == hitBoxBottom_ || nullptr == attackBox_ || nullptr == pushBox_ || nullptr == grabBox_) {
    return;
  }

  unsigned int imageIndex = pRender_->GetImageIndex();
  IImage* pImage = pRender_->GetImage();
  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  CollisionInfo* pCollisionInfo;

  Vector actorPosition = GetPosition();
  Vector imagePosition = pFileImage->RenderTransform(imageIndex).GetPosition();
  Vector imageScale = pFileImage->GetScale(imageIndex);
  
  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_HitBoxTop, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      hitBoxTop_->OnActive(true);
      //Vector newPosition = {0.0f, 0.0f};
      // hitBoxTop_->SetPosition(newPosition);
      hitBoxTop_->SetPosition(pCollisionInfo->position_);
      hitBoxTop_->SetScale(pCollisionInfo->scale_);
    } else {
      hitBoxTop_->OnActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_HitBoxBottom, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      hitBoxBottom_->OnActive(true);
      hitBoxBottom_->SetPosition(pCollisionInfo->position_);
      hitBoxBottom_->SetScale(pCollisionInfo->scale_);
    } else {
      hitBoxBottom_->OnActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_AttackBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      attackBox_->OnActive(true);
      attackBox_->SetPosition(pCollisionInfo->position_);
      attackBox_->SetScale(pCollisionInfo->scale_);
    } else {
      attackBox_->OnActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_PushBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pushBox_->OnActive(true);
      pushBox_->SetPosition(pCollisionInfo->position_);
      pushBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pushBox_->OnActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_GrabBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      grabBox_->OnActive(true);
      grabBox_->SetPosition(pCollisionInfo->position_);
      grabBox_->SetScale(pCollisionInfo->scale_);
    } else {
      grabBox_->OnActive(false);
    }
  }
}
