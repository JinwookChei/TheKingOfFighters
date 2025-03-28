#include "stdafx.h"
#include "CollisionBound.h"
#include "ViewPortImage.h"
#include "CreateCollisionButton.h"

CreateCollisionButton::CreateCollisionButton()
    : bindViewPortImage_(nullptr),
      boundType_(CollisionBoundType::CBT_HitBoxTop) {
}

CreateCollisionButton::~CreateCollisionButton() {
}

void CreateCollisionButton::Initialize(ViewPortImage* bindViewPortImage, CollisionBoundType boundType) {

  bindViewPortImage_ = bindViewPortImage;
  boundType_ = boundType;
}

void CreateCollisionButton::BeginPlay() {
}

void CreateCollisionButton::Tick(unsigned long long curTick) {
}

void CreateCollisionButton::ClickDownEvent() {

  if (nullptr == bindViewPortImage_) {
    return;
  }
 IImage* pImage = bindViewPortImage_->GetImage();
 if (nullptr == pImage || true == pImage->IsRenderTexture())
 {
   return;
  }
 
 IFileImage* pFileImage = (IFileImage*)pImage;
 unsigned int imageIndex = bindViewPortImage_->GetImageIndex();

 CollisionInfo* collisionInfo;
 if (false == pFileImage->GetCollisionBoxInfo(imageIndex, boundType_, &collisionInfo))
 {
   return;
 }

 collisionInfo->position_ = {100.0f, 100.0f};
 collisionInfo->scale_ = {100.0f, 100.0f};
 collisionInfo->hasCollision_ = true;
}

void CreateCollisionButton::Render(IRenderTexture* renderTexture) {
}
