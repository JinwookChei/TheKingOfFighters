#include "stdafx.h"
#include "Object.h"
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

  ImageRenderer* pRenderer = bindObject_->GetImageRenderer();
  if (nullptr == pRenderer) {
    return;
  }
  unsigned int imageIndex = pRenderer->GetImageIndex();

  IFileImage* pImage = (IFileImage*)pRenderer->GetImage();
  if (nullptr == pImage) {
    return;
  }

  switch (imageMoveDirType_) {
    case IMD_PlusRow: {
      pImage->AddImagePositionOffSet(imageIndex, {1.0f, 0.0f});
      break;
    }
    case IMD_MinusRow: {
      pImage->AddImagePositionOffSet(imageIndex, {-1.0f, 0.0f});
      break;
    }
    case IMD_PlusCol: {
      pImage->AddImagePositionOffSet(imageIndex, {0.0f, 1.0f});
      break;
    }
    case IMD_MinusCol: {
      pImage->AddImagePositionOffSet(imageIndex, {0.0f, -1.0f});
      break;
    }
    case IMD_Reset: {
      const Vector& curOffSet = pImage->GetImagePositionOffSet(imageIndex);
      pImage->AddImagePositionOffSet(imageIndex, -curOffSet);

      break;
    }
    default:
      break;
  }
}

Object* ImageMoveButton::GetBindObject() const {
  return bindObject_;
}

void ImageMoveButton::BindObject(Object* object) {
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
