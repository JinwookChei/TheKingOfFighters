#include "stdafx.h"
#include "TimeManager.h"

float Lerp(float a, float b, float t) {
  return a + (b - a) * t;
}

TimeManager::TimeManager()
    : onFrameFreeze_(false),
      freezeDuration_(0.0f),
      curFreezeTime_(0.0f),
      timeScale_(1.0f),
      targetTimeScale_(1.0f),
      timeScaleLerpSpeed_(5.0f) {
}

TimeManager::~TimeManager() {
}

TimeManager* TimeManager::Instance() {
  return GTimeManager;
}

void TimeManager::OnFrameFreeze(unsigned long long freezeDuration /*= 200*/) {
  freezeDuration_ = freezeDuration;
  onFrameFreeze_ = true;
}

bool TimeManager::FrameFreeze(unsigned long long deltaTick) {
  if (GTimeManager->onFrameFreeze_ == true) {
    GTimeManager->curFreezeTime_ += deltaTick;
    if (GTimeManager->curFreezeTime_ >= GTimeManager->freezeDuration_) {
      GTimeManager->curFreezeTime_ = 0;
      GTimeManager->onFrameFreeze_ = false;
    } else {
      return true;
    }
  }

  return false;
}

void TimeManager::SetTimeScale(float scale, float lerpSpeed /*= 0.5f*/) {
  targetTimeScale_ = scale;
  timeScaleLerpSpeed_ = lerpSpeed;
}

void TimeManager::TickTimeEffects(unsigned long long deltaTick) {
  if (fabs(timeScale_ - targetTimeScale_) > 0.001f) {
    float deltaSeconds = deltaTick / 1000.0f;  // 밀리초 → 초 변환
    timeScale_ = Lerp(timeScale_, targetTimeScale_, deltaSeconds * timeScaleLerpSpeed_);
  }
}

float TimeManager::GetTimeScale() const {
  return timeScale_;
}

