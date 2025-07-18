#include "stdafx.h"
#include "CollisionBox.h"
#include "ToolActor.h"
#include "CollisionBoxCorner.h"
#include "CreateCollisionButton.h"

CreateCollisionButton::CreateCollisionButton()
    : bindToolActor_(nullptr),
      bindCollisionBox_(nullptr),
      collisionBoxType_(CollisionBoxType::CBT_HitBoxTop) {
}

CreateCollisionButton::~CreateCollisionButton() {
}

void CreateCollisionButton::Initialize(ToolActor* bindActor, CollisionBox* bindCollisionBox, CollisionBoxType collisionBoxType) {
  bindToolActor_ = bindActor;
  bindCollisionBox_ = bindCollisionBox;
  collisionBoxType_ = collisionBoxType;
}

void CreateCollisionButton::BeginPlay() {
}

void CreateCollisionButton::Tick(unsigned long long curTick) {
}

void CreateCollisionButton::ClickDownEvent() {

  if (nullptr == bindToolActor_ || nullptr == bindCollisionBox_) {
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


  IImage* pImage = bindToolActor_->GetImage();
  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  unsigned int imageIndex = bindToolActor_->GetImageIndex();
  ImageRenderType  imageRenderType = bindToolActor_->GetImageRenderer()->GetImageRenderType();
  Vector localScale = bindToolActor_->GetImageRenderer()->GetLocalScale();  
  Vector imagePostionOffSet = pFileImage->GetImagePositionOffSet(imageIndex);

  CollisionInfo* pCollisionInfo;
  if (false == pFileImage->GetCollisionBoxInfo(imageIndex, collisionBoxType_, &pCollisionInfo)) {
    return;
  }

  pCollisionInfo->hasCollision_ = true;
  pCollisionInfo->scale_ = pFileImage->GetScale(imageIndex) * localScale;
  pCollisionInfo->position_ = imagePostionOffSet;

  switch (imageRenderType) {
    case ImageRenderType::Center:
      //pCollisionInfo->position_ = {0.0f, 0.0f};
      break;
    case ImageRenderType::Left:
      //pCollisionInfo->position_ = {+pCollisionInfo->scale_.HalfX(), 0.0f};
      pCollisionInfo->position_.X += pCollisionInfo->scale_.HalfX();
      break;
    case ImageRenderType::Right:
      //pCollisionInfo->position_ = {-pCollisionInfo->scale_.HalfX(), 0.0f};
      pCollisionInfo->position_.X -= pCollisionInfo->scale_.HalfX();
      break;
    case ImageRenderType::Top:
      //pCollisionInfo->position_ = {0.0f, +pCollisionInfo->scale_.HalfY()};
      pCollisionInfo->position_.Y += pCollisionInfo->scale_.HalfY();
      break;
    case ImageRenderType::Bottom:
      //pCollisionInfo->position_ = {0.0f, -pCollisionInfo->scale_.HalfY()};
      pCollisionInfo->position_.Y -= pCollisionInfo->scale_.HalfY();
      break;
    case ImageRenderType::LeftTop:
      //pCollisionInfo->position_ = {+pCollisionInfo->scale_.HalfX(), +pCollisionInfo->scale_.HalfY()};
      pCollisionInfo->position_.X += pCollisionInfo->scale_.HalfX();
      pCollisionInfo->position_.Y += pCollisionInfo->scale_.HalfY();
      break;
    case ImageRenderType::LeftBottom:
      //pCollisionInfo->position_ = {+pCollisionInfo->scale_.HalfX(), -pCollisionInfo->scale_.HalfY()};
      pCollisionInfo->position_.X += pCollisionInfo->scale_.HalfX();
      pCollisionInfo->position_.Y -= pCollisionInfo->scale_.HalfY();
      break;
    case ImageRenderType::RightTop:
      //pCollisionInfo->position_ = {-pCollisionInfo->scale_.HalfX(), +pCollisionInfo->scale_.HalfY()};
      pCollisionInfo->position_.X -= pCollisionInfo->scale_.HalfX();
      pCollisionInfo->position_.Y += pCollisionInfo->scale_.HalfY();
      break;
    case ImageRenderType::RightBottom:
      //pCollisionInfo->position_ = {-pCollisionInfo->scale_.HalfX(), -pCollisionInfo->scale_.HalfY()};
      pCollisionInfo->position_.X -= pCollisionInfo->scale_.HalfX();
      pCollisionInfo->position_.Y -= pCollisionInfo->scale_.HalfY();
      break;
    default:
      break;
  }

    
}

void CreateCollisionButton::Render(IRenderTexture* renderTexture) {
}
