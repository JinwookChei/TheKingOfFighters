#pragma once

class ProjectileComponent
    : public ActorComponent {
 public:
  ProjectileComponent();
  ~ProjectileComponent();

  void BeginPlay() override;

  bool Initialize(Level* level);

  void FireProjectile(unsigned long long projectileTag, bool isFacingRight);

  bool RegistProjectileInfo(
      unsigned long long projectileTag,
      unsigned long long imageIndex,
      unsigned int startIndex,
      unsigned int endIndex,
      unsigned long long interval,
      bool loop,
      const Color8Bit transColor,
      const Vector& velocity,
      const Vector& position,
      const Vector& range);

  bool RegistProjectileInfo(
      unsigned long long projectileTag,
      unsigned long long imageIndex,
      const std::vector<unsigned int>& indices,
      unsigned long long interval,
      bool loop,
      const Color8Bit& transColor,
      const Vector& velocity,
      const Vector& position,
      const Vector& range);
  
  bool RegistProjectileInfo(
      unsigned long long projectileTag,
      unsigned long long imageIndex,
      std::vector<unsigned int> indices,
      std::vector<unsigned long long> intervals,
      bool loop,
      Color8Bit transColor,
      const Vector& velocity,
      const Vector& position,
      const Vector& range);

 private:
  Level* level_;

  HashTable projectileTable_;
};
