#include "stdafx.h"

#include "CollisionBox.h"
#include "CollisionBoxCorner.h"
#include "ToolActor.h"
#include "DeleteCollisionButton.h"

DeleteCollisionButton::DeleteCollisionButton()
    : bindToolActor_(nullptr),
      bindCollisionBox_(nullptr),
      collisionBoxType_(CollisionBoxType::CBT_HitBoxTop) {
}

DeleteCollisionButton::~DeleteCollisionButton() {
}

void DeleteCollisionButton::Initialize(ToolActor* bindActor, CollisionBox* bindCollisionBox, CollisionBoxType boundType) {
  bindToolActor_ = bindActor;
  bindCollisionBox_ = bindCollisionBox;
  collisionBoxType_ = boundType;
}

void DeleteCollisionButton::BeginPlay() {
    
}

void DeleteCollisionButton::Tick(unsigned long long curTick) {
}

void DeleteCollisionButton::ClickDownEvent() {

    if (nullptr == bindToolActor_ || nullptr == bindCollisionBox_) {
    return;
  }

  CollisionBoxCorner* cornerStart = bindCollisionBox_->GetCornerStart();
  CollisionBoxCorner* cornerEnd = bindCollisionBox_->GetCornerEnd();
  if (nullptr == cornerStart || nullptr == cornerEnd) {
    return;
  }

  cornerStart->EnableCollision(false);
  cornerEnd->EnableCollision(false);


  IImage* pImage = bindToolActor_->GetImage();
  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  unsigned int imageIndex = bindToolActor_->GetImageIndex();

  CollisionInfo* pCollisionInfo;
  if (false == pFileImage->GetCollisionBoxInfo(imageIndex, collisionBoxType_, &pCollisionInfo)) {
    return;
  }

  pCollisionInfo->position_ = {0.0f, 0.0f};
  pCollisionInfo->scale_ = {0.0f, 0.0f};
  pCollisionInfo->hasCollision_ = false;
}

void DeleteCollisionButton::Render(IRenderTexture* renderTexture) {
}
