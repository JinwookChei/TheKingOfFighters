#include "stdafx.h"
#include "Projectile.h"
#include "CollisionBox.h"
#include "KOFPlayer.h"
#include "KOFLevel.h"
#include "Attacktable.h"
#include "ProjectileComponent.h"

Projectile::Projectile()
    : pOwner_(nullptr),
      pOwnerProjectileComponent_(nullptr),
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
        Destroy();
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

  if (accumulRange_.X > projectileInfo_.range_.X) {
    Destroy();
  }

  UpdateCollisionBoundScale();

  UpdateAttack();
}

bool Projectile::Initialize() {
  SetPosition(pOwner_->GetPosition() + projectileInfo_.position_);

  pRender_ = CreateImageRenderFIFO();
  IImage* pImage = ImgManager::GetIntance()->GetImg(projectileInfo_.imageIndex_);
  if (nullptr == pImage) {
    return false;
  }
  pRender_->SetImage(pImage);
  // pRender_->SetTransparentColor(projectileInfo_.transColor_);
  pRender_->SetAlpha(1.0f);
  pRender_->SetLocalScale({4.2f, 4.2f});
  pRender_->SetImageRenderType(ImageRenderType::Center);

  pCollisionBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_AttackBox);
  if (nullptr == pCollisionBox_) {
    return false;
  }

  pCollisionBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Red});

  return true;
}

Actor* Projectile::GetOwner() const {
  return pOwner_;
}

void Projectile::SetOwner(Actor* owner) {
  pOwner_ = owner;
}

ProjectileComponent* Projectile::GetOwnerProjectileComponent() const {
  return pOwnerProjectileComponent_;
}

void Projectile::SetOwnerProjectileComponent(ProjectileComponent* ownerProjectileComponent) {
  pOwnerProjectileComponent_ = ownerProjectileComponent;
}

ProjectileInfo Projectile::GetProjectileInfo() const {
  return projectileInfo_;
}

void Projectile::SetProjectileInfo(const ProjectileInfo& projectileInfo) {
  projectileInfo_ = projectileInfo;
}

LINK_ITEM* Projectile::GetProjectileLink() {
  return &projectileLink_;
}

void Projectile::UpdateCollisionBoundScale() {
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

void Projectile::UpdateAttack() {
  CollisionComponent* pTargetCollision = nullptr;
  if (CheckAttackCollision(&pTargetCollision)) {
    if (nullptr != pTargetCollision) {
      Actor* pTargetOwner = pTargetCollision->GetOwner();
      if (nullptr == pTargetOwner) {
        return;
      }
      KOFPlayer* pTargetPlayer = dynamic_cast<KOFPlayer*>(pTargetOwner);
      if (nullptr == pTargetPlayer) {
        return;
      }

      if (nullptr == projectileInfo_.pAttackInfo_) {
        return;
      }

      pTargetPlayer->HitEvent(projectileInfo_.pAttackInfo_);

      Level* pLevel = GetLevel();
      if (nullptr == pLevel) {
        return;
      }
      KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
      if (nullptr == pKOFLevel) {
        return;
      }
      pKOFLevel->FreezeActors({this, pTargetPlayer}, false, 80);

      // Calculate Effect Position.
      Vector collisionSectionLeftTop = {
          pCollisionBox_->GetCollisionInfo().Left() > pTargetCollision->GetCollisionInfo().Left() ? pCollisionBox_->GetCollisionInfo().Left() : pTargetCollision->GetCollisionInfo().Left(),
          pCollisionBox_->GetCollisionInfo().Top() > pTargetCollision->GetCollisionInfo().Top() ? pCollisionBox_->GetCollisionInfo().Top() : pTargetCollision->GetCollisionInfo().Top(),
      };

      Vector collisionSectionRightBottom = {
          pCollisionBox_->GetCollisionInfo().Right() < pTargetCollision->GetCollisionInfo().Right() ? pCollisionBox_->GetCollisionInfo().Right() : pTargetCollision->GetCollisionInfo().Right(),
          pCollisionBox_->GetCollisionInfo().Bottom() < pTargetCollision->GetCollisionInfo().Bottom() ? pCollisionBox_->GetCollisionInfo().Bottom() : pTargetCollision->GetCollisionInfo().Bottom(),
      };

      Vector effectPosition = {
          (collisionSectionRightBottom.X + collisionSectionLeftTop.X) / 2,
          (collisionSectionRightBottom.Y + collisionSectionLeftTop.Y) / 2};

      // 이펙트도 여기서 스폰.
      EffectManager::Instance()->SpawnEffect(GetLevel(), projectileInfo_.pAttackInfo_->effectKey_, effectPosition);

      if (projectileInfo_.isDestroyOnCollision_ == true) {
        Destroy();
      }
    }
  }
}

bool Projectile::CheckAttackCollision(CollisionComponent** outTargetCollision) {
  if (true == pCollisionBox_->HasHit()) {
    return false;
  }
  CollisionComponent* pTargetCollision_Top = nullptr;
  if (true == pCollisionBox_->Collision(
                  {
                      .targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop,
                      .targetCollisionType = CollisionType::CollisionType_Rect,
                      .myCollisionType = CollisionType::CollisionType_Rect,
                  },
                  &pTargetCollision_Top)) {
    *outTargetCollision = pTargetCollision_Top;
    pTargetCollision_Top->MarkAsHit();
    pCollisionBox_->MarkAsHit();
    return true;
  }

  CollisionComponent* pTargetCollision_Bottom = nullptr;
  if (true == pCollisionBox_->Collision(
                  {
                      .targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_HitBoxBottom,
                      .targetCollisionType = CollisionType::CollisionType_Rect,
                      .myCollisionType = CollisionType::CollisionType_Rect,
                  },
                  &pTargetCollision_Bottom)) {
    *outTargetCollision = pTargetCollision_Bottom;
    pTargetCollision_Bottom->MarkAsHit();
    pCollisionBox_->MarkAsHit();
    return true;
  }

  *outTargetCollision = nullptr;
  return false;
}

void Projectile::Destroy(){
  pOwnerProjectileComponent_->UnLinkDestroyedProjectile(&projectileLink_);
  SetDestroy();

}