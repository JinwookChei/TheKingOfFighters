#pragma once

class Enemy
    : public Actor {
 public:
  Enemy();

  ~Enemy();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

};