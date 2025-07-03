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
      projectileLink_({nullptr, nullptr, this}) {
}

Projectile::~Projectile() {
}

void Projectile::BeginPlay() {
}

void Projectile::Tick(unsigned long long curTick) {

}

bool Projectile::Initialize() {
  KOFPlayer* pKOFPlayerOwner = dynamic_cast<KOFPlayer*>(pOwner_);
  if (nullptr == pKOFPlayerOwner) {
    return false;
  }

  // CAMERA SETTING
  SetUseCameraposition(true);

  // POSITION
  if (true == pKOFPlayerOwner->PlayerOnLeft()) {
    SetPosition(pKOFPlayerOwner->GetPosition() + projectileInfo_.spawnPosition_);
  } else {
    SetPosition(pKOFPlayerOwner->GetPosition() + Vector{-projectileInfo_.spawnPosition_.X, projectileInfo_.spawnPosition_.Y});
  }

  // COLLISION
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
      pKOFLevel->FreezeActors({pOwner_, pTargetPlayer}, false, 80);

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
      EffectManager::Instance()->SpawnEffect(GetLevel(), projectileInfo_.pAttackInfo_->effectType_, effectPosition);

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

void Projectile::Destroy() {
  if (false == IsDestroy()) {
    pOwnerProjectileComponent_->UnLinkDestroyedProjectile(&projectileLink_);
    SetDestroy();
  }
}