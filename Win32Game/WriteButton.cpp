#include "stdafx.h"
#include "ViewPortImage.h"
#include "WriteButton.h"

WriteButton::WriteButton()
    : filePath_("../ContentsResource/test.csv"),
      bindObject_(nullptr) {
}

WriteButton::~WriteButton() {
}

void WriteButton::BeginPlay() {
}

void WriteButton::Tick(unsigned long long curTick) {
}

void WriteButton::ClickDownEvent() {
  WriteData();
}

void WriteButton::BindObject(ViewPortImage* object) {
  bindObject_ = object;
}

void WriteButton::SetFilePath(const std::string& filePath) {
  filePath_ = filePath;
}

void WriteButton::WriteData() {
  if (nullptr == bindObject_) {
    return;
  }

  IImage* pImage = bindObject_->GetImage();

  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  pFileImage->ExportImageInfoToCSV(filePath_);
}

void WriteButton::Render(IRenderTexture* renderTexture) {
}
