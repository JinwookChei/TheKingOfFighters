#pragma once

class TestLevel final
    : public Level {
 public:
  TestLevel();

  ~TestLevel();

  void BeginPlay() override;

  void Tick(unsigned long long dletaTick) override;

 private:
  Vector position_;

  Vector scale_;
};