#pragma once

class ToolActor;
class TextComponent;

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

  ToolActor* toolActor_;

  TextComponent* imageIndexTextComponent_;

  wchar_t* imageIndexTextBuffer_;
};