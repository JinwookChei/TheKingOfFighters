#include "stdafx.h"
#include "CameraManager.h"
#include "Actor.h"

CameraManager::CameraManager()
    : target_(nullptr) {
}

CameraManager::~CameraManager() {
}

CameraManager* CameraManager::Instance() {
  return GCamera;
}

void CameraManager::SetLookAt(const Vector& newLookAt) {
  lookAt_ = newLookAt;
}

const Vector& CameraManager::GetLookAt() const {
  return lookAt_;
}

const Vector& CameraManager::GetCenter() const {
  return center_;
}

void CameraManager::SetTarget(Actor* target) {
  target_ = target;
}

Vector CameraManager::GetRenderPosition(const Vector& position) const {
  return position - diff_;
}

Vector CameraManager::GetWorldPosition(const Vector& renderPosition) const {
  return renderPosition + diff_;
}

void CameraManager::BeginPlay() {
  resolution_ = GEngine->GetBackbufferScale();

  center_ = {resolution_.HalfX(), resolution_.HalfY()};
}

void CameraManager::CalculateTargetDiff() {
  Vector v = lookAt_;
  if (nullptr != target_) {
    v += target_->GetPosition();
  }

  diff_ = v - center_;
}
