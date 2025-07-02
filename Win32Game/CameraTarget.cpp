#include "stdafx.h"
#include "CameraTarget.h"

CameraTarget::CameraTarget()
    : onCameraShake_(false),
      cameraShakeDuration_(0),
      cameraShakeTimer_(0),
      preShakePosition_({0.0f, 0.0f}),
      cameraMinHeight_(0.0f),
      cameraMaxHeight_(0.0f),
      cameraMinWidth_(0.0f),
      cameraMaxWidth_(0.0f) {
}

CameraTarget::~CameraTarget() {
}

void CameraTarget::BeginPlay() {
}

void CameraTarget::Tick(unsigned long long curTick) {
  if (true == onCameraShake_) {
    cameraShakeTimer_ += curTick;
    if (cameraShakeTimer_ >= cameraShakeDuration_) {
      OffCameraShake();
    } else {
      int shakeX = (rand() % 11) - 5;
      int shakeY = (rand() % 11) - 5;
      Vector curCameraPosition = GetPosition();

      if ((curCameraPosition.X <= cameraMinWidth_ && shakeX < 0) || curCameraPosition.X >= cameraMaxWidth_ && shakeX > 0) {
        shakeX *= -1;
      }
      if ((curCameraPosition.Y <= cameraMinHeight_ && shakeY < 0) || curCameraPosition.Y >= cameraMaxHeight_ && shakeY > 0) {
        shakeY *= -1;
      }
      SetPosition({curCameraPosition.X + shakeX, curCameraPosition.Y + shakeY});
    }
  }
}

bool CameraTarget::Initialize(float cameraMinHeight, float cameraMaxHeight, float cameraMinWidth, float cameraMaxWidth) {
  cameraMinHeight_ = cameraMinHeight;
  cameraMaxHeight_ = cameraMaxHeight;
  cameraMinWidth_ = cameraMinWidth;
  cameraMaxWidth_ = cameraMaxWidth;

  return true;
}

void CameraTarget::OnCameraShake(unsigned long long duration) {
  onCameraShake_ = true;
  cameraShakeDuration_ = duration;
  cameraShakeTimer_ = 0;
}

void CameraTarget::OffCameraShake() {
  onCameraShake_ = false;
  cameraShakeDuration_ = 0;
  cameraShakeTimer_ = 0;
  preShakePosition_ = {0.0f, 0.0f};
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
