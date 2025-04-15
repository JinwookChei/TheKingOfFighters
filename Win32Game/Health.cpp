#include "stdafx.h"
#include "Health.h"
#include "Player.h"

Health::Health()
{
}

Health::~Health() {
}

void Health::BeginPlay() {
  //pImageRenderer_ = CreateImageRender();
  //IImage* pImage = ImgManager::GetIntance()->GetImg(6);

  //pImageRenderer_->SetImage(pImage);
  //pImageRenderer_->SetTransparentColor(Color8Bit{0, 0, 0, 0});
  //pImageRenderer_->SetLocalScale({1.0f, 1.0f});
  //pImageRenderer_->SetImageRenderType(ImageRenderType::LeftTop);
}

bool Health::Initialize(Player* bindPlayer) {
  //if (nullptr == bindPlayer) {
  //  return false;
  //}

  //pBindPalyer_ = bindPlayer;

  return true;
}

void Health::Tick(unsigned long long curTick) {
}

void Health::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  //renderTexture->Text(font_, text_, fontSize_, {0.0f, 0.0f} /*localPosition_*/, textColor_);
}
