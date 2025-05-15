#include "stdafx.h"
#include "KOFPlayer.h"
#include "GhostEffect.h"

GhostEffect::GhostEffect()
    : owner_(nullptr),
      pOwnerRenderer_(nullptr),
      ppGhostRenderers_(nullptr),
      ghostNum_(0),
      isRenderOn_(false),
      renderOnCount_(0),
      updateTime_(0),
      accumulTime_(0) {
}

GhostEffect::~GhostEffect() {
  if (nullptr != ppGhostRenderers_) {
    delete[] ppGhostRenderers_;
    ppGhostRenderers_ = nullptr;
  }
}

void GhostEffect::BeginPlay() {
  isRenderOn_ = false;
  SetActive(false);
}

void GhostEffect::Tick(unsigned long long deltaTick) {
  if (nullptr == owner_ || nullptr == pOwnerRenderer_) {
    return;
  }

  accumulTime_ += deltaTick;

  if (accumulTime_ >= updateTime_) {
    GhostInfo spriteInfo;
    spriteInfo.image_ = pOwnerRenderer_->GetImage();
    spriteInfo.imageIndex_ = pOwnerRenderer_->GetImageIndex();
    spriteInfo.worldPosition_ = owner_->GetPosition();

    ghostBuffer_.Update(spriteInfo);
    accumulTime_ = 0;

    if (isRenderOn_) {
      if (renderOnCount_ < ghostNum_) {
        ppGhostRenderers_[ghostNum_ - renderOnCount_ - 1]->SetActive(true);
        ++renderOnCount_;
      }
    } else {
      if (renderOnCount_ > 0 && renderOnCount_ <= ghostNum_) {
        --renderOnCount_;
        ppGhostRenderers_[renderOnCount_]->SetActive(false);
      }

      if (renderOnCount_ == 0) {
        SetActive(false);
      }
    }
  }

  for (int i = 0; i < ghostNum_; ++i) {
    GhostInfo* pGhostInfo;
    if (false == ghostBuffer_.Get(i, &pGhostInfo)) {
      return;
    }
    ppGhostRenderers_[i]->SetImage(pGhostInfo->image_, pGhostInfo->imageIndex_);
    ppGhostRenderers_[i]->SetPosition(pGhostInfo->worldPosition_ - owner_->GetPosition());
  }
}

bool GhostEffect::Initialize(ImageRenderer* ownerRenderer, int ghostNum, unsigned long long updateTime) {
  owner_ = GetOwner();
  if (nullptr == owner_ || ghostNum < 0) {
    return false;
  }

  if (nullptr == ownerRenderer) {
    return false;
  }

  pOwnerRenderer_ = ownerRenderer;
  ghostNum_ = ghostNum;
  updateTime_ = updateTime;

  if (false == ghostBuffer_.Initialize(ghostNum_)) {
    return false;
  }

  ppGhostRenderers_ = new ImageRenderer*[ghostNum_];

  for (int i = 0; i < ghostNum_; ++i) {
    ppGhostRenderers_[i] = owner_->CreateImageRenderLIFO();

    if (nullptr == ppGhostRenderers_[i]) {
      return false;
    }
    ppGhostRenderers_[i]->SetImageRenderType(ownerRenderer->GetImageRenderType());
    ppGhostRenderers_[i]->SetLocalScale(ownerRenderer->GetLocalScale());
  };
  return true;
}

void GhostEffect::SetTransparentColor(const Color8Bit& transColor) {
  for (int i = 0; i < ghostNum_; ++i) {
    ppGhostRenderers_[i]->SetTransparentColor(transColor);
  };
}

void GhostEffect::On() {
  renderOnCount_ = 0;
  isRenderOn_ = true;
  SetActive(true);
}

void GhostEffect::Off() {
  isRenderOn_ = false;
}
