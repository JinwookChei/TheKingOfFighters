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

  SetPosition({GetPosition().X, GetPosition().Y + velocityY_});

  UpdateCollisionBoundScale();

  UpdateAttack();
}


bool HyakushikiOniyaki::Initialize() {
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

  if (0 == projectileInfo_.miscValue_) {
    if (true == pKOFPlayerOwner->PlayerOnLeft()) {
      pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_NONE), 292, 301, 20, false, 292);
    } else {
      pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 292, 301, 20, false, 292);
    }
  } else {
    if (true == pKOFPlayerOwner->PlayerOnLeft()) {
      pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_NONE), 302, 311, 20, false, 302);
    } else {
      pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 302, 311, 20, false, 302);
    }
  }

  pRender_->ChangeAnimation(1);

  velocityY_ = -7.0f;

  return true;
}