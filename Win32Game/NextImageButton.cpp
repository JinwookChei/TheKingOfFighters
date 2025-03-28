#include "stdafx.h"
#include "ViewPortImage.h"
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

  IImage* pImage = bindObject_->GetImage();
  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }
  IFileImage* pFileImage = (IFileImage*)pImage;
  unsigned int imageIndex = bindObject_->GetImageIndex();


  if (nextImageType_ == NextImage_Next) {
    ++imageIndex;
  } else if (nextImageType_ == NextImage_Prev) {
    --imageIndex;
  }

  if (imageIndex > pImage->GetImageCount() - 1) {
    imageIndex = 0;
  }

  bindObject_->SetImageIndex(imageIndex);
}

ViewPortImage* NextImageButton::GetBindObject() const {
  return bindObject_;
}

void NextImageButton::BindObject(ViewPortImage* object) {
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
