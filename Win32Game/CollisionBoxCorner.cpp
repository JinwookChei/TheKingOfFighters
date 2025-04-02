#include "stdafx.h"
#include "CollisionBox.h"
#include "ViewPortImage.h"
#include "CollisionBoxCorner.h"

CollisionBoxCorner::CollisionBoxCorner()
    : bindViewPortImage_(nullptr),
      collisionBoxType_(CollisionBoxType::CBT_HitBoxTop),
      cornerType_(CollisionBoxCornerType::CBCT_Start),
      color_(Color8Bit::BlackAlpha),
      prevMousePosition_({0.0f, 0.0f}) {
}

CollisionBoxCorner::~CollisionBoxCorner() {
}

void CollisionBoxCorner::BeginPlay() {
  SetScale({15.0f, 15.0f});
  EnableCollision(false);
}

void CollisionBoxCorner::Tick(unsigned long long curTick) {
  MoveWithDrag();
}

void CollisionBoxCorner::ClickDownEvent() {
}

void CollisionBoxCorner::Initialize(ViewPortImage* viewPortImage, CollisionBoxType boundType, CollisionBoxCornerType cornerType, const Color8Bit& color) {
  bindViewPortImage_ = viewPortImage;
  collisionBoxType_ = boundType;
  cornerType_ = cornerType;
  color_ = color;
}

void CollisionBoxCorner::Render(IRenderTexture* renderTexture) {
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

  if (false == pFileImage->GetCollisionBoxInfo(imageIndex, collisionBoxType_, &pCollisionInfo) || false == pCollisionInfo->hasCollision_) {
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

void CollisionBoxCorner::MoveWithDrag() {
  if (cornerType_ == CollisionBoxCornerType::CBCT_Start) {
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

    // if (IsMouseClick()) {
    //   Vector deltaPosition = curMousePosition - prevMousePosition_;
    //   CollisionInfo* pCollisionInfo;
    //   if (false == pFileImage->GetCollisionBoxInfo(imageIndex, collisionBoxType_, &pCollisionInfo) || false == pCollisionInfo->hasCollision_) {
    //     return;
    //   }

    //  pCollisionInfo->position_ += deltaPosition;
    //  pCollisionInfo->scale_ -= deltaPosition;
    //}

    CollisionInfo* pCollisionInfo;
    if (false == pFileImage->GetCollisionBoxInfo(imageIndex, collisionBoxType_, &pCollisionInfo)) {
      return;
    }

    if (IsMouseClick()) {
      Vector deltaPosition = curMousePosition - prevMousePosition_;
      if (false == pCollisionInfo->hasCollision_) {
        return;
      }

      pCollisionInfo->position_ += deltaPosition;
      pCollisionInfo->scale_ -= deltaPosition;
    }

    // SetPosition(pCollisionInfo->position_);

    UI* ownerUI = GetOwner();
    if (nullptr == ownerUI) {
      return;
    }

    /*Vector iamgeScale = pFileImage->GetScale(imageIndex);
    Vector ownerScale = ownerUI->GetScale();
    Vector scale = pCollisionInfo->scale_;
    Vector collisionOffset = pCollisionInfo->position_;
    Vector newPosition = {ownerScale.HalfX() - iamgeScale.HalfX() + collisionOffset.X, ownerScale.HalfY() - iamgeScale.HalfY() + collisionOffset.Y};
    SetPosition(newPosition);*/

    SetPosition({0.0f, 0.0f});

    prevMousePosition_ = curMousePosition;
  }

  else {
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
      if (false == pFileImage->GetCollisionBoxInfo(imageIndex, collisionBoxType_, &pCollisionInfo)) {
        return;
      }

      pCollisionInfo->scale_ += deltaPosition;
    }

    CollisionInfo* pCollisionInfo;
    if (false == pFileImage->GetCollisionBoxInfo(imageIndex, collisionBoxType_, &pCollisionInfo) || false == pCollisionInfo->hasCollision_) {
      return;
    }

    // SetPosition(pCollisionInfo->position_ + pCollisionInfo->scale_);

    UI* ownerUI = GetOwner();
    if (nullptr == ownerUI) {
      return;
    }

    Vector scale = ownerUI->GetScale();
    Vector collisionOffset = pCollisionInfo->position_;
    Vector collisionScale = pCollisionInfo->scale_;
    Vector newPosition = {scale.HalfX() + collisionOffset.X + collisionScale.X, scale.HalfY() + collisionOffset.Y + collisionScale.Y};
    SetPosition(newPosition);

    prevMousePosition_ = curMousePosition;
  }
}
