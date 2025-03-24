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
    bool down_ = false;   // ���� ����
    bool press_ = false;  // ��� ���������ִ���
    bool up_ = false;     // ��� ����������?
    bool free_ = true;    // �������� ���� ����.

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