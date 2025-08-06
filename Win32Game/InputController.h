#pragma once

enum TEMPKEYTYPE
{
  INPUT_PRESS = 0,
  INPUT_DOWN,
  INPUT_UP
};

class KOFPlayer;
class InputController
    : public ActorComponent
{
 public:
  InputController();

  ~InputController() override;

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize(KOFPlayer* pOwnerPlayer, CommandComponent* pOwnerCommandComponent);
  
  void UpdateInput();

  void UpdateCommand();

  void ResetInputBitSet();

  //void CompareInputBitset();

  bool IsEqualInputBitSet(TEMPKEYTYPE keytype, const std::bitset<8>& compareTarget) const;

  bool IsContainInputBitSet(TEMPKEYTYPE keytype, const std::bitset<8>& compareTarget) const;

  bool IsNoKeyInput() const;

  private:
  KOFPlayer* pOwnerPlayer_;

  CommandComponent* pOwnerCommand_;

  std::array<int, 8> playerKeySet_;

  std::bitset<8> inputPressBitSet_;

  std::bitset<8> inputDownBitSet_;

  std::bitset<8> inputUpBitSet_;
};