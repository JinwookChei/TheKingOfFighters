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
  float curVelocity = velocity_ * deltaTick;
  SetPosition({GetPosition().X + curVelocity, GetPosition().Y});

  if (range_ > 0) {
    accumulRange_ += curVelocity;
    if (accumulRange_ > range_) {
      Destroy();
    }
  } else {
    accumulRange_ += curVelocity;
    if (accumulRange_ < range_) {
      Destroy();
    }
  }

  UpdateCollisionBoundScale();

  UpdateAttack();
}

bool YamiBarai::Initialize() {
  KOFPlayer* pKOFPlayerOwner = dynamic_cast<KOFPlayer*>(pOwner_);
  if (nullptr == pKOFPlayerOwner) {
    return false;
  }



  //  RENDERER
  pRender_ = CreateImageRenderFIFO();
  pRender_->SetImageRenderType(ImageRenderType::Bottom);
  pRender_->SetLocalScale({4.2f, 4.2f});
  pRender_->SetAlpha(1.0f);
  pRender2_ = CreateImageRenderFIFO();
  pRender2_->SetImageRenderType(ImageRenderType::Bottom);
  pRender2_->SetLocalScale({4.2f, 4.2f});
  pRender2_->SetAlpha(1.0f);

  attackInfo_.attackType_ = ATTYPE_LowAttack;
  attackInfo_.damage_ = {10.0f};
  attackInfo_.effectType_ = EFTYPE_Hit_2;
  attackInfo_.elementType_ = ELMTTYPE_BlueFlame;
  attackInfo_.freezeTime_ = 140.0f;
  attackInfo_.isMultiHit_ = false;
  attackInfo_.knockBackForce_ = {1.5f, 0.0f};
  spawnPosition_ = {180.0f, 50.0f};
  isDestroyOnCollision_ = true;

  if (true == pKOFPlayerOwner->PlayerOnLeft()) {
    pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_NONE), 239, 243, 10, true, 239);
    pRender2_->CreateAnimation(2, (IMGTYPE_IoriImage | IMGMOD_NONE), 245, 254, 10, true, 245);
    velocity_ = 2.0f;
    range_ = 1500.0f;
  } else {
    pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 239, 244, 10, true, 239);
    pRender2_->CreateAnimation(2, (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 245, 254, 10, true, 245);
    velocity_ = -2.0f;
    range_ = -1500.0f;
  }
  pRender_->ChangeAnimation(1);
  pRender2_->ChangeAnimation(2);

  if (false == Projectile::Initialize()) {
    return false;
  }

  return true;
}