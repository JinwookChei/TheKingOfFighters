#include "stdafx.h"
#include "CollisionBox.h"
#include "ViewPortImage.h"
#include "CollisionBoxCorner.h"
#include "CreateCollisionButton.h"

CreateCollisionButton::CreateCollisionButton()
    : bindViewPortImage_(nullptr),
      bindCollisionBox_(nullptr),
      collisionBoxType_(CollisionBoxType::CBT_HitBoxTop) {
}

CreateCollisionButton::~CreateCollisionButton() {
}

void CreateCollisionButton::Initialize(ViewPortImage* bindViewPortImage, CollisionBox* bindCollisionBox, CollisionBoxType collisionBoxType) {
  bindViewPortImage_ = bindViewPortImage;
  bindCollisionBox_ = bindCollisionBox;
  collisionBoxType_ = collisionBoxType;
}

void CreateCollisionButton::BeginPlay() {
}

void CreateCollisionButton::Tick(unsigned long long curTick) {
}

void CreateCollisionButton::ClickDownEvent() {

  if (nullptr == bindViewPortImage_ || nullptr ==  bindCollisionBox_) {
    return;
  }

  CollisionBoxCorner* cornerStart = bindCollisionBox_->GetCornerStart();
  CollisionBoxCorner* cornerEnd = bindCollisionBox_->GetCornerEnd();
  if (nullptr == cornerStart || nullptr == cornerEnd)
  {
    return;
  }

  cornerStart->EnableCollision(true);
  cornerEnd->EnableCollision(true);


  IImage* pImage = bindViewPortImage_->GetImage();
  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  unsigned int imageIndex = bindViewPortImage_->GetImageIndex();

  CollisionInfo* pCollisionInfo;
  if (false == pFileImage->GetCollisionBoxInfo(imageIndex, collisionBoxType_, &pCollisionInfo)) {
    return;
  }

  pCollisionInfo->hasCollision_ = true;
  pCollisionInfo->position_ = {0.0f, 0.0f};
  pCollisionInfo->scale_ = {100.0f, 100.0f};
}

void CreateCollisionButton::Render(IRenderTexture* renderTexture) {
}
