#pragma once

class IoriAnimationHandler
    : public AnimationHandler
{
 public:
  IoriAnimationHandler();

  ~IoriAnimationHandler();

  void Tick(unsigned long long deltaTick) override;

  void Test() override;

  bool RegistAnimations() override;
  
};
