#pragma once


class KOFLevel final
    : public Level {
 public:
  KOFLevel();

  ~KOFLevel();
  
  void BeginPlay() override;

  void Tick(unsigned long long dletaTick) override;

 private:
  Vector position_;

  Vector scale_;
};