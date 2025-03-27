#include "stdafx.h"
#include "ImageObject.h"

ImageObject::ImageObject()
    : image_(nullptr),
      imageIndex_(0),
      prevMousePosition_({0.0f, 0.0f}) {
}

ImageObject::~ImageObject() {
}

void ImageObject::BeginPlay() {
  image_ = ImgManager::GetIntance()->GetImg(1);
  
  //Transform renderTransform = image_->RenderTransform(imageIndex_);
  Vector imageScale = image_->GetScale(imageIndex_);
  Vector localeScale(4.0f, 4.0f);
  SetScale(imageScale * localeScale);
}

void ImageObject::Tick(unsigned long long curTick) {

}

IImage* ImageObject::GetImage() const {
  return image_;
}

unsigned int ImageObject::GetImageIndex() const {
  return imageIndex_;
}

void ImageObject::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture || nullptr == image_) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Transform& transform = GetTransform();
  renderTexture->Transparent(image_, imageIndex_, transform.GetScale(), Color8Bit{169, 139, 150, 0});
  renderTexture->SetAlpha(1.0f, transform, true, owner->GetCurrentColor());
}
