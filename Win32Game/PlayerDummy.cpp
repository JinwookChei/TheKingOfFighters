#include "stdafx.h"
#include "PlayerDummy.h"
//#include "BattleComponent.h"
//
//Player::Player()
//    : pRender_(nullptr),
//      pCollision_(nullptr),
//      prevTargetCollision_(nullptr),
//      pBattle_(nullptr) {
//}
//
//Player::~Player() {
//}
//
//void Player::BeginPlay() {
//  SetActorGroup(ActorGroupEngineType::ActorGroupEngineType_None);
//
//  SetDebugParameter({.on_ = true, .linethickness_ = 1.0f, .color_ = Color8Bit::Red});
//
//  pRender_ = CreateImageRender();
//
//  pCollision_ = CreateCollision(CollisionGroupType::CollisionGroupType_Player);
//  pCollision_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .withCircle_ = false, .linethickness_ = 1.0f, .color_ = Color8Bit::Blue});
//  pCollision_->SetScale({100.0f, 100.0f});
//  pCollision_->SetPosition({100.0f, 0.0f});
//
//  IImage* pFind = ImgManager::GetIntance()->GetImg(0);
//
//  pRender_->CreateAnimation(1, 0, 0, (unsigned int)(pFind->GetImageCount() - 1), 100, true);  // 아이들
//  // pRender_->CreateAnimation(1, 1, 0, 12, 80, true);  // 아이들
//  //  pRender_->CreateAnimation(1, 1, 13, 16, 80, true);  // 아이들
//  // pRender_->CreateAnimation(1, 1, 0, 16, 80, true);  // 아이들
//  // pRender_->CreateAnimation(1, 1, 0, 12, 80, true);  // 아이들
//  //  pRender_->CreateAnimation(1, 1, 9, 16, 80, true);  // 아이들
//  //   pRender_->CreateAnimation(2, 3, {15, 16, 17}, 100, true);  // 걷기
//
//  // pRender_->SetImage(ImgManager::GetIntance()->GetImg(0));
//  // pRender_->SetAlpha(1.0f);
//  pRender_->SetTransparentColor(Color8Bit(86, 177, 222, 0));
//
//  // pRender_->SetImageRenderType(ImageRenderType::LeftTop);
//  pRender_->SetImageRenderType(ImageRenderType::Center);
//
//  pRender_->ChangeAnimation(1);
//
//  pRender_->SetLocalScale({1.0f, 1.0f});
//  pRender_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 1.0f, .color_ = Color8Bit::Green});
//
//  pBattle_ = CreateComponent<BattleComponent>();
//}
//
//void Player::Tick(unsigned long long deltaTick) {
//  /*if (false == InputManager::Instance()->IsAnyKeyPress()) {
//    pRender_->ChangeAnimation(1);
//    return;
//  }*/
//
//  Vector moveDir = {0.0f, 0.0f};
//
//  if (InputManager::Instance()->IsPress('A') || InputManager::Instance()->IsPress('a')) {
//    // pRender_->ChangeAnimation(2);
//    moveDir += Vector::Left;
//  }
//  if (InputManager::Instance()->IsPress('D') || InputManager::Instance()->IsPress('d')) {
//    moveDir += Vector::Right;
//  }
//  if (InputManager::Instance()->IsPress('W') || InputManager::Instance()->IsPress('w')) {
//    moveDir += Vector::Up;
//  }
//  if (InputManager::Instance()->IsPress('S') || InputManager::Instance()->IsPress('s')) {
//    moveDir += Vector::Down;
//  }
//  if (InputManager::Instance()->IsPress('F') || InputManager::Instance()->IsPress('f')) {
//    pRender_->SetAngle(pRender_->GetAngle() + 0.1f);
//  }
//
//  if (moveDir == Vector(0.0f, 0.0f)) {
//    pRender_->ChangeAnimation(1);
//  }
//
//  Vector newPosition = moveDir + GetPosition();
//  SetPosition(newPosition);
//
//  CollisionComponent* targetCollision = nullptr;
//  if (pCollision_->Collision(CollisionCheckParameter{.targetGroup = CollisionGroupType::CollisionGroupType_Monster, .targetCollisionType = CollisionType::CollisionType_Rect, .myCollisionType = CollisionType::CollisionType_Circle}, &targetCollision)) {
//    ActorComponentSetDebugParameter debugparameter = pCollision_->GetDebugParameter();
//    debugparameter.color_ = Color8Bit::Red;
//    pCollision_->SetDebugParameter(debugparameter);
//
//    if (nullptr != targetCollision) {
//      debugparameter = targetCollision->GetDebugParameter();
//      debugparameter.color_ = Color8Bit::Cyan;
//      targetCollision->SetDebugParameter(debugparameter);
//      prevTargetCollision_ = targetCollision;
//    }
//
//  } else {
//    ActorComponentSetDebugParameter debugparameter = pCollision_->GetDebugParameter();
//    debugparameter.color_ = Color8Bit::Blue;
//    pCollision_->SetDebugParameter(debugparameter);
//
//    if (nullptr != prevTargetCollision_) {
//      debugparameter = prevTargetCollision_->GetDebugParameter();
//      debugparameter.color_ = Color8Bit::Black;
//      prevTargetCollision_->SetDebugParameter(debugparameter);
//      prevTargetCollision_ = nullptr;
//    }
//  }
//}