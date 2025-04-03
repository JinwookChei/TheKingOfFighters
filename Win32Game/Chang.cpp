#include "stdafx.h"
#include "Chang.h"
#include "CollisionBox.h"

Chang::Chang()
    : pRender_(nullptr),
      pHitBoxTop_(nullptr),
      pHitBoxBottom_(nullptr),
      pAttackBox_(nullptr),
      pPushBox_(nullptr),
      pGrabBox_(nullptr),
      pCommendComponent_(nullptr),
      pBattle_(nullptr) {
}

Chang::~Chang() {
}

void Chang::BeginPlay() {
  pRender_ = CreateImageRender();

  pRender_->CreateAnimation(1, 4, 8, 13, 50, true);   // 아이들
  pRender_->CreateAnimation(2, 4, 33, 35, 50, true);  // 뒷걸음질.
  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->SetTransparentColor(Color8Bit{17, 91, 124, 0});

  pRender_->ChangeAnimation(1);
  pRender_->SetLocalScale({4.0f, 4.0f});

  // COLLISION
  pHitBoxTop_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop);
  pHitBoxBottom_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxBottom);
  pAttackBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_AttackBox);
  pPushBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_PushBox);
  pGrabBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_GrabBox);

  // COMMEND
  pCommendComponent_ = CreateComponent<CommendComponent>();
  pCommendComponent_->SetTimeOutThreshold(80);
  if (false == pCommendComponent_->RegistTask({CK_Left, CK_Down, CK_Right}, 2)) {
    return;
  }

  CollisionUpdate();

  // DBUG SETTING
  SetDebugParameter({.on_ = true, .linethickness_ = 2.0f});
  pRender_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Cyan});
  pHitBoxTop_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  pHitBoxBottom_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  pAttackBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Red});
  pPushBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::White});
  pGrabBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Yellow});
}

void Chang::Tick(unsigned long long deltaTick) {
  RenderUpdate();

  CommendUpdate();

  CollisionUpdate();
}

void Chang::RenderUpdate() {
  if (false == InputManager::Instance()->IsAnyKeyPress()) {
    pRender_->ChangeAnimation(1);
    return;
  }

  Vector moveDir = {0.0f, 0.0f};

  if (InputManager::Instance()->IsPress('J') || InputManager::Instance()->IsPress('j')) {
    // pRender_->ChangeAnimation(3);
    moveDir += Vector::Left;
  }
  if (InputManager::Instance()->IsPress('L') || InputManager::Instance()->IsPress('l')) {
    // pRender_->ChangeAnimation(4);
    moveDir += Vector::Right;
  }
  if (InputManager::Instance()->IsPress('I') || InputManager::Instance()->IsPress('i')) {
    moveDir += Vector::Up;
  }
  if (InputManager::Instance()->IsPress('K') || InputManager::Instance()->IsPress('k')) {
    // pRender_->ChangeAnimation(2);
  }
  if (InputManager::Instance()->IsPress('F') || InputManager::Instance()->IsPress('f')) {
    // pRender_->ChangeAnimation(5);
  }

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

void Chang::CommendUpdate() {
}

void Chang::CollisionUpdate() {
  if (nullptr == pHitBoxTop_ || nullptr == pHitBoxBottom_ || nullptr == pAttackBox_ || nullptr == pPushBox_ || nullptr == pGrabBox_) {
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
      pHitBoxTop_->OnActive(true);
      pHitBoxTop_->SetPosition(pCollisionInfo->position_);
      pHitBoxTop_->SetScale(pCollisionInfo->scale_);
    } else {
      pHitBoxTop_->OnActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_HitBoxBottom, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pHitBoxBottom_->OnActive(true);
      pHitBoxBottom_->SetPosition(pCollisionInfo->position_);
      pHitBoxBottom_->SetScale(pCollisionInfo->scale_);
    } else {
      pHitBoxBottom_->OnActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_AttackBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pAttackBox_->OnActive(true);
      pAttackBox_->SetPosition(pCollisionInfo->position_);
      pAttackBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pAttackBox_->OnActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_PushBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pPushBox_->OnActive(true);
      pPushBox_->SetPosition(pCollisionInfo->position_);
      pPushBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pPushBox_->OnActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_GrabBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pGrabBox_->OnActive(true);
      pGrabBox_->SetPosition(pCollisionInfo->position_);
      pGrabBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pGrabBox_->OnActive(false);
    }
  }
}
