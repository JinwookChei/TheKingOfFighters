#include "stdafx.h"
#include "MPBar.h"


MPBar::MPBar()
    : pImage_(nullptr),
      imageIndex_(0),
      colorTransparent_({0, 0, 0, 0}) {
}

MPBar::~MPBar() {
}

void MPBar::BeginPlay() {
  EnableCollision(false);
}

bool MPBar::Initialize(unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent) {
  pImage_ = ImgManager::GetIntance()->GetImg(imageNum);
  if (nullptr == pImage_) {
    return false;
  }

  SetScale(pImage_->GetScale(imageIndex));

  imageIndex_ = imageIndex;
  colorTransparent_ = colorTransparent;

  return true;
}

void MPBar::Tick(unsigned long long curTick) {
}

void MPBar::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture || nullptr == pImage_) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Vector& imageScale = pImage_->GetScale(imageIndex_);

  //renderTexture->Transparent(pImage_, imageIndex_, imageScale, colorTransparent_);
  renderTexture->AlphaBlend(pImage_, imageIndex_, imageScale, 1.0f);
}
