#pragma once


class HealthComponent final
    : public ActorComponent
{
 public:
  HealthComponent();
  ~HealthComponent();

 void BeginPlay() override;

 bool Initialize(float maxHealth);

 void Tick(unsigned long long curTick) override;

 void SetHealth(float health);

 float Health() const;

 float MaxHealth() const;

 void Heel(float heel);

 void TakeDamage(float damage);

 private:
 float maxHealth_;

 float health_; 

};
