#include "stdafx.h"
#include "KOFPlayer.h"
#include "Projectile.h"
#include "YamiBarai.h"

YamiBarai::YamiBarai()
    : pRender2_(nullptr),
      accumulRange_(0.0f),
      velocity_(0.0f),
      range_(0.0f) {
}

YamiBarai::~YamiBarai() {
}

void YamiBarai::Tick(unsigned long long deltaTick) {
  SetPosition({GetPosition().X + velocity_, GetPosition().Y});

  if (range_ > 0) {
    accumulRange_ += velocity_;
    if (accumulRange_ > range_) {
      Destroy();
    }
  } else {
    accumulRange_ += velocity_;
    if (accumulRange_ < range_) {
      Destroy();
    }
  }

  UpdateCollisionBoundScale();

  UpdateAttack();
}

bool YamiBarai::Initialize() {
  if (false == Projectile::Initialize()) {
    return false;
  }

  KOFPlayer* pKOFPlayerOwner = dynamic_cast<KOFPlayer*>(pOwner_);
  if (nullptr == pKOFPlayerOwner) {
    return false;
  }

  //  RENDERER
  pRender_ = CreateImageRenderFIFO();
  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->SetLocalScale({4.2f, 4.2f});
  pRender_->SetAlpha(1.0f);
  pRender2_ = CreateImageRenderFIFO();
  pRender2_->SetImageRenderType(ImageRenderType::Center);
  pRender2_->SetLocalScale({4.2f, 4.2f});
  pRender2_->SetAlpha(1.0f);

  if (true == pKOFPlayerOwner->PlayerOnLeft()) {
    pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_NONE), 239, 243, 10, true, 239);
    pRender2_->CreateAnimation(2, (IMGTYPE_IoriImage | IMGMOD_NONE), 245, 254, 10, true, 245);
    velocity_ = 25.0f;
    range_ = 1500.0f;
  } else {
    pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 239, 244, 10, true, 239);
    pRender2_->CreateAnimation(2, (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 245, 254, 10, true, 245);
    velocity_ = -25.0f;
    range_ = -1500.0f;
  }
  pRender_->ChangeAnimation(1);
  pRender2_->ChangeAnimation(2);
  

  return true;
}