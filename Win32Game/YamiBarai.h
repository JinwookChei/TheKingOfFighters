#pragma once

class YamiBarai
    : public Projectile {
 public:
  YamiBarai();

  ~YamiBarai() override;

  bool Initialize() override;

  void UpdateProjectile() override;

 private:
  float accumulRange_;

  float velocity_;
 
  float range_;
};