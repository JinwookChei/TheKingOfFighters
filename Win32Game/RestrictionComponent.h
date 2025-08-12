#pragma once
#include "RestrictionManager.h"

enum PLAYER_RESTRICT_TYPE : unsigned int {
  PR_LockInput,
  PR_LockExecuteCommand,
  PR_LockAnimTrans,
  PR_Max
};

struct Restriction {
  unsigned long long restrictTag_ = 0;

  std::bitset<PR_Max> restrictBitset_;

  void* searchHandle_ = nullptr;
};

class RestrictionComponent
    : public ActorComponent {
 public:
  friend class RestrictionManager;

  RestrictionComponent();

  ~RestrictionComponent() override;

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize();

  bool RegistAnimStateRestrict(unsigned long long restrictTag, std::initializer_list<PLAYER_RESTRICT_TYPE> restrictList);

  void ChangeAnimStateRestrict(unsigned long long restrictTag);

  void CalculateFinalRestrict();

  bool EqualFinalRestrict(std::initializer_list<PLAYER_RESTRICT_TYPE> compareRestrictList);

  bool ContainFinalRestrict(std::initializer_list<PLAYER_RESTRICT_TYPE> compareRestrictList);

  bool CanInput() const;

  bool CanExecuteCommand() const;

 private:

  Restriction animStateRestrict_;

  Restriction externRestrict_;

  Restriction finalRestrict_;

  HashTable animStateRestrictTable_;
};