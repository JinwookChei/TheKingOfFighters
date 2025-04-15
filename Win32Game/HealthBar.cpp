#include "stdafx.h"
#include "HealthBar.h"
#include "Player.h"

HealthBar::HealthBar(){
}

HealthBar::~HealthBar() {
}

void HealthBar::BeginPlay() {
  //pImageRenderer_ = CreateImageRender();
  //IImage* pImage = ImgManager::GetIntance()->GetImg(5);

  //pImageRenderer_->SetImage(pImage);
  //pImageRenderer_->SetTransparentColor(Color8Bit{0, 0, 0, 0});
  //pImageRenderer_->SetLocalScale({1.0f, 1.0f});
  //pImageRenderer_->SetImageRenderType(ImageRenderType::LeftTop);
}

bool HealthBar::Initialize(Player* bindPlayer) {
  return true;
}

void HealthBar::Tick(unsigned long long curTick) {
}

void HealthBar::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  //renderTexture->Text(font_, text_, fontSize_, {0.0f, 0.0f} /*localPosition_*/, textColor_);
}
