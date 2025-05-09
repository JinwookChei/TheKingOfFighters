#include "stdafx.h"
#include "TimeManager.h"

TimeManager::TimeManager()
    : onFrameFreeze_(false),
      freezeDuration_(0.0f),
      curFreezeTime_(0.0f) {
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
