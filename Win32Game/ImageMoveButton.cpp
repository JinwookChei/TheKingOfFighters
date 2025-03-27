#include "stdafx.h"
#include "ImageObject.h"
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

  IImage* image = bindObject_->GetImage();
  if (nullptr == image || true == image->IsRenderTexture()) {
    return;
  }

  IFileImage* fileImage = (IFileImage*)image;

  unsigned int imageIndex = bindObject_->GetImageIndex();

  switch (imageMoveDirType_) {
    case IMD_PlusRow: {
      fileImage->AddImagePositionOffSet(imageIndex, {1.0f, 0.0f});
      break;
    }
    case IMD_MinusRow: {
      fileImage->AddImagePositionOffSet(imageIndex, {-1.0f, 0.0f});
      break;
    }
    case IMD_PlusCol: {
      fileImage->AddImagePositionOffSet(imageIndex, {0.0f, 1.0f});
      break;
    }
    case IMD_MinusCol: {
      fileImage->AddImagePositionOffSet(imageIndex, {0.0f, -1.0f});
      break;
    }
    case IMD_Reset: {
      const Vector& curOffSet = fileImage->GetImagePositionOffSet(imageIndex);
      fileImage->AddImagePositionOffSet(imageIndex, -curOffSet);

      break;
    }
    default:
      break;
  }
}

ImageObject* ImageMoveButton::GetBindObject() const {
  return bindObject_;
}

void ImageMoveButton::BindObject(ImageObject* object) {
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
