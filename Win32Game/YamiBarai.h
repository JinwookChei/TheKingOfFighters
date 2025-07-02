#pragma once

class YamiBarai
    : public Projectile {
 public:
  YamiBarai();

  ~YamiBarai() override;

  bool Initialize() override;

  void UpdateProjectile() override;

 private:
  ImageRenderer* pRender2_;

  float accumulRange_;

  float velocity_;
 
  float range_;
};