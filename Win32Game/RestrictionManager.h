#pragma once

class RestrictionComponent;
enum PLAYER_RESTRICT_TYPE : unsigned int;

struct RestrictComponentInfo {
  unsigned long long actorId_ = 0;

  RestrictionComponent* pRestrictComponent_ = nullptr;

  void* searchHandle_ = nullptr;
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

  void ApplyExternalRestrict(unsigned long long actorId, std::initializer_list<PLAYER_RESTRICT_TYPE> restrictList);

  void ReleaseExternalRestrict(unsigned long long actorId, std::initializer_list<PLAYER_RESTRICT_TYPE> restrictList);

  void ResetExternalRestrict(unsigned long long actorId);

 private:
  HashTable restrictComponentTable_;
};
