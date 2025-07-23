#include "stdafx.h"
#include "Projectile.h"
#include "KOFPlayer.h"
#include "HyakushikiOniyaki.h"

HyakushikiOniyaki::HyakushikiOniyaki()
    : velocityY_(0.0f) {
}

HyakushikiOniyaki::~HyakushikiOniyaki() {
}

void HyakushikiOniyaki::Tick(unsigned long long deltaTick) {
  if (true == pRender_->IsAnimationEnd()) {
    Destroy();
  }

  SetPosition({GetPosition().X, GetPosition().Y + velocityY_ * deltaTick});

  UpdateCollisionBoundScale();

  UpdateAttack();
}

bool HyakushikiOniyaki::Initialize() {
  KOFPlayer* pKOFPlayerOwner = dynamic_cast<KOFPlayer*>(pOwner_);
  if (nullptr == pKOFPlayerOwner) {
    return false;
  }

  //  RENDERER
  pRender_ = CreateImageRenderFIFO();
  pRender_->SetImageRenderType(ImageRenderType::Bottom);
  pRender_->SetLocalScale({4.2f, 4.2f});
  pRender_->SetAlpha(1.0f);

  attackInfo_.attackType_ = ATTYPE_LowAttack;
  attackInfo_.damage_ = {10.0f};
  attackInfo_.effectType_ = EFTYPE_Hit_2;
  attackInfo_.elementType_ = ELMTTYPE_BlueFlame;
  attackInfo_.freezeTime_ = 140.0f;
  attackInfo_.isMultiHit_ = true;
  attackInfo_.knockBackForce_ = {1.5f, 2.0f};
  isDestroyOnCollision_ = false;

  if (0 == miscValue_) {
    spawnPosition_ = {50.0f, -30.0f};
    if (true == pKOFPlayerOwner->PlayerOnLeft()) {
      pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_NONE), 292, 301, 20, false, 292);
    } else {
      pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 292, 301, 20, false, 292);
    }
  } else {
    spawnPosition_ = {-80.0f, -200.0f};
    if (true == pKOFPlayerOwner->PlayerOnLeft()) {
      pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_NONE), 302, 311, 20, false, 302);
    } else {
      pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 302, 311, 20, false, 302);
    }
  }

  pRender_->ChangeAnimation(1);
  velocityY_ = -1.5f;

  if (false == Projectile::Initialize()) {
    return false;
  }

  return true;
}