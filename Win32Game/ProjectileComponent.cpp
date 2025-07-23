#include "stdafx.h"
#include "Projectile.h"
#include "ProjectileComponent.h"
#include "AttackTable.h"
#include "YamiBarai.h"
#include "HyakushikiOniyaki.h"
#include "Ura306Shiki.h"

ProjectileComponent::ProjectileComponent()
    : level_(nullptr),
      activeProjectilesHead_ (nullptr),
      activeProjectilesTail_(nullptr) {
}

ProjectileComponent::~ProjectileComponent() {
}

void ProjectileComponent::BeginPlay() {
}

bool ProjectileComponent::Initialize(Level* level) {
  if (nullptr == level) {
    return false;
  }
  level_ = level;

  return true;
}

void ProjectileComponent::FireProjectile(unsigned long long projectileTag) {
  Projectile* newProjectile = nullptr;
  switch (projectileTag)
  {
    case IORI_PROJECTILE_YamiBarai:
      newProjectile = level_->SpawnActor<YamiBarai>(ActorGroupEngineType_Projectile);
      break;
    case IORI_PROJECTILE_HyakushikiOniyaki_Low:
      newProjectile = level_->SpawnActor<HyakushikiOniyaki>(ActorGroupEngineType_Projectile);
      newProjectile->SetMiscValue(0);
      break;
    case IORI_PROJECTILE_HyakushikiOniyaki_High:
      newProjectile = level_->SpawnActor<HyakushikiOniyaki>(ActorGroupEngineType_Projectile);
      newProjectile->SetMiscValue(1);
      break;
    case IORI_PROJECTILE_Ura306Shiki:
      newProjectile = level_->SpawnActor<Ura306Shiki>(ActorGroupEngineType_Projectile);
      break;
    default:
      return;
      break;
  }
  
  if (nullptr == newProjectile) {
    return;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }
  newProjectile->SetOwner(owner);
  newProjectile->SetOwnerProjectileComponent(this);
  
  LinkToLinkedListFIFO(&activeProjectilesHead_, &activeProjectilesTail_, newProjectile->GetProjectileLink());

  if (false == newProjectile->Initialize()) {
    return;
  }
}

int ProjectileComponent::GetActiveProjectilesCount() {
  return CountLinkedList(activeProjectilesHead_);
}

void ProjectileComponent::UnLinkDestroyedProjectile(LINK_ITEM* linkItem) {
  UnLinkFromLinkedList(&activeProjectilesHead_, &activeProjectilesTail_, linkItem);
}