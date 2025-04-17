#include "stdafx.h"
#include "Health.h"
#include "Player.h"

Health::Health()
    : pPlayer_(nullptr),
      pImage_(nullptr),
      imageIndex_(0),
      colorTransparent_({0, 0, 0, 0}) {
}

Health::~Health() {
}

void Health::BeginPlay() {
  EnableCollision(false);
}

bool Health::Initialize(Player* bindPlayer, unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent) {
  if (nullptr == bindPlayer) {
    return false;
  }

  pImage_ = ImgManager::GetIntance()->GetImg(imageNum);
  if (nullptr == pImage_) {
    return false;
  }

  SetScale(pImage_->GetScale(imageIndex));

  pPlayer_ = bindPlayer;
  imageIndex_ = imageIndex;
  colorTransparent_ = colorTransparent;

  return true;
}

void Health::Tick(unsigned long long curTick) {

}

void Health::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture || nullptr == pPlayer_|| nullptr == pImage_) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Vector& imageScale = pImage_->GetScale(imageIndex_);

  renderTexture->Transparent(pImage_, imageIndex_, imageScale, colorTransparent_);
}
