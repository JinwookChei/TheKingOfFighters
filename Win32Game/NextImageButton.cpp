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
  if (false == InputManager::Instance()->IsAnyKeyPress()) {
    return;
  }

  if (true == InputManager::Instance()->IsAnyKeyPress()) {
    if (InputManager::Instance()->IsDown(VK_RIGHT)) {
      if (nextImageType_ == NextImage_Next) {
        ClickDownEvent();
      }
    }

    if (InputManager::Instance()->IsDown(VK_LEFT)) {
      if (nextImageType_ == NextImage_Prev) {
        ClickDownEvent();
      }
    }
  }
}

void NextImageButton::ClickDownEvent() {
  if (nullptr == bindToolActor_) {
    return;
  }
  unsigned int imageIndex = bindToolActor_->GetImageIndex();

  if (nextImageType_ == NextImage_Next) {
    ++imageIndex;
  } else if (nextImageType_ == NextImage_Prev) {
    --imageIndex;
  }
  else if (nextImageType_ == NextImage_SuperNext)
  {
    imageIndex += 10;
  } else if (nextImageType_ == NextImage_SuperPrev) {
    imageIndex -= 10;
  }

  bindToolActor_->ChangeImage(imageIndex);
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
