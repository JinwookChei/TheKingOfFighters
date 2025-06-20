#include "stdafx.h"
#include "BlackBoard.h"

BlackBoard::BlackBoard()
    : pRender_(nullptr),
      fadeDuration_(0.0f),
      fadeTimer_(0.0f),
      alpha_(0.0f),
      onFadeIn_(false),
      onFadeOut_(false) {
}

BlackBoard::~BlackBoard() {
}

void BlackBoard::BeginPlay() {
  pRender_ = CreateImageRenderFIFO();
  pRender_->SetImage(ImgManager::GetIntance()->GetImg(IMGKEY_BlackBoardImage));
  pRender_->SetImageRenderType(ImageRenderType::LeftTop);
  pRender_->SetLocalScale({2.4f, 3.7f});
  pRender_->SetAlpha(0.0f);
  SetActive(false);
}

void BlackBoard::Tick(unsigned long long curTick) {
  if (IsActive() == true) {
    fadeTimer_ += curTick;
    float t = fadeTimer_ / fadeDuration_;

    if (onFadeIn_) {
      alpha_ -= t;
      if (alpha_ <= 0.0f) {
        onFadeIn_ = false;
        SetActive(false);
      }
    }

    if (onFadeOut_) {
      alpha_ += t;
    }

    alpha_ = (alpha_ < 0.0f) ? 0.0f : (alpha_ > 1.0f) ? 1.0f : alpha_;
    pRender_->SetAlpha(alpha_);
  }
}

void BlackBoard::FadeIn(float fadeDuration) {
  if (IsActive() == false) {
    return;
  }
  fadeDuration_ = fadeDuration;
  fadeTimer_ = 0.0f;
  onFadeOut_ = false;
  onFadeIn_ = true;
}

void BlackBoard::FadeOut(float fadeDuration) {
  if (onFadeOut_ == true) {
    alpha_ = 0.0f;
  }
  SetActive(true);
  fadeDuration_ = fadeDuration;
  fadeTimer_ = 0.0f;
  onFadeOut_ = true;
  onFadeIn_ = false;
}
