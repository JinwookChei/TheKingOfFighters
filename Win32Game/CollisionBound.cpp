#include "stdafx.h"
#include "ViewPortImage.h"
#include "CollisionBoundCorner.h"
#include "CollisionBound.h"

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
      color_ = {173, 216, 230, 255};
      break;
    case CBT_attackBox:
      color_ = {255, 0, 0, 255};
      break;
    case CBT_pushBox:
      color_ = {255, 255, 255, 255};
      break;
    case CBT_grabBox:
      color_ = {255, 255, 0, 255};
      break;
    default:
      break;
  }
  

  bindCornerStart_ = owner->CreateUIComponent<CollisionBoundCorner>();
  bindCornerStart_->Initialize(bindViewPortImage_, BoundCornerType::BCT_Start, color_);

  bindCornerEnd_ = owner->CreateUIComponent<CollisionBoundCorner>();
  bindCornerEnd_->Initialize(bindViewPortImage_, BoundCornerType::BCT_End, color_);
}


void CollisionBound::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner)
  {
    return;
  }

  const Transform& transform = GetTransform();
  renderTexture->DrawRectagle(transform.GetScale(), color_, 1.0f);
  renderTexture->SetAlpha(1.0f, transform, true, owner->GetCurrentColor());
}