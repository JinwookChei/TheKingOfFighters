#include "stdafx.h"
#include "ToolActor.h"
#include "ImageMoveButton.h"

ImageMoveButton::ImageMoveButton()
    : bindToolActor_(nullptr),
      imageMoveDirType_(ImageMoveDirType::IMD_None) {
}

ImageMoveButton::~ImageMoveButton() {
}

void ImageMoveButton::BeginPlay() {
}

void ImageMoveButton::Tick(unsigned long long curTick) {
}

void ImageMoveButton::ClickDownEvent() {
  if (nullptr == bindToolActor_) {
    return;
  }

  IImage* pImage = bindToolActor_->GetImage();
  if (nullptr == pImage || true == pImage->IsRenderTexture())
  {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  unsigned int imageIndex = bindToolActor_->GetImageIndex();

  switch (imageMoveDirType_) {
    case IMD_PlusRow: {
      bindToolActor_->AddPositionOffSet({1.0f, 0.0f});
      break;
    }
    case IMD_MinusRow: {
      bindToolActor_->AddPositionOffSet({-1.0f, 0.0f});
      break;
    }
    case IMD_PlusCol: {
      bindToolActor_->AddPositionOffSet({0.0f, 1.0f});
      break;
    }
    case IMD_MinusCol: {
      bindToolActor_->AddPositionOffSet({0.0f, -1.0f});
      break;
    }
    case IMD_Reset: {

      //bindToolActor_->ResetPostionOffset();

      break;
    }
    default:
      break;
  }
}

ToolActor* ImageMoveButton::GetBindObject() const {
  return bindToolActor_;
}

void ImageMoveButton::BindObject(ToolActor* object) {
  if (nullptr == object) {
    return;
  }

  bindToolActor_ = object;
}

ImageMoveDirType ImageMoveButton::GetImageMoveDirType() const {
  return imageMoveDirType_;
}

void ImageMoveButton::SetImageMoveDirType(ImageMoveDirType moveDirType) {
  imageMoveDirType_ = moveDirType;
}

void ImageMoveButton::Render(IRenderTexture* renderTexture) {
}
