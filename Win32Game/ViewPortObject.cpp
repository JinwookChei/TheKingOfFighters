#include "stdafx.h"
#include "ViewPortObject.h"

ViewPortObject::ViewPortObject()
    : owner_(nullptr),
      image_(nullptr),
      imageIndex_(0),
      localeScale_{1.0f, 1.0f},
      TransColor_(Color8Bit::Magenta) {
}

ViewPortObject::~ViewPortObject() {
}

void ViewPortObject::BeginPlay() {
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

void ViewPortObject::Tick(unsigned long long curTick) {
}

void ViewPortObject::ClickDownEvent() {
}

IImage* ViewPortObject::GetImage() const {
  return image_;
}

void ViewPortObject::ChangeImage() {
}

unsigned int ViewPortObject::GetImageIndex() const {
  return imageIndex_;
}

void ViewPortObject::SetImageIndex(unsigned int index) {
  imageIndex_ = index;

  if (false == image_->IsRenderTexture()) {
    IFileImage* fileImage = (IFileImage*)image_;

    Vector imageOffSet = fileImage->GetImagePositionOffSet(imageIndex_);
    Vector ownerHalfScale = {owner_->GetScale().HalfX(), owner_->GetScale().HalfY()};
    SetPosition(ownerHalfScale + imageOffSet);
  }
}

void ViewPortObject::AddPositionOffSet(const Vector& offSet) {
  if (true == image_->IsRenderTexture()) {
    return;
  }

  IFileImage* fileImage = (IFileImage*)image_;
  fileImage->AddImagePositionOffSet(imageIndex_, offSet);

  Vector imageOffSet = fileImage->GetImagePositionOffSet(imageIndex_);
  Vector ownerHalfScale = {owner_->GetScale().HalfX(), owner_->GetScale().HalfY()};
  SetPosition(ownerHalfScale + imageOffSet);
}

void ViewPortObject::ResetPostionOffset() {
  if (true == image_->IsRenderTexture()) {
    return;
  }

  IFileImage* fileImage = (IFileImage*)image_;
  Vector tempOffSet = fileImage->GetImagePositionOffSet(imageIndex_);
  fileImage->AddImagePositionOffSet(imageIndex_, -tempOffSet);

  Vector imageOffSet = fileImage->GetImagePositionOffSet(imageIndex_);
  Vector ownerHalfScale = {owner_->GetScale().HalfX(), owner_->GetScale().HalfY()};
  SetPosition(ownerHalfScale + imageOffSet);
}

Vector ViewPortObject::GetPositionOffSet() const {
  if (true == image_->IsRenderTexture()) {
    return {0.0f, 0.0f};
  }

  IFileImage* fileImage = (IFileImage*)image_;
  return fileImage->GetImagePositionOffSet(imageIndex_);
}

void ViewPortObject::Render(IRenderTexture* renderTexture) {
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
