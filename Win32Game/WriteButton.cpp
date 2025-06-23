#include "stdafx.h"
#include "ToolActor.h"
#include "WriteButton.h"

WriteButton::WriteButton()
    : filePath_("../ContentsResource/test.csv"),
      bindToolActor_(nullptr) {
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

void WriteButton::BindObject(ToolActor* toolActor) {
  bindToolActor_ = toolActor;
}

void WriteButton::SetFilePath(const std::string& filePath) {
  filePath_ = filePath;
}

void WriteButton::WriteData() {

  if (nullptr == bindToolActor_) {
    return;
  }

  IImage* pImage = bindToolActor_->GetImage();

  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  pFileImage->ExportImageInfoToCSV(filePath_);


  MessageBox(NULL, L"!!!주의!!! 정말로 저장하시겠습니까 ????", L"!!!주의!!!", MB_OK);
}

void WriteButton::Render(IRenderTexture* renderTexture) {
}
