#include "stdafx.h"
#include "BackGroundMask.h"

BackGroundMask::BackGroundMask()
    : pRender_(nullptr),
      fadeDuration_(0.0f),
      fadeTimer_(0.0f),
      alpha_(0.0f),
      onFadeIn_(false),
      onFadeOut_(false),
      onFadeInOut_(false) {
}

BackGroundMask::~BackGroundMask() {
}

void BackGroundMask::BeginPlay() {
  pRender_ = CreateImageRenderFIFO();
  pRender_->SetImage(ImgManager::GetIntance()->GetImg(IMGKEY_BlackBoardImage));
  pRender_->SetImageRenderType(ImageRenderType::LeftTop);
  pRender_->SetLocalScale({2.4f, 3.7f});
  pRender_->SetAlpha(0.0f);
  SetActive(false);
}

void BackGroundMask::Tick(unsigned long long curTick) {
  fadeTimer_ += curTick;

  float addTemp = curTick / fadeDuration_;

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

void BackGroundMask::FadeIn(float fadeDuration) {
  if (IsActive() == false) {
    return;
  }
  fadeDuration_ = fadeDuration;
  fadeTimer_ = 0.0f;
  onFadeOut_ = false;
  onFadeIn_ = true;
}

void BackGroundMask::FadeOut(IMAGE_KEY image, float fadeDuration) {
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

void BackGroundMask::FadeInOut(IMAGE_KEY image, float fadeInOutDuration) {
  FadeOut(image, fadeInOutDuration);
  onFadeInOut_ = true;
}
