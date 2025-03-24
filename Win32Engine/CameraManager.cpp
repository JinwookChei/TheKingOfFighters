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

void CameraManager::SetTarget(Actor* target) {
  target_ = target;
}

Vector CameraManager::GetRenderPosition(const Vector& position) const {
  return position - diff_;
}

Vector CameraManager::GetWorldPosition(const Vector& renderPosition) const {
  return renderPosition + diff_;
}

void CameraManager::CalculateTargetDiff() {
  Vector bufferScale = GEngine->GetBackbufferScale();

  Vector center = {bufferScale.HalfX(), bufferScale.HalfY()};

  Vector v = lookAt_;
  if (nullptr != target_) {
    v += target_->GetPosition();
  }

  diff_ = v - center;
}
