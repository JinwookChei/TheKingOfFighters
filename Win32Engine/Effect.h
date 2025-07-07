#pragma once
#include "Actor.h"

class Effect
    : public Actor {
 public:
  Effect();

  ~Effect();

  bool Initialize();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  EffectInfo* GetEffectInfo() const;

  void SetEffectInfo(EffectInfo* effectInfo);

 protected:

 private:

  EffectInfo* pEffectInfo_;

  ImageRenderer* pRender_;

  SoundChannel soundChannel_;

  long long curTime_;

  int curFrame_;

  bool isFirstTick_;

};
