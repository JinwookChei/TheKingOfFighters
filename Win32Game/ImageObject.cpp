#include "stdafx.h"
#include "ImageObject.h"

ImageObject::ImageObject()
    : ownerImageRender_(nullptr),
      prevMousePosition_({0.0f, 0.0f}) {
}

ImageObject::~ImageObject() {
}

void ImageObject::BeginPlay() {
  // NEW
  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  ownerImageRender_ = owner->GetImageRenderer();
  IImage* pFind = ImgManager::GetIntance()->GetImg(1);
  ownerImageRender_->SetImage(pFind, 0);
  ownerImageRender_->SetTransparentColor(Color8Bit{17, 91, 124, 0});
  ownerImageRender_->SetImageRenderType(ImageRenderType::Center);
  ownerImageRender_->SetLocalScale({4.0f, 4.0f});
  ownerImageRender_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 1.0f, .color_ = Color8Bit::Green});

  // SetDebugParameter({.on_ = true, .linethickness_ = 1.0f, .color_ = Color8Bit::Red});
  // imageRender_ = CreateImageRender();
  SetScale(ownerImageRender_->GetScale() * ownerImageRender_->GetLocalScale());
}

void ImageObject::Tick(unsigned long long curTick) {
  //   UI* owner = GetOwner();

  Vector curMousePosition = GEngineCore->GetMousePosition();
  if (IsMouseClick()) {
    Vector deltaPosition = curMousePosition - prevMousePosition_;

    unsigned int imageIndex = ownerImageRender_->GetImageIndex();

    IFileImage* pImage = (IFileImage*)ownerImageRender_->GetImage();
    if (nullptr == pImage) {
      return;
    }
    pImage->AddImagePositionOffSet(imageIndex, deltaPosition);
  }
  prevMousePosition_ = curMousePosition;
}

ImageRenderer* ImageObject::GetOwnerImageRenderer() const {
  return ownerImageRender_;
}


void ImageObject::Render(IRenderTexture* renderTexture) {
}
