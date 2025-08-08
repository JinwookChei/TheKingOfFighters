#include "stdafx.h"
#include "ScreenMask.h"

ScreenMask::ScreenMask()
    : pRender_(nullptr),
      fadeDuration_(0.0f),
      fadeTimer_(0.0f),
      alpha_(0.0f),
      onFadeIn_(false),
      onFadeOut_(false),
      onFadeInOut_(false) {
}

ScreenMask::~ScreenMask() {
}

void ScreenMask::BeginPlay() {
  pRender_ = CreateImageRenderFIFO();
  pRender_->SetImage(ImgManager::GetIntance()->GetImg(IMGTYPE_BlackBoardImage));
  pRender_->SetImageRenderType(ImageRenderType::LeftTop);
  pRender_->SetLocalScale({2.4f, 3.7f});
  pRender_->SetAlpha(0.0f);
  SetActive(false);
}

void ScreenMask::Tick(unsigned long long curTick) {
  fadeTimer_ += curTick;

  float addTemp = curTick / (float)fadeDuration_;

  if (onFadeIn_) {
    alpha_ -= addTemp;
    if (fadeTimer_ >= fadeDuration_) {
      onFadeIn_ = false;
      SetActive(false);
    }
  }

  if (onFadeOut_) {
    alpha_ += addTemp;
    if (fadeTimer_ >= fadeDuration_) {
      if (onFadeInOut_) {
        FadeIn(fadeDuration_);
        onFadeInOut_ = false;
      }
    } 
  }

  alpha_ = (alpha_ < 0.0f) ? 0.0f : (alpha_ > 1.0f) ? 1.0f
                                                    : alpha_;
  pRender_->SetAlpha(alpha_);
}

void ScreenMask::FadeIn(unsigned long long fadeDuration) {
  if (IsActive() == false) {
    return;
  }
  fadeDuration_ = fadeDuration;
  fadeTimer_ = 0.0f;
  onFadeOut_ = false;
  onFadeIn_ = true;
}

void ScreenMask::FadeOut(IMAGE_TYPE image, unsigned long long fadeDuration) {
  if (onFadeOut_ == true) {
    alpha_ = 0.0f;
  }
  SetActive(true);
  pRender_->SetImage(ImgManager::GetIntance()->GetImg(image));
  fadeDuration_ = fadeDuration;
  fadeTimer_ = 0.0f;
  onFadeOut_ = true;
  onFadeIn_ = false;
}

void ScreenMask::FadeInOut(IMAGE_TYPE image, unsigned long long fadeInOutDuration) {
  FadeOut(image, fadeInOutDuration);
  onFadeInOut_ = true;
}

void ScreenMask::InitAlpha(float alpha) {
  alpha_ = alpha;
}

float ScreenMask::GetCurrentAlpha() const {
  return alpha_;
}
