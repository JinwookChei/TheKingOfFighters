#include "stdafx.h"
#include "ViewPortImage.h"
#include "CollisionBound.h"
#include "CollisionBoundCorner.h"

CollisionBoundCorner::CollisionBoundCorner()
    : bindViewPortImage_(nullptr),
      boundType_(CollisionBoundType::CBT_HitBoxTop),
      cornerType_(CollisionBoundCornerType::CBCT_Start),
      color_(Color8Bit::BlackAlpha),
      prevMousePosition_({0.0f, 0.0f}) {
}

CollisionBoundCorner::~CollisionBoundCorner() {
}

void CollisionBoundCorner::BeginPlay() {
  SetScale({15.0f, 15.0f});
}

void CollisionBoundCorner::Tick(unsigned long long curTick) {
  MoveWithDrag();
}

void CollisionBoundCorner::ClickDownEvent() {
}

void CollisionBoundCorner::Initialize(ViewPortImage* viewPortImage, CollisionBoundType boundType, CollisionBoundCornerType cornerType, const Color8Bit& color) {
  bindViewPortImage_ = viewPortImage;
  boundType_ = boundType;
  cornerType_ = cornerType;
  color_ = color;
}

void CollisionBoundCorner::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture) {
    return;
  }

  if (nullptr == bindViewPortImage_) {
    return;
  }

  // 이미지의 Collisioninfo.hasCollision이 False면 Render 안함.
  unsigned int imageIndex = bindViewPortImage_->GetImageIndex();
  IImage* pImage = bindViewPortImage_->GetImage();

  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }
  IFileImage* pFileImage = (IFileImage*)pImage;
  CollisionInfo* pCollisionInfo;

  if (false == pFileImage->GetCollisionBoxInfo(imageIndex, boundType_, &pCollisionInfo) || false == pCollisionInfo->hasCollision_)
  {
    return;
  }
  // 이미지의 Collisioninfo.hasCollision이 False면 Render 안함.


  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Transform& transform = GetTransform();

  renderTexture->DrawCircle(transform.GetScale(), color_, 2.0f);
  renderTexture->SetAlpha(1.0f, transform, true, owner->GetCurrentColor());
}

void CollisionBoundCorner::MoveWithDrag() {
  if (cornerType_ == CollisionBoundCornerType::CBCT_Start) {
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
      CollisionInfo* pCollisionInfo;
      if (false == pFileImage->GetCollisionBoxInfo(imageIndex, boundType_, &pCollisionInfo) || false == pCollisionInfo->hasCollision_) {
        return;
      }

      pCollisionInfo->position_ += deltaPosition;
      pCollisionInfo->scale_ -= deltaPosition;
    }

    CollisionInfo* pCollisionInfo;
    if (false == pFileImage->GetCollisionBoxInfo(imageIndex, boundType_, &pCollisionInfo)) {
      return;
    }

    SetPosition(pCollisionInfo->position_);

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
      CollisionInfo* pCollisionInfo;
      if (false == pFileImage->GetCollisionBoxInfo(imageIndex, boundType_, &pCollisionInfo)) {
        return;
      }

      pCollisionInfo->scale_ += deltaPosition;
    }

    CollisionInfo* pCollisionInfo;
    if (false == pFileImage->GetCollisionBoxInfo(imageIndex, boundType_, &pCollisionInfo) || false == pCollisionInfo->hasCollision_) {
      return;
    }

    SetPosition(pCollisionInfo->position_ + pCollisionInfo->scale_);

    prevMousePosition_ = curMousePosition;
  }
}

