#pragma once

class TimeManager {
  friend class EngineCore;

 public:
  TimeManager();
  ~TimeManager();

  JO_API static TimeManager* Instance();

  JO_API void OnFrameFreeze(unsigned long long freezeDuration = 200);

  bool FrameFreeze(unsigned long long deltaTick);

  JO_API void SetTimeScale(float scale, float lerpSpeed = 5.0f);

  void TickTimeEffects(unsigned long long deltaTick);

  float GetTimeScale() const;

 private:
  bool onFrameFreeze_;

  unsigned long long freezeDuration_;

  unsigned long long curFreezeTime_;

  float timeScale_;

  float targetTimeScale_;

  float timeScaleLerpSpeed_;
};