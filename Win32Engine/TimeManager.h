#pragma once

class TimeManager {
  friend class EngineCore;

 public:
  TimeManager();
  ~TimeManager();

  JO_API static TimeManager* Instance();

  JO_API void OnFrameFreeze(unsigned long long freezeDuration = 200);

 private:
  bool onFrameFreeze_;

  unsigned long long freezeDuration_;

  unsigned long long curFreezeTime_;
};