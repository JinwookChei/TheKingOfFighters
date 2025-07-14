#include "stdafx.h"
#include "KOFPlayer.h"
#include "Projectile.h"
#include "Ura306Shiki.h"

Ura306Shiki::Ura306Shiki() {
}

Ura306Shiki::~Ura306Shiki() {
}

void Ura306Shiki::Tick(unsigned long long deltaTick) {
  if (true == pRender_->IsAnimationEnd()) {
    Destroy();
  }

  UpdateCollisionBoundScale();

  UpdateAttack();
}

bool Ura306Shiki::Initialize() {
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

  if (true == pKOFPlayerOwner->PlayerOnLeft()) {
    pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_NONE), 406, 423, 20, false, 406);
  } else {
    pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 406, 423, 20, false, 406);
  }

  pRender_->ChangeAnimation(1);

  return true;
}
