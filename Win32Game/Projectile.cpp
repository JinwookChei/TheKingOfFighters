#include "stdafx.h"
#include "Projectile.h"
#include "CollisionBox.h"

Projectile::Projectile()
    : owner_(nullptr),
      pRender_(nullptr),
      pCollisionBox_(nullptr),
      accumulRange_({0.0f, 0.0f}),
      curTime_(0),
      curFrame_(0),
      isFirstTick_(true) {
}

Projectile::~Projectile() {
}

void Projectile::BeginPlay() {
}

void Projectile::Tick(unsigned long long curTick) {
  if (true == IsDestroy()) {
    return;
  }

  if (true == isFirstTick_) {
    unsigned int imageIndex = projectileInfo_.indices_[0];
    pRender_->SetImageIndex(imageIndex);
    curTime_ = projectileInfo_.intervals_[0];
    isFirstTick_ = false;
  }

  curTime_ -= curTick;
  if (curTime_ <= 0) {
    ++curFrame_;

    if (curFrame_ >= projectileInfo_.indices_.size()) {
      if (true == projectileInfo_.loop_) {
        isFirstTick_ = true;
        curFrame_ = 0;
      } else {
        SetDestroy();
      }
    } else {
      unsigned int imageIndex = projectileInfo_.indices_[curFrame_];
      pRender_->SetImageIndex(imageIndex);
      IImage* pImage = pRender_->GetImage();
      if (nullptr == pImage) {
        return;
      }
      pRender_->SetScale(pImage->GetScale(imageIndex));
      curTime_ = projectileInfo_.intervals_[curFrame_];
    }
  }

  SetPosition(GetPosition() + projectileInfo_.velocity_);
  accumulRange_ += projectileInfo_.velocity_;

  if (accumulRange_.X > projectileInfo_.range_.X)
  {
    SetDestroy();
  }

  CollisionUpdate();
}

bool Projectile::Initialize() {
  SetPosition(owner_->GetPosition() + projectileInfo_.position_);

  pRender_ = CreateImageRenderFIFO();
  IImage* pImage = ImgManager::GetIntance()->GetImg(projectileInfo_.imageIndex_);
  if (nullptr == pImage) {
    return false;
  }
  pRender_->SetImage(pImage);
  pRender_->SetTransparentColor(projectileInfo_.transColor_);
  pRender_->SetLocalScale({4.5f, 4.5f});
  pRender_->SetImageRenderType(ImageRenderType::Center);

  pCollisionBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_AttackBox);
  if (nullptr == pCollisionBox_) {
    return false;
  }

  pCollisionBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Red});

  return true;
}

Actor* Projectile::GetOwner() const {
  return owner_;
}

void Projectile::SetOwner(Actor* owner) {
  owner_ = owner;
}

ProjectileInfo Projectile::GetProjectileInfo() const {
  return projectileInfo_;
}

void Projectile::SetProjectileInfo(const ProjectileInfo& projectileInfo) {
  projectileInfo_ = projectileInfo;
}

void Projectile::CollisionUpdate() {
  if (nullptr == pRender_ || nullptr == pCollisionBox_) {
    return;
  }

  unsigned int imageIndex = pRender_->GetImageIndex();
  IImage* pImage = pRender_->GetImage();
  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  CollisionInfo* pCollisionInfo;

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_AttackBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pCollisionBox_->SetActive(true);
      pCollisionBox_->SetPosition(pCollisionInfo->position_);
      pCollisionBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pCollisionBox_->SetActive(false);
    }
  }
}