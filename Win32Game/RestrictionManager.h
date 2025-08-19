#pragma once
#include "RestrictionComponent.h"

struct RestrictComponentInfo {
  unsigned long long actorId_ = 0;

  RestrictionComponent* pRestrictComponent_ = nullptr;

  void* searchHandle_ = nullptr;
};

 struct ActiveRestrictionInfo {
   unsigned long long actorId_ = 0;

   RestrictionComponent* pRestrictComponent_ = nullptr;

   std::bitset<PLAYER_RESTRICT_TYPE::PR_Max> restrictBitset_;

   bool isInfinite_ = false;

   unsigned long long timer_ = 0;

   unsigned long long duration_ = 0;
 };


class RestrictionManager final 
: public Actor{
 public:
  RestrictionManager();

  ~RestrictionManager();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;  

  bool Initialize();

  bool RegistComponent(unsigned long long actorId, RestrictionComponent* pRestrictComponent);

  void UnregistComponent(unsigned long long actorId);

  void ApplyExternalRestrict(
	  unsigned long long actorId, 
	  std::vector<PLAYER_RESTRICT_TYPE> restrictList, 
	  bool isInfinite = true, 
	  unsigned long long duration = 0);

    void ApplyExternalRestrict(
      unsigned long long actorId,
      const std::bitset<PR_Max>& restrictList,
      bool isInfinite = true,
      unsigned long long duration = 0);

  void ReleaseExternalRestrict(unsigned long long actorId, std::vector<PLAYER_RESTRICT_TYPE> restrictList);

    void ReleaseExternalRestrict(unsigned long long actorId, const std::bitset<PR_Max>& restrictList);

  void ClearExternalRestrict(unsigned long long actorId);

 private:
  HashTable restrictComponentTable_;

  std::vector<ActiveRestrictionInfo> activeRestrictions_;
};
