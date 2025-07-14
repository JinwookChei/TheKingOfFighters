#pragma once

class MPComponent
    : public ActorComponent {
 public:
  MPComponent();

  ~MPComponent();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize(float maxMP);

  float MP() const;

  float MaxMP() const;

  int SkillPoint() const;

  int MaxSkillPoint() const;

  void ChargeMP(float mp);

 private:
  float maxMP_;

  float MP_;

  int maxSkillPoint_;

  int skillPoint_;
};