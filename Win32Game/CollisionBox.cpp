#include "stdafx.h"
#include "ToolActor.h"
#include "CollisionBox.h"
#include "CollisionBoxCorner.h"


CollisionBox::CollisionBox()
    : bindToolActor_(nullptr),
      bindCornerStart_(nullptr),
      bindCornerEnd_(nullptr),
      collisionBoxType_(CollisionBoxType::CBT_HitBoxTop),
      color_(Color8Bit::BlackAlpha),
      prevMousePosition_({0.0f, 0.0f}) {
}

CollisionBox::~CollisionBox() {
}

void CollisionBox::BeginPlay() {
  EnableCollision(false);
}

void CollisionBox::Tick(unsigned long long curTick) {
  Transform startTransform = bindCornerStart_->GetTransform();
  Transform endTransform = bindCornerEnd_->GetTransform();

  Vector scale = endTransform.GetPosition() - startTransform.GetPosition();
  SetScale(scale);
  Vector position = {startTransform.GetPosition().X + scale.HalfX(), startTransform.GetPosition().Y + scale.HalfY()};
  SetPosition(position);
}

void CollisionBox::ClickDownEvent() {
}

void CollisionBox::ClickExit() {
}

void CollisionBox::Initialize(ToolActor* toolActor, ImageController* imageController, CollisionBoxType collisionBoxType) {
  
  UI* owner = GetOwner();

  if (nullptr == owner) {
    return;
  }

  if (nullptr == toolActor)
  {
    return;
  }

  if (nullptr == imageController)
  {
    return;
  }
  
  bindToolActor_ = toolActor;
  collisionBoxType_ = collisionBoxType;

  switch (collisionBoxType_) {
    case CBT_HitBoxTop:
      color_ = {0, 0, 255, 255};
      break;
    case CBT_HitBoxBottom:
      color_ = {150, 100, 255, 255};
      break;
    case CBT_AttackBox:
      color_ = {255, 0, 0, 255};
      break;
    case CBT_PushBox:
      color_ = {255, 255, 255, 255};
      break;
    case CBT_GrabBox:
      color_ = {255, 255, 0, 255};
      break;
    default:
      break;
  }

  bindCornerStart_ = owner->CreateUIComponent<CollisionBoxCorner>();
  bindCornerStart_->Initialize(bindToolActor_, imageController, collisionBoxType_, CollisionBoxCornerType::CBCT_Start, color_);

  bindCornerEnd_ = owner->CreateUIComponent<CollisionBoxCorner>();
  bindCornerEnd_->Initialize(bindToolActor_, imageController, collisionBoxType_, CollisionBoxCornerType::CBCT_End, color_);
}

CollisionBoxCorner* CollisionBox::GetCornerStart() {
  return bindCornerStart_;
}

CollisionBoxCorner* CollisionBox::GetCornerEnd() {
  return bindCornerEnd_;
}


void CollisionBox::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture) {
    return;
  }

  // 이미지의 Collisioninfo.hasCollision이 False면 Render 안함.
  if (nullptr == bindToolActor_) {
    return;
  }

  unsigned int imageIndex = bindToolActor_->GetImageIndex();
  IImage* pImage = bindToolActor_->GetImage();

  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }
  IFileImage* pFileImage = (IFileImage*)pImage;
  CollisionInfo* pCollisionInfo;

  if (false == pFileImage->GetCollisionBoxInfo(imageIndex, collisionBoxType_, &pCollisionInfo) || false == pCollisionInfo->hasCollision_) {
    return;
  }
  // --


  UI* owner = GetOwner();
  if (nullptr == owner)
  {
    return;
  }

  const Transform& transform = GetTransform();

  renderTexture->DrawRectagle(transform.GetScale(), color_, 2.0f);
  renderTexture->SetAlpha(1.0f, transform, true, owner->GetCurrentColor());
}