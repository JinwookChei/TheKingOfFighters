#include "stdafx.h"
#include "Effect.h"
#include "CollisionComponent.h"
#include "ImageRenderer.h"

Effect::Effect()
    : pEffectInfo_(nullptr),
      pRender_(nullptr) {
}

Effect::~Effect() {
}

bool Effect::Initialize() {
  pRender_ = CreateImageRender();

  IImage* pImage = ImgManager::GetIntance()->GetImg(pEffectInfo_->imageIndex_);
  if (nullptr == pImage) {
    return false;
  }

  pRender_->SetImage(pImage);
  pRender_->SetTransparentColor(pEffectInfo_->transColor_);
  pRender_->SetLocalScale({4.0f, 4.0f});
  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->CreateAnimation(1, pEffectInfo_->imageIndex_, pEffectInfo_->indices_, pEffectInfo_->intervals_);
  
  pRender_->ChangeAnimation(1);

  return true;
}

void Effect::BeginPlay() {
}

void Effect::Tick(unsigned long long curTick) {
}

EffectInfo* Effect::GetEffectInfo() const {
  return pEffectInfo_;
}

void Effect::SetEffectInfo(EffectInfo* effectInfo) {
  pEffectInfo_ = effectInfo;
}

LINK_ITEM* Effect::GetEffectLink() const {
  return effectLink_;
}
