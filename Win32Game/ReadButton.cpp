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
  std::wstringstream wss;
  wss << L"!!!주의!!! 정보를 불러올까요? ????\n FilePath : " << std::wstring(filePath_.begin(), filePath_.end());

  int result = MessageBox(NULL, wss.str().c_str(), L"READ", MB_YESNO | MB_ICONQUESTION);
  if (result == IDYES) {
    IFileImage* pFileImage = (IFileImage*)pImage;
    pFileImage->ApplyImageInfoFromCSV(filePath_);  
  } else if (result == IDNO) {
    return;
  }
  

  // unsigned int imageIndex = bindToolActor_->GetImageIndex();
  // bindToolActor_->SetImageIndex(imageIndex);
}

void ReadButton::Render(IRenderTexture* renderTexture) {
}
