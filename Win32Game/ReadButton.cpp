#include "stdafx.h"
#include "ViewPortImage.h"
#include "ReadButton.h"

ReadButton::ReadButton()
    : filePath_("../ContentsResource/test.csv"),
      bindObject_(nullptr) {
}

ReadButton::~ReadButton() {
}

void ReadButton::BeginPlay() {
}

void ReadButton::Tick(unsigned long long curTick) {
}

void ReadButton::ClickDownEvent() {
  ReadData();
}

void ReadButton::BindObject(ViewPortImage* object) {
  bindObject_ = object;
}

void ReadButton::SetFilePath(const std::string& filePath) {
  filePath_ = filePath;
}

void ReadButton::ReadData() {
  if (nullptr == bindObject_) {
    return;
  }

  IImage* pImage = bindObject_->GetImage();

  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  pFileImage->CalculateTransformFromCSV(filePath_);
}

void ReadButton::Render(IRenderTexture* renderTexture) {
}
