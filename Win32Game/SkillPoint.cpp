#include "stdafx.h"
#include "MPComponent.h"
#include "KOFPlayer.h"
#include "SkillPoint.h"

SkillPoint::SkillPoint()
    : pPlayer_(nullptr),
      onRender_(false),
      skillPointIndex_(0),
      pImage_(nullptr),
      localeScale_({1.0f, 1.0f}),
      imageIndex_(0),
      colorTransparent_({0, 0, 0, 0}) {
}

SkillPoint::~SkillPoint() {
}

void SkillPoint::BeginPlay() {
  EnableCollision(false);
}

void SkillPoint::Tick(unsigned long long curTick) {
  const MPComponent* pMPComponent = pPlayer_->GetMPComponent();
  if (nullptr == pMPComponent) {
    return;
  }

  if (skillPointIndex_ < pMPComponent->SkillPoint()) {
    onRender_ = true;
  } else {
    onRender_ = false;
  }
}

bool SkillPoint::Initialize(KOFPlayer* bindPlayer, int skillPointIndex, unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent) {
  pImage_ = ImgManager::GetIntance()->GetImg(imageNum);
  if (nullptr == pImage_) {
    return false;
  }

  SetScale(pImage_->GetScale(imageIndex));

  pPlayer_ = bindPlayer;
  skillPointIndex_ = skillPointIndex;
  imageIndex_ = imageIndex;
  colorTransparent_ = colorTransparent;
  localeScale_ = Vector(0.1f, 0.1f);

  return true;
}

void SkillPoint::Render(IRenderTexture* renderTexture) {
  if (false == onRender_) {
    return;
  }

  if (nullptr == renderTexture || nullptr == pImage_) {
    return;
  }

  const Vector& imageScale = pImage_->GetScale(imageIndex_) * localeScale_;

  renderTexture->Transparent(pImage_, imageIndex_, imageScale, colorTransparent_);
}
