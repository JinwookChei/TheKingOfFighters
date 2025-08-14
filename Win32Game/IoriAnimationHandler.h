#pragma once

class IoriAnimationHandler
    : public AnimationHandler
{
 public:
  IoriAnimationHandler();

  ~IoriAnimationHandler();

  bool RegistAnimations() override;
  
};
