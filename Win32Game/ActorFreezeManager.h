#pragma once

struct ActorFreezeInfo {
  unsigned long long actorId_ = 0;

  Actor* pActor_ = nullptr;

  bool isInfinite_ = false;

  unsigned long long timer_ = 0;

  unsigned long long duration_ = 0;

  void* searchHandle_ = nullptr;
};

class ActorFreezeManager final
    : public Actor {
 public:
  ActorFreezeManager();

  ~ActorFreezeManager();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize();

  bool RegistActor(unsigned long long actorId, Actor* pActor);

  void UnregistActor(unsigned long long actorId);

  void ApplyFreeze(unsigned long long actorId, bool isInfinite = true, unsigned long long duration = 0);

  void Defreeze(unsigned long long actorId);

 private:
  HashTable actorFreezeTable_;

  std::vector<unsigned long long> frozenActors_;
};
