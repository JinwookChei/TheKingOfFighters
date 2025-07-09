#pragma once


class GameInstance
{
 public:
  GameInstance();
  virtual ~GameInstance();

  bool Initialize();

  static GameInstance* Instance();

  void LoadKOFImages();
};
