#include "stdafx.h"
#include "Effect.h"
#include "CollisionComponent.h"
#include "ImageRenderer.h"

Effect::Effect()
    : pEffectInfo_(nullptr),
      pRender_(nullptr),
      curTime_(0),
      curFrame_(0),
      isFirstTick_(true) {
}

Effect::~Effect() {
}

bool Effect::Initialize() {
  if (nullptr == pEffectInfo_) {
    return false;
  }
  pRender_ = CreateImageRenderFIFO();

  if (0 != pEffectInfo_->soundTag_) {
  soundChannel_ = SoundManager::Instance()->SoundPlay(pEffectInfo_->soundTag_);
  }

  IImage* pImage = ImgManager::GetIntance()->GetImg(pEffectInfo_->imageTag_);
  if (nullptr == pImage) {
    return false;
  }

  pRender_->SetImage(pImage);
  pRender_->SetLocalScale(pEffectInfo_->imageLocalScale_);
  pRender_->SetImageRenderType(ImageRenderType::Center);

  if (pEffectInfo_->isAlphaEffect_) {
    pRender_->SetAlpha(pEffectInfo_->alpha_);
  } else {
    pRender_->SetTransparentColor(pEffectInfo_->transColor_);
  }

  pRender_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Cyan});
  return true;
}

void Effect::BeginPlay() {
}

void Effect::Tick(unsigned long long curTick) {
  if (true == IsDestroy()) {
    return;
  }

  if (true == isFirstTick_) {
    unsigned int animIndex = pEffectInfo_->indices_[0];
    pRender_->SetImageIndex(animIndex);
    curTime_ = pEffectInfo_->intervals_[0];
    isFirstTick_ = false;
  }

  curTime_ -= curTick;
  if (curTime_ <= 0) {
    ++curFrame_;

    if (curFrame_ >= pEffectInfo_->indices_.size()) {
      if (true == pEffectInfo_->loop_) {
        isFirstTick_ = true;
        curFrame_ = 0;
      } else {
        SetDestroy();
      }
    } else {
      unsigned int animIndex = pEffectInfo_->indices_[curFrame_];
      pRender_->SetImageIndex(animIndex);
      IImage* pImage = pRender_->GetImage();
      if (nullptr == pImage) {
        return;
      }
      pRender_->SetScale(pImage->GetScale(animIndex));

      curTime_ = pEffectInfo_->intervals_[curFrame_];
    }
  }
}

EffectInfo* Effect::GetEffectInfo() const {
  return pEffectInfo_;
}

void Effect::SetEffectInfo(EffectInfo* effectInfo) {
  pEffectInfo_ = effectInfo;
}
