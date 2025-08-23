#pragma once
enum CHANG_ANIM_TYPE : unsigned long long {
  CHANG_ANIMTYPE_HikiNige = PLAYER_ANIMTYPE_Max + 1ULL,
  CHANG_ANIMTYPE_TekkyuuGeki,
  CHANG_ANIMTYPE_TekkyuuDaiKaiten,
  CHANG_ANIMTYPE_TekkyuuFunsaiGeki,
  CHANG_ANIMTYPE_Max
};


class Chang
    : public KOFPlayer {
 public:
  Chang();

  ~Chang() override;

  void BeginPlay() override;

  void Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) override;

  void CompareInputBitset() override;
};