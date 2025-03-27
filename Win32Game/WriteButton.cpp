#include "stdafx.h"
#include "ViewPortObject.h"
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

void WriteButton::BindObject(ViewPortObject* object) {
  bindObject_ = object;
}

void WriteButton::SetFilePath(const std::string& filePath) {
  filePath_ = filePath;
}

void WriteButton::WriteData() {
  /*ImageRenderer* pRenderer = bindObject_->GetOwnerImageRenderer();
  if (nullptr == pRenderer)
  {
    return;
  }

  IFileImage* fileImage = dynamic_cast<IFileImage*>(pRenderer->GetImage());
  if (nullptr == fileImage)
  {
    return;
  }

  fileImage->ExportImageInfoToCSV(filePath_);*/
}

void WriteButton::Render(IRenderTexture* renderTexture) {
}
