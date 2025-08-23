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
  KOFPlayer* pKOFPlayerOwner = dynamic_cast<KOFPlayer*>(pOwner_);
  if (nullptr == pKOFPlayerOwner) {
    return false;
  }

  //  RENDERER
  pRender_ = CreateImageRenderFIFO();
  pRender_->SetImageRenderType(ImageRenderType::Bottom);
  pRender_->SetLocalScale({4.2f, 4.2f});
  pRender_->SetAlpha(1.0f);

  attackInfo_.attackType_ = ATTYPE_Airborne;
  attackInfo_.damage_ = {10.0f};
  attackInfo_.effectType_ = EFTYPE_Hit_2;
  attackInfo_.elementType_ = ELMTTYPE_BlueFlame;
  attackInfo_.freezeTime_ = 140.0f;
  attackInfo_.isMultiHit_ = true;
  attackInfo_.knockBackForce_ = {2.0f, -9.0f};
  spawnPosition_ = {400.0f, 0.0f};
  isDestroyOnCollision_ = false;

  if (true == pKOFPlayerOwner->PlayerOnLeft()) {
    pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_NONE), 406, 423, 20, false, 406);
  } else {
    pRender_->CreateAnimation(1, (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 406, 423, 20, false, 406);
  }

  pRender_->ChangeAnimation(1);

  if (false == Projectile::Initialize()) {
    return false;
  }

  return true;
}
