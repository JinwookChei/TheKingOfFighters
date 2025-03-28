#include "stdafx.h"
#include "ViewPortImage.h"
#include "ImageMoveButton.h"

ImageMoveButton::ImageMoveButton()
    : bindObject_(nullptr),
      imageMoveDirType_(ImageMoveDirType::IMD_None) {
}

ImageMoveButton::~ImageMoveButton() {
}

void ImageMoveButton::BeginPlay() {
}

void ImageMoveButton::Tick(unsigned long long curTick) {
}

void ImageMoveButton::ClickDownEvent() {
  if (nullptr == bindObject_) {
    return;
  }

  IImage* pImage = bindObject_->GetImage();
  if (nullptr == pImage || true == pImage->IsRenderTexture())
  {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  unsigned int imageIndex = bindObject_->GetImageIndex();

  switch (imageMoveDirType_) {
    case IMD_PlusRow: {
      bindObject_->AddPositionOffSet({1.0f, 0.0f});
      break;
    }
    case IMD_MinusRow: {
      bindObject_->AddPositionOffSet({-1.0f, 0.0f});
      break;
    }
    case IMD_PlusCol: {
      bindObject_->AddPositionOffSet({0.0f, 1.0f});
      break;
    }
    case IMD_MinusCol: {
      bindObject_->AddPositionOffSet({0.0f, -1.0f});
      break;
    }
    case IMD_Reset: {

      bindObject_->ResetPostionOffset();

      break;
    }
    default:
      break;
  }
}

ViewPortImage* ImageMoveButton::GetBindObject() const {
  return bindObject_;
}

void ImageMoveButton::BindObject(ViewPortImage* object) {
  if (nullptr == object) {
    return;
  }

  bindObject_ = object;
}

ImageMoveDirType ImageMoveButton::GetImageMoveDirType() const {
  return imageMoveDirType_;
}

void ImageMoveButton::SetImageMoveDirType(ImageMoveDirType moveDirType) {
  imageMoveDirType_ = moveDirType;
}

void ImageMoveButton::Render(IRenderTexture* renderTexture) {
}
