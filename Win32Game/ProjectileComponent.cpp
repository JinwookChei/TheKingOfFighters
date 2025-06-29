#include "stdafx.h"
#include "Projectile.h"
#include "ProjectileComponent.h"

ProjectileComponent::ProjectileComponent()
    : level_(nullptr) {
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

void ProjectileComponent::FireProjectile(unsigned long long projectileTag, bool isFacingRight) {
  ProjectileInfo* pInfo;
  if (0 == projectileTable_.Select((void**)&pInfo, 1, &projectileTag, 8)) {
    return;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  Projectile* newProjectile = level_->SpawnActor<Projectile>(ActorGroupEngineType_Effect);
  if (true == isFacingRight) {
  newProjectile->SetOwner(owner);
  newProjectile->SetProjectileInfo(*pInfo);
  newProjectile->SetUseCameraposition(true);
  }
  else {
    ProjectileInfo copyInfo = *pInfo;
    copyInfo.position_ = Vector({-pInfo->position_.X, pInfo->position_.Y});
    copyInfo.velocity_ = Vector({-pInfo->velocity_.X, pInfo->velocity_.Y});
    copyInfo.imageIndex_ = (pInfo->imageIndex_ | IMGMOD_FLIPPED);

    newProjectile->SetOwner(owner);
    newProjectile->SetProjectileInfo(copyInfo);
    newProjectile->SetUseCameraposition(true);
  }

  if (false == newProjectile->Initialize()) {
    return;
  }
}

bool ProjectileComponent::RegistProjectileInfo(
    unsigned long long projectileTag,
    unsigned long long imageIndex,
    unsigned int startIndex,
    unsigned int endIndex,
    unsigned long long interval,
    bool loop,
    const Color8Bit transColor,
    const Vector& velocity,
    const Vector& position,
    const Vector& range) {
  std::vector<unsigned int> indices;

  int size = (int)(endIndex - startIndex);
  if (size < 0) {
    return false;
  }

  indices.reserve(size);

  for (unsigned int n = startIndex; n <= endIndex; ++n) {
    indices.push_back(n);
  }

  return RegistProjectileInfo(projectileTag, imageIndex, indices, interval, loop, transColor, velocity, position, range);
}

bool ProjectileComponent::RegistProjectileInfo(
    unsigned long long projectileTag,
    unsigned long long imageIndex,
    const std::vector<unsigned int>& indices,
    unsigned long long interval,
    bool loop,
    const Color8Bit& transColor,
    const Vector& velocity,
    const Vector& position,
    const Vector& range) {
  std::vector<unsigned long long> intervals;
  intervals.reserve(indices.size());

  for (size_t n = 0; n < indices.size(); ++n) {
    intervals.push_back(interval);
  }

  return RegistProjectileInfo(projectileTag, imageIndex, indices, intervals, loop, transColor, velocity, position, range);
}

bool ProjectileComponent::RegistProjectileInfo(
    unsigned long long projectileTag,
    unsigned long long imageIndex,
    std::vector<unsigned int> indices,
    std::vector<unsigned long long> intervals,
    bool loop,
    Color8Bit transColor,
    const Vector& velocity,
    const Vector& position,
    const Vector& range) {
  ProjectileInfo* pFind;
  if (0 != projectileTable_.Select((void**)&pFind, 1, &projectileTag, 8)) {
    return false;
  }

  ProjectileInfo* pInfo = new ProjectileInfo;
  pInfo->projectileTag_ = projectileTag;
  pInfo->imageIndex_ = imageIndex;
  pInfo->indices_ = indices;
  pInfo->intervals_ = intervals;
  pInfo->loop_ = loop;
  pInfo->transColor_ = transColor;
  pInfo->velocity_ = velocity;
  pInfo->position_ = position;
  pInfo->range_ = range;
  pInfo->searchHandle_ = projectileTable_.Insert(pInfo, &pInfo->projectileTag_, 8);

  return nullptr != pInfo->searchHandle_;
}