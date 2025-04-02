#include "stdafx.h"
#include "ToolActor.h"
#include "NextImageButton.h"


NextImageButton::NextImageButton()
    : bindToolActor_(nullptr),
      nextImageType_(NextImageType::NextImage_Next) {
}

NextImageButton::~NextImageButton() {
}

void NextImageButton::BeginPlay() {
}

void NextImageButton::Tick(unsigned long long curTick) {
}

void NextImageButton::ClickDownEvent() {
  if (nullptr == bindToolActor_) {
    return;
  }

  IImage* pImage = bindToolActor_->GetImage();
  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }
  IFileImage* pFileImage = (IFileImage*)pImage;
  unsigned int imageIndex = bindToolActor_->GetImageIndex();


  if (nextImageType_ == NextImage_Next) {
    ++imageIndex;
  } else if (nextImageType_ == NextImage_Prev) {
    --imageIndex;
  }

  if (imageIndex > pImage->GetImageCount() - 1) {
    imageIndex = 0;
  }

  //bindToolActor_->SetImageIndex(imageIndex);
}

ToolActor* NextImageButton::GetBindObject() const {
  return bindToolActor_;
}

void NextImageButton::BindObject(ToolActor* object) {
  if (nullptr == object) {
    return;
  }

  bindToolActor_ = object;
}

void NextImageButton::SetNextImageType(NextImageType nextImageType) {
  nextImageType_ = nextImageType;
}

void NextImageButton::Render(IRenderTexture* renderTexture) {
}
