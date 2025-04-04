#include "stdafx.h"
#include "Iori.h"
#include "CollisionBox.h"
#include "Chang.h"

Iori::Iori()
    : pRender_(nullptr),
      pHitBoxTop_(nullptr),
      pHitBoxBottom_(nullptr),
      pAttackBox_(nullptr),
      pPushBox_(nullptr),
      pGrabBox_(nullptr),
      pCommendComponent_(nullptr),
      pBattle_(nullptr) {
}

Iori::~Iori() {
}

void Iori::BeginPlay() {
  // RENDERER
  pRender_ = CreateImageRender();
  pRender_->CreateAnimation(IoriAnim::IORIANIM_IDle, 3, 6, 14, 50, true);          // 아이들
  pRender_->CreateAnimation(IoriAnim::IORIANIM_Seat, 3, 15, 22, 50, true);        // 앉기.
  pRender_->CreateAnimation(IoriAnim::IORIANIM_Walk, 3, 27, 34, 50, true);         // -> 걷기
  pRender_->CreateAnimation(IoriAnim::IORIANIM_BackWalk, 3, 35, 43, 50, true);     // <- 뒤로가기
  pRender_->CreateAnimation(IoriAnim::IORIANIM_Kick, 3, 108, 117, 50, false);       // 발차기
  pRender_->CreateAnimation(IoriAnim::IORIANIM_SUperKick, 3, 136, 146, 50, false);  // 커맨드 테스트.

  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->SetTransparentColor(Color8Bit{169, 139, 150, 0});

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
  if (false == pCommendComponent_->RegistTask({CK_Left, CK_Down, CK_Right}, IoriAnim::IORIANIM_SUperKick)) {
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

void Iori::Tick(unsigned long long deltaTick) {
  RenderUpdate();

  CommendUpdate();

  CollisionUpdate();

  CollisionComponent* pTargetCollision = nullptr;
  CollisionCheckParameter;

  if (false == pAttackBox_->Collision(
      {
          .targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop,
          .targetCollisionType = CollisionType::CollisionType_Rect,
          .myCollisionType = CollisionType::CollisionType_Rect,
      },
      &pTargetCollision))
  {
    return;
  }

  
  //Actor* targetActor = pTargetCollision->GetOwner();
  //targetActor

}

void Iori::RenderUpdate() {
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
}

void Iori::CommendUpdate() {
  if (InputManager::Instance()->IsDown('A') || InputManager::Instance()->IsDown('a')) {
    pCommendComponent_->JumpNode(CK_Left);
  }

  if (InputManager::Instance()->IsDown('D') || InputManager::Instance()->IsDown('d')) {
    pCommendComponent_->JumpNode(CK_Right);
  }

  if (InputManager::Instance()->IsDown('W') || InputManager::Instance()->IsDown('w')) {
    pCommendComponent_->JumpNode(CK_Up);
  }

  if (InputManager::Instance()->IsDown('S') || InputManager::Instance()->IsDown('s')) {
    pCommendComponent_->JumpNode(CK_Down);
  }

  switch (pCommendComponent_->GetTask()) {
    case IORIANIM_None:
      break;

    case IORIANIM_IDle:
      break;

    case IORIANIM_Seat:
      break;

    case IORIANIM_Walk:
      break;

    case IORIANIM_BackWalk:
      break;

    case IORIANIM_Kick:
      break;

    case IORIANIM_SUperKick:
      pRender_->ChangeAnimation(IORIANIM_SUperKick);
      pCommendComponent_->ResetNode();
      //MessageBox(NULL, L"SuperKick!!", L"알림", MB_OK);
      break;
    default:
      break;
  }
}

void Iori::CollisionUpdate() {
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



// Regacy

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