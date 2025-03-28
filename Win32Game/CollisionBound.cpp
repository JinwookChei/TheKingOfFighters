#include "stdafx.h"
#include "ViewPortImage.h"
#include "CollisionBound.h"
#include "CollisionBoundCorner.h"


CollisionBound::CollisionBound()
    : bindViewPortImage_(nullptr),
      bindCornerStart_(nullptr),
      bindCornerEnd_(nullptr),
      boundType_(CollisionBoundType::CBT_HitBoxTop),
      color_(Color8Bit::BlackAlpha),
      prevMousePosition_({0.0f, 0.0f}) {
}

CollisionBound::~CollisionBound() {
}

void CollisionBound::BeginPlay() {
  EnableCollision(false);
}

void CollisionBound::Tick(unsigned long long curTick) {
  Transform startTransform = bindCornerStart_->GetTransform();
  Transform endTransform = bindCornerEnd_->GetTransform();

  Vector scale = endTransform.GetPosition() - startTransform.GetPosition();
  SetScale(scale);
  Vector position = {startTransform.GetPosition().X + scale.HalfX(), startTransform.GetPosition().Y + scale.HalfY()};
  SetPosition(position);
}

void CollisionBound::ClickDownEvent() {
}

void CollisionBound::ClickExit() {
}

void CollisionBound::Initialize(ViewPortImage* viewPortImage, CollisionBoundType boundType) {
  
  UI* owner = GetOwner();

  if (nullptr == owner) {
    return;
  }

  bindViewPortImage_ = viewPortImage;
  if (nullptr == bindViewPortImage_)
  {
    return;
  }

  boundType_ = boundType;

  switch (boundType_) {
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
  

  bindCornerStart_ = owner->CreateUIComponent<CollisionBoundCorner>();
  bindCornerStart_->Initialize(bindViewPortImage_, boundType_, CollisionBoundCornerType::CBCT_Start, color_);

  bindCornerEnd_ = owner->CreateUIComponent<CollisionBoundCorner>();
  bindCornerEnd_->Initialize(bindViewPortImage_, boundType_, CollisionBoundCornerType::CBCT_End, color_);
}


void CollisionBound::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture) {
    return;
  }

  // 이미지의 Collisioninfo.hasCollision이 False면 Render 안함.
  if (nullptr == bindViewPortImage_) {
    return;
  }

  unsigned int imageIndex = bindViewPortImage_->GetImageIndex();
  IImage* pImage = bindViewPortImage_->GetImage();

  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }
  IFileImage* pFileImage = (IFileImage*)pImage;
  CollisionInfo* collisionInfo;

  if (false == pFileImage->GetCollisionBoxInfo(imageIndex, boundType_, &collisionInfo) || false == collisionInfo->hasCollision_) {
    return;
  }
  //이미지의 Collisioninfo.hasCollision이 False면 Render 안함.


  UI* owner = GetOwner();
  if (nullptr == owner)
  {
    return;
  }

  const Transform& transform = GetTransform();

  renderTexture->DrawRectagle(transform.GetScale(), color_, 2.0f);
  renderTexture->SetAlpha(1.0f, transform, true, owner->GetCurrentColor());
}