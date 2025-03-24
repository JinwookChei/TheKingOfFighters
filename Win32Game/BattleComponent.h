#pragma once

class BattleComponent
    : public ActorComponent {
 public:
  BattleComponent();

  ~BattleComponent();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;
};