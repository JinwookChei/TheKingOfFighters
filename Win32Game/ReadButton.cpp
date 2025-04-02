#include "stdafx.h"
#include "ToolActor.h"
#include "ReadButton.h"

ReadButton::ReadButton()
    : filePath_("../ContentsResource/test.csv"),
      bindToolActor_(nullptr) {
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

void ReadButton::BindObject(ToolActor* toolActor) {
  bindToolActor_ = toolActor;
}

void ReadButton::SetFilePath(const std::string& filePath) {
  filePath_ = filePath;
}

void ReadButton::ReadData() {
  if (nullptr == bindToolActor_) {
    return;
  }

  IImage* pImage = bindToolActor_->GetImage();

  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;

 
  pFileImage->CalculateTransformFromCSV(filePath_);


  unsigned int imageIndex = bindToolActor_->GetImageIndex();
  //bindToolActor_->SetImageIndex(imageIndex);

  MessageBox(NULL, L"안녕하세요! 이것은 간단한 메시지 창입니다.", L"알림", MB_OK);
}

void ReadButton::Render(IRenderTexture* renderTexture) {
}
