#include "stdafx.h"
#include "CollisionBound.h"
#include "ViewPortImage.h"
#include "DeleteCollisionButton.h"

DeleteCollisionButton::DeleteCollisionButton()
    : bindViewPortImage_(nullptr),
      boundType_(CollisionBoundType::CBT_HitBoxTop) {
}

DeleteCollisionButton::~DeleteCollisionButton() {
}

void DeleteCollisionButton::Initialize(ViewPortImage* bindViewPortImage, CollisionBoundType boundType) {
  bindViewPortImage_ = bindViewPortImage;
  boundType_ = boundType;
}

void DeleteCollisionButton::BeginPlay() {
    
}

void DeleteCollisionButton::Tick(unsigned long long curTick) {
}

void DeleteCollisionButton::ClickDownEvent() {

  if (nullptr == bindViewPortImage_) {
    return;
  }
  IImage* pImage = bindViewPortImage_->GetImage();
  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  unsigned int imageIndex = bindViewPortImage_->GetImageIndex();

  CollisionInfo* pCollisionInfo;
  if (false == pFileImage->GetCollisionBoxInfo(imageIndex, boundType_, &pCollisionInfo)) {
    return;
  }

  pCollisionInfo->position_ = {0.0f, 0.0f};
  pCollisionInfo->scale_ = {0.0f, 0.0f};
  pCollisionInfo->hasCollision_ = false;
}

void DeleteCollisionButton::Render(IRenderTexture* renderTexture) {
}
