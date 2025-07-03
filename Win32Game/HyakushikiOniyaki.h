#pragma once

class HyakushikiOniyaki
    : public Projectile {
 public:
  HyakushikiOniyaki();

  ~HyakushikiOniyaki() override;

  void Tick(unsigned long long deltaTick);
  
  bool Initialize() override;

 private:

  float velocityY_;
};