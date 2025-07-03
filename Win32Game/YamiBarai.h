#pragma once

class YamiBarai
    : public Projectile {
 public:
  YamiBarai();

  ~YamiBarai() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize() override;

 private:
  ImageRenderer* pRender2_;

  float accumulRange_;

  float velocity_;
 
  float range_;
};