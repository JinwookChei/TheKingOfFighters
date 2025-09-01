#pragma once
enum CHANG_ANIM_TYPE : unsigned long long {
  CHANG_ANIMTYPE_HikiNige = PLAYER_ANIMTYPE_Max + 1ULL,
  CHANG_ANIMTYPE_TekkyuuGeki,
  CHANG_ANIMTYPE_TekkyuuDaiKaiten,
  CHANG_ANIMTYPE_TekkyuuFunsaiGeki,
  CHANG_ANIMTYPE_TekkyuDaiBousou_0,
  CHANG_ANIMTYPE_TekkyuDaiBousou_1,
  CHANG_ANIMTYPE_TekkyuDaiBousou_2,
  CHANG_ANIMTYPE_TekkyuDaiBousou_3,
  CHANG_ANIMTYPE_TekkyuDaiBousou_4,
  CHANG_ANIMTYPE_TekkyuDaiBousou_5,
  CHANG_ANIMTYPE_TekkyuDaiBousou_6,
  CHANG_ANIMTYPE_TekkyuDaiBousou_7,
  CHANG_ANIMTYPE_TekkyuDaiBousou_8,
  CHANG_ANIMTYPE_TekkyuDaiBousou_9,
  CHANG_ANIMTYPE_TekkyuDaiBousou_10,
  CHANG_ANIMTYPE_TekkyuDaiBousou_11,
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