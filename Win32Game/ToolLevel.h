#pragma once

class ToolLevel final
    : public Level {
 public:
  ToolLevel();

  ~ToolLevel();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

 private:
  Vector position_;

  Vector scale_;
};