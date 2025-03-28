#include "stdafx.h"
#include "ViewPortImage.h"
#include "CollisionBoundCorner.h"

CollisionBoundCorner::CollisionBoundCorner()
    : bindViewPortImage_(nullptr),
      cornerType_(BoundCornerType::BCT_Start),
      color_(Color8Bit::BlackAlpha),
      prevMousePosition_({0.0f, 0.0f}) {
}

CollisionBoundCorner::~CollisionBoundCorner() {
}

void CollisionBoundCorner::BeginPlay() {
  SetScale({15.0f, 15.0f});
}

void CollisionBoundCorner::Tick(unsigned long long curTick) {
  // TODO : 코드 함축 해야함.
  if (cornerType_ == BoundCornerType::BCT_Start) {
    Vector curMousePosition = GEngineCore->GetMousePosition();

    if (nullptr == bindViewPortImage_) {
      return;
    }

    unsigned int imageIndex = bindViewPortImage_->GetImageIndex();
    IImage* pImage = bindViewPortImage_->GetImage();

    if (nullptr == pImage || true == pImage->IsRenderTexture()) {
      return;
    }
    IFileImage* pFileImage = (IFileImage*)pImage;

    if (IsMouseClick()) {
      Vector deltaPosition = curMousePosition - prevMousePosition_;
      CollisionInfo collisionInfo;
      if (false == pFileImage->GetHitBoxTopInfo(imageIndex, &collisionInfo)) {
        return;
      }

      collisionInfo.position_ += deltaPosition;
      collisionInfo.scale_ -= deltaPosition;
      pFileImage->SetHitBoxTopInfo(imageIndex, collisionInfo);
    }

    Vector imageOffSet = pFileImage->GetImagePositionOffSet(imageIndex);
    CollisionInfo collisionInfo;
    if (false == pFileImage->GetHitBoxTopInfo(imageIndex, &collisionInfo)) {
      return;
    }

    SetPosition(imageOffSet + collisionInfo.position_);

    prevMousePosition_ = curMousePosition;
  } else {
    Vector curMousePosition = GEngineCore->GetMousePosition();

    if (nullptr == bindViewPortImage_) {
      return;
    }

    unsigned int imageIndex = bindViewPortImage_->GetImageIndex();
    IImage* pImage = bindViewPortImage_->GetImage();

    if (nullptr == pImage || true == pImage->IsRenderTexture()) {
      return;
    }
    IFileImage* pFileImage = (IFileImage*)pImage;

    if (IsMouseClick()) {
      Vector deltaPosition = curMousePosition - prevMousePosition_;
      CollisionInfo collisionInfo;
      if (false == pFileImage->GetHitBoxTopInfo(imageIndex, &collisionInfo)) {
        return;
      }

      collisionInfo.scale_ += deltaPosition;
      pFileImage->SetHitBoxTopInfo(imageIndex, collisionInfo);
    }

    Vector imageOffSet = pFileImage->GetImagePositionOffSet(imageIndex);
    CollisionInfo collisionInfo;
    if (false == pFileImage->GetHitBoxTopInfo(imageIndex, &collisionInfo)) {
      return;
    }

    SetPosition(imageOffSet + collisionInfo.position_ + collisionInfo.scale_);

    prevMousePosition_ = curMousePosition;
  }
}

void CollisionBoundCorner::ClickDownEvent() {
}

void CollisionBoundCorner::Initialize(ViewPortImage* viewPortImage, BoundCornerType cornerType, const Color8Bit& color) {
  bindViewPortImage_ = viewPortImage;
  cornerType_ = cornerType;
  color_ = color;
}

void CollisionBoundCorner::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Transform& transform = GetTransform();
  renderTexture->DrawCircle(transform.GetScale(), color_, 2.0f);
  renderTexture->SetAlpha(1.0f, transform, true, owner->GetCurrentColor());
}
