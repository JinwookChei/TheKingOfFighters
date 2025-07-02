#include "stdafx.h"
#include "CameraTarget.h"

CameraTarget::CameraTarget()
    : cameraMinHeight_(0.0f),
      cameraMaxHeight_(0.0f),
      cameraMinWidth_ (0.0f),
      cameraMaxWidth_(0.0f) {
}


CameraTarget::~CameraTarget() {
}

void CameraTarget::BeginPlay() {
}

void CameraTarget::Tick(unsigned long long curTick) {
}

bool CameraTarget::Initialize(float cameraMinHeight, float cameraMaxHeight, float cameraMinWidth, float cameraMaxWidth) {
  cameraMinHeight_ = cameraMinHeight;
  cameraMaxHeight_ = cameraMaxHeight;
  cameraMinWidth_ = cameraMinWidth;
  cameraMaxWidth_ = cameraMaxWidth;

  return true;
}

float CameraTarget::GetCameraMinHeight() const {
  return cameraMinHeight_;
}

float CameraTarget::GetCameraMaxHeight() const {
  return cameraMaxHeight_;
}

float CameraTarget::GetCameraMinWidth() const {
  return cameraMinWidth_;
}

float CameraTarget::GetCameraMaxWidth() const {
  return cameraMaxWidth_;
}
