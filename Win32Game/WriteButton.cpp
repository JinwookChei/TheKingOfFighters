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

  int result = MessageBox(NULL, L"!!!����!!! ������ �����Ͻðڽ��ϱ� ????", L"!!!����!!!", MB_YESNO | MB_ICONQUESTION);
  if (result == IDYES) {
    IFileImage* pFileImage = (IFileImage*)pImage;
    pFileImage->ExportImageInfoToCSV(filePath_);  
  } else if (result == IDNO) {
    return;    
  }
}

void WriteButton::Render(IRenderTexture* renderTexture) {
}
