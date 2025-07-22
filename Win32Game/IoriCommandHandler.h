#pragma once

class IoriCommandHandler
    : public CommandHandler {
 public:
  IoriCommandHandler();

  ~IoriCommandHandler();

  bool RegistCommands() override;

  void Command_1();

  void Command_2();

  void Command_3();

  void Command_4();

  void Command_5();

  void Command_6();

  void Command_7();

};