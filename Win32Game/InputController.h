#pragma once

enum KEY_STATE : unsigned int {
  KEY_STATE_Press = 0,
  KEY_STATE_Down,
  KEY_STATE_Up
};

enum KEY_TYPE : unsigned int {
  KEY_Left = 0,
  KEY_Down,
  KEY_Right,
  KEY_Up,
  KEY_A,
  KEY_B,
  KEY_C,
  KEY_D
};

class KOFPlayer;
class InputController
    : public ActorComponent {
 public:
  InputController();

  ~InputController() override;

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize(KOFPlayer* pOwnerPlayer, CommandComponent* pOwnerCommandComponent);

  void UpdateInput();

  void UpdateCommand();

  void ResetInputBitSet();

  bool IsEqualInputBitSet(KEY_STATE keyState, std::initializer_list<KEY_TYPE> targetKeys) const;

  bool IsContainInputBitSet(KEY_STATE keyState, std::initializer_list<KEY_TYPE> targetKeys) const;

  bool IsNoKeyInput() const;

 private:
  KOFPlayer* pOwnerPlayer_;

  CommandComponent* pOwnerCommand_;

  std::array<int, 8> playerKeySet_;

  std::bitset<8> inputPressBitSet_;

  std::bitset<8> inputDownBitSet_;

  std::bitset<8> inputUpBitSet_;
};