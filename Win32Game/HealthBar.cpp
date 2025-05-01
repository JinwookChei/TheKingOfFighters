#include "stdafx.h"
#include "HealthBar.h"

HealthBar::HealthBar()
    : pImage_(nullptr),
      imageIndex_(0),
      colorTransparent_({0, 0, 0, 0}) {
}

HealthBar::~HealthBar() {
}

void HealthBar::BeginPlay() {
  EnableCollision(false);
}

bool HealthBar::Initialize(unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent) {
  pImage_ = ImgManager::GetIntance()->GetImg(imageNum);
  if (nullptr == pImage_) {
    return false;
  }

  SetScale(pImage_->GetScale(imageIndex));

  imageIndex_ = imageIndex;
  colorTransparent_ = colorTransparent;

  return true;
}

void HealthBar::Tick(unsigned long long curTick) {
}

void HealthBar::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture || nullptr == pImage_) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Vector& imageScale = pImage_->GetScale(imageIndex_);

  renderTexture->Transparent(pImage_, imageIndex_, imageScale, colorTransparent_);
}
