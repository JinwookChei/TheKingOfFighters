#include "stdafx.h"
#include "Object.h"
#include "NextImageButton.h"


NextImageButton::NextImageButton()
    : bindObject_(nullptr),
      nextImageType_(NextImageType::NextImage_Next) {
}

NextImageButton::~NextImageButton() {
}

void NextImageButton::BeginPlay() {
}

void NextImageButton::Tick(unsigned long long curTick) {
}

void NextImageButton::ClickDownEvent() {
  if (nullptr == bindObject_) {
    return;
  }

  ImageRenderer* pTargetRenderer = bindObject_->GetImageRenderer();
  if (nullptr == pTargetRenderer) {
    return;
  }

  unsigned int tempIndex = pTargetRenderer->GetImageIndex();

  IImage* pImage = pTargetRenderer->GetImage();

  if (nullptr == pImage) {
    return;
  }

  if (nextImageType_ == NextImage_Next) {
    ++tempIndex;
  } else if (nextImageType_ == NextImage_Prev) {
    --tempIndex;
  }

  if (tempIndex > pImage->GetImageCount() - 1 || tempIndex < 0) {
    tempIndex = 0;
  }
  pTargetRenderer->SetImage(pImage, tempIndex);
}

Object* NextImageButton::GetBindObject() const {
  return bindObject_;
}

void NextImageButton::BindObject(Object* object) {
  if (nullptr == object) {
    return;
  }

  bindObject_ = object;
}

void NextImageButton::SetNextImageType(NextImageType nextImageType) {
  nextImageType_ = nextImageType;
}

void NextImageButton::Render(IRenderTexture* renderTexture) {
}
