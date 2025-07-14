#pragma once


class Ura306Shiki
    : public Projectile {
 public:
  Ura306Shiki();

  ~Ura306Shiki() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize() override;

};