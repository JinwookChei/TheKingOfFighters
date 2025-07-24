#pragma once

class HyakushikiOniyaki
    : public Projectile {
 public:
  HyakushikiOniyaki();

  ~HyakushikiOniyaki() override;

  void Tick(unsigned long long deltaTick) override;
  
  bool Initialize() override;

 private:
  Vector velocity_;
};