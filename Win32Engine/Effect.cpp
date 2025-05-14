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
  pRender_ = CreateImageRenderFIFO();

  IImage* pImage = ImgManager::GetIntance()->GetImg(pEffectInfo_->imageIndex_);
  if (nullptr == pImage) {
    return false;
  }

  pRender_->SetImage(pImage);
  pRender_->SetTransparentColor(pEffectInfo_->transColor_);
  pRender_->SetLocalScale({4.0f, 4.0f});
  pRender_->SetImageRenderType(ImageRenderType::Center);
  // pRender_->CreateAnimation(1, pEffectInfo_->imageIndex_, pEffectInfo_->indices_, pEffectInfo_->intervals_, pEffectInfo_->loop_);
  // pRender_->ChangeAnimation(1);

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
    unsigned int imageIndex = pEffectInfo_->indices_[0];
    pRender_->SetImageIndex(imageIndex);
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
      unsigned int imageIndex = pEffectInfo_->indices_[curFrame_];
      pRender_->SetImageIndex(imageIndex);
      IImage* pImage = pRender_->GetImage();
      if (nullptr == pImage) {
        return;
      }
      pRender_->SetScale(pImage->GetScale(imageIndex));

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

// LINK_ITEM* Effect::GetEffectLink() const {
//   return effectLink_;
// }
