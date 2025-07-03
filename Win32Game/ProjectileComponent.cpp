#include "stdafx.h"
#include "Projectile.h"
#include "ProjectileComponent.h"
#include "AttackTable.h"
#include "YamiBarai.h"
#include "HyakushikiOniyaki.h"

ProjectileComponent::ProjectileComponent()
    : level_(nullptr),
      activeProjectilesHead_ (nullptr),
      activeProjectilesTail_(nullptr) {
}

ProjectileComponent::~ProjectileComponent() {
  for (HashTableIterator iter = projectileTable_.begin(); iter != projectileTable_.end();) {
    ProjectileInfo* pDel = (ProjectileInfo*)*iter;

    iter = projectileTable_.erase(iter);

    delete pDel;
  }

  projectileTable_.Cleanup();
}

void ProjectileComponent::BeginPlay() {
}

bool ProjectileComponent::Initialize(Level* level) {
  if (nullptr == level) {
    return false;
  }
  level_ = level;

  return projectileTable_.Initialize(8, 8);
}

void ProjectileComponent::FireProjectile(unsigned long long projectileTag) {
  ProjectileInfo* pInfo;
  if (0 == projectileTable_.Select((void**)&pInfo, 1, &projectileTag, 8)) {
    return;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  Projectile* newProjectile = nullptr;
  switch (pInfo->projectileTag_)
  {
    case IORI_PROJECTILE_YamiBarai:
      newProjectile = level_->SpawnActor<YamiBarai>(ActorGroupEngineType_Effect);
      break;
    case IORI_PROJECTILE_HyakushikiOniyaki_Low:
      newProjectile = level_->SpawnActor<HyakushikiOniyaki>(ActorGroupEngineType_Effect);
      break;
    case IORI_PROJECTILE_HyakushikiOniyaki_High:
      newProjectile = level_->SpawnActor<HyakushikiOniyaki>(ActorGroupEngineType_Effect);
      break;
    default:
      break;
  }
  
  if (nullptr == newProjectile) {
    return;
  }

  newProjectile->SetOwner(owner);
  newProjectile->SetOwnerProjectileComponent(this);
  newProjectile->SetProjectileInfo(*pInfo);
  
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

bool ProjectileComponent::RegistProjectileInfo(unsigned long long projectileTag, AttackInfo* pAttackInfo, const Vector& spawnPosition, bool isDestroyOnCollision, int miscValue/* = 0*/) {
  ProjectileInfo* pFind;
  if (0 != projectileTable_.Select((void**)&pFind, 1, &projectileTag, 8)) {
    return false;
  }

  ProjectileInfo* pInfo = new ProjectileInfo;
  pInfo->projectileTag_ = projectileTag;
  pInfo->pAttackInfo_ = pAttackInfo;
  pInfo->spawnPosition_ = spawnPosition;
  pInfo->isDestroyOnCollision_ = isDestroyOnCollision;
  pInfo->miscValue_ = miscValue;
  pInfo->searchHandle_ = projectileTable_.Insert(pInfo, &pInfo->projectileTag_, 8);

  return nullptr != pInfo->searchHandle_;
}

