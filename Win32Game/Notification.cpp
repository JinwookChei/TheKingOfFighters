#include "stdafx.h"
#include "Notification.h"

Notification::Notification()
    : pImage_(nullptr),
      localeScale_({1.0f, 1.0f}),
      imageIndex_(0),
      colorTransparent_({0, 0, 0, 0}) {
}

Notification::~Notification() {
}

void Notification::BeginPlay() {
}

bool Notification::Initialize(unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent) {
  pImage_ = ImgManager::GetIntance()->GetImg(imageNum);
  if (nullptr == pImage_) {
    return false;
  }

  SetScale(pImage_->GetScale(imageIndex));

  imageIndex_ = imageIndex;
  colorTransparent_ = colorTransparent;
  localeScale_ = Vector(0.7f, 0.7f);

  return true;
}

void Notification::Tick(unsigned long long curTick) {
  if (false == EnableTick()) {
    return;
  }

  Vector curPos = GetPosition();

  SetPosition({curPos.X + 1.0f, curPos.Y});
}

void Notification::Render(IRenderTexture* renderTexture) {
  if (false == EnableRender()) {
    return;
  }

  if (nullptr == renderTexture || nullptr == pImage_) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Vector& imageScale = pImage_->GetScale(imageIndex_) * localeScale_;

  renderTexture->AlphaBlend(pImage_, imageIndex_, imageScale, 1.0f);
  // renderTexture->Transparent(pImage_, imageIndex_, imageScale, colorTransparent_);
}
