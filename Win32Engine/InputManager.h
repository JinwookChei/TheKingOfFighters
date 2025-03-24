#pragma once

class HashTable;
class InputManager final {
 private:
  friend class EngineCore;

  class InputState {
    friend class InputManager;

   public:
    InputState();

    InputState(int key);

    void InputStateCheck(unsigned long long deltaTick);

   private:
    bool down_ = false;   // 누른 순간
    bool press_ = false;  // 계속 눌려지고있는지
    bool up_ = false;     // 방금 떼어졌는지?
    bool free_ = true;    // 눌려지고 있지 않음.

    int key_ = -1;

    unsigned long long pressTime_ = 0;
    unsigned long long upTime_ = 0;
  };

 public:
  InputManager();

  ~InputManager();

  JO_API static InputManager* Instance();

  JO_API bool IsAnyKeyDown() const;

  JO_API bool IsAnyKeyPress() const;

  JO_API bool IsDown(int key);

  JO_API bool IsPress(int key);

  JO_API unsigned long long PressTime(int key);

  JO_API bool IsUp(int key);

  JO_API bool IsFree(int key);

  JO_API unsigned long long UpTime(int key);

 private:
  bool Initialize();

  void Tick(unsigned long long deltaTime);

  unsigned long long isAnyKeyDown_ : 1;

  unsigned long long isAnyKeyPress_ : 1;

  HashTable* hashTable_;
};