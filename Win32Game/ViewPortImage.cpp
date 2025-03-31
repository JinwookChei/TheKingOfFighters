#include "stdafx.h"
#include "ViewPortImage.h"

ViewPortImage::ViewPortImage()
    : owner_(nullptr),
      image_(nullptr),
      imageIndex_(0),
      localeScale_{1.0f, 1.0f},
      TransColor_(Color8Bit::Magenta),
      prevMousePosition_({0.0f, 0.0f}) {
}

ViewPortImage::~ViewPortImage() {
}

void ViewPortImage::BeginPlay() {
  owner_ = GetOwner();
  if (nullptr == owner_) {
    return;
  }

  image_ = ImgManager::GetIntance()->GetImg(1);

  TransColor_ = Color8Bit{169, 139, 150, 0};

  Vector scale = image_->GetScale(imageIndex_);

  localeScale_ = {3.0f, 3.0f};

  SetScale(scale * localeScale_);

  if (false == image_->IsRenderTexture()) {
    IFileImage* fileImage = (IFileImage*)image_;

    Vector imageOffSet = fileImage->GetImagePositionOffSet(imageIndex_);
    Vector ownerHalfScale = {owner_->GetScale().HalfX(), owner_->GetScale().HalfY()};
    SetPosition(ownerHalfScale + imageOffSet);
  } else {
    Vector ownerHalfScale = {owner_->GetScale().HalfX(), owner_->GetScale().HalfY()};
    SetPosition(ownerHalfScale);
  }
}

void ViewPortImage::Tick(unsigned long long curTick) {
  Vector curMousePosition = GEngineCore->GetMousePosition();
  if (IsMouseClick()) {
    Vector deltaPosition = curMousePosition - prevMousePosition_;

    AddPositionOffSet(deltaPosition);
  }

  prevMousePosition_ = curMousePosition;
}

void ViewPortImage::ClickDownEvent() {

}

IImage* ViewPortImage::GetImage() const {
  return image_;
}

void ViewPortImage::ChangeImage() {
}

unsigned int ViewPortImage::GetImageIndex() const {
  return imageIndex_;
}

void ViewPortImage::SetImageIndex(unsigned int index) {
  imageIndex_ = index;

  if (false == image_->IsRenderTexture()) {
    IFileImage* fileImage = (IFileImage*)image_;

    Vector imageOffSet = fileImage->GetImagePositionOffSet(imageIndex_);
    Vector ownerHalfScale = {owner_->GetScale().HalfX(), owner_->GetScale().HalfY()};
    SetPosition(ownerHalfScale + imageOffSet);
  }
}

void ViewPortImage::AddPositionOffSet(const Vector& offSet) {
  if (true == image_->IsRenderTexture()) {
    return;
  }

  IFileImage* fileImage = (IFileImage*)image_;
  fileImage->AddImagePositionOffSet(imageIndex_, offSet);   
  fileImage->AddCollisionBoxPositionOffSet(imageIndex_, offSet);

  Vector imageOffSet = fileImage->GetImagePositionOffSet(imageIndex_);
  Vector ownerHalfScale = {owner_->GetScale().HalfX(), owner_->GetScale().HalfY()};
  SetPosition(ownerHalfScale + imageOffSet);
}

void ViewPortImage::ResetPostionOffset() {
  if (true == image_->IsRenderTexture()) {
    return;
  }

  IFileImage* fileImage = (IFileImage*)image_;
  Vector tempOffSet = fileImage->GetImagePositionOffSet(imageIndex_);
  fileImage->AddImagePositionOffSet(imageIndex_, -tempOffSet);
  fileImage->AddCollisionBoxPositionOffSet(imageIndex_, -tempOffSet);

  Vector imageOffSet = fileImage->GetImagePositionOffSet(imageIndex_);
  Vector ownerHalfScale = {owner_->GetScale().HalfX(), owner_->GetScale().HalfY()};
  SetPosition(ownerHalfScale + imageOffSet);
}

Vector ViewPortImage::GetPositionOffSet() const {
  if (true == image_->IsRenderTexture()) {
    return {0.0f, 0.0f};
  }

  IFileImage* fileImage = (IFileImage*)image_;
  return fileImage->GetImagePositionOffSet(imageIndex_);
}

void ViewPortImage::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture || nullptr == image_) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Transform& transform = GetTransform();

  renderTexture->Transparent(image_, imageIndex_, transform.GetScale(), TransColor_);
  renderTexture->SetAlpha(1.0f, transform, true, owner->GetCurrentColor());
}
