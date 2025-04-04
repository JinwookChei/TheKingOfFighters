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
      animState_(CHAS_None),
      // pStateComponent_(nullptr),
      pBattle_(nullptr) {
}

Chang::~Chang() {
}

void Chang::BeginPlay() {
  pRender_ = CreateImageRender();

  pRender_->CreateAnimation(CHAS_Idel, 4, 8, 13, 50, true);   // ¾ÆÀÌµé
  pRender_->CreateAnimation(CHAS_Hit, 4, 33, 35, 50, false);  // HIT
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
  //if (false == pCommendComponent_->RegistTask({CK_Left, CK_Down, CK_Right}, 2)) {
  //  return;
  //}

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

  if (true == CollisionHitUpdate()) {
    pRender_->ChangeAnimation(animState_);
  }

  do {
    if (false == pRender_->IsPlayingLoopAnimation()) {
      break;
    }

    InputUpdate();

    CommendUpdate();

    pRender_->ChangeAnimation(animState_);
  } while (false);

  CollisionBoundUpdate();
}

void Chang::InputUpdate() {
  if (false == InputManager::Instance()->IsPress('J') && false == InputManager::Instance()->IsPress('j')
      && false == InputManager::Instance()->IsPress('L') && false == InputManager::Instance()->IsPress('l')
      && false == InputManager::Instance()->IsPress('I') && false == InputManager::Instance()->IsPress('i')
      && false == InputManager::Instance()->IsPress('K') && false == InputManager::Instance()->IsPress('k') ){
    animState_ = CHAS_Idel;
    return;
  }

  Vector moveDir = {0.0f, 0.0f};

  if (InputManager::Instance()->IsPress('J') || InputManager::Instance()->IsPress('j')) {
    //animState_ = CHAS_Idel;
    moveDir += Vector::Left;
  }
  if (InputManager::Instance()->IsPress('L') || InputManager::Instance()->IsPress('l')) {
    //animState_ = CHAS_Idel;
    moveDir += Vector::Right;
  }
  if (InputManager::Instance()->IsPress('I') || InputManager::Instance()->IsPress('i')) {
    moveDir += Vector::Up;
  }
  if (InputManager::Instance()->IsPress('K') || InputManager::Instance()->IsPress('k')) {
  }
  if (InputManager::Instance()->IsPress('F') || InputManager::Instance()->IsPress('f')) {
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

void Chang::CollisionBoundUpdate() {
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
      pHitBoxTop_->SetActive(true);
      pHitBoxTop_->SetPosition(pCollisionInfo->position_);
      pHitBoxTop_->SetScale(pCollisionInfo->scale_);
    } else {
      pHitBoxTop_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_HitBoxBottom, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pHitBoxBottom_->SetActive(true);
      pHitBoxBottom_->SetPosition(pCollisionInfo->position_);
      pHitBoxBottom_->SetScale(pCollisionInfo->scale_);
    } else {
      pHitBoxBottom_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_AttackBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pAttackBox_->SetActive(true);
      pAttackBox_->SetPosition(pCollisionInfo->position_);
      pAttackBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pAttackBox_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_PushBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pPushBox_->SetActive(true);
      pPushBox_->SetPosition(pCollisionInfo->position_);
      pPushBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pPushBox_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_GrabBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pGrabBox_->SetActive(true);
      pGrabBox_->SetPosition(pCollisionInfo->position_);
      pGrabBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pGrabBox_->SetActive(false);
    }
  }
}

bool Chang::CollisionHitUpdate() {
  if (pHitBoxTop_->IsHit()) {
    animState_ = CHAS_Hit;
    pHitBoxTop_->OffHit();
    return true;
  }

  if (pHitBoxBottom_->IsHit()) {
    animState_ = CHAS_Hit;
    pHitBoxTop_->OffHit();
    return true;
  }

  return false;
}
