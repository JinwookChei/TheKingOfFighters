#include "stdafx.h"
#include "Portrait.h"

Portrait::Portrait()
    : pImage_(nullptr),
      localeScale_({0.0f, 0.0f}),
      imageIndex_(0),
      colorTransparent_({0, 0, 0, 0}) {
}

Portrait::~Portrait() {
}

void Portrait::BeginPlay() {
  EnableCollision(false);

}

bool Portrait::Initialize(unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent) {
  pImage_ = ImgManager::GetIntance()->GetImg(imageNum);
  if (nullptr == pImage_) {
    return false;
  }
  
  SetScale(pImage_->GetScale(imageIndex));

  imageIndex_ = imageIndex;
  colorTransparent_ = colorTransparent;
  localeScale_ = Vector(4.5f, 4.5f);

  return true;
}

void Portrait::Tick(unsigned long long curTick) {
}

void Portrait::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture || nullptr == pImage_) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Vector& imageScale = pImage_->GetScale(imageIndex_) * localeScale_;

  renderTexture->Transparent(pImage_, imageIndex_, imageScale, colorTransparent_);
}
