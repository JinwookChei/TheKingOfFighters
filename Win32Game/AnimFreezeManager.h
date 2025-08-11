#pragma once

struct AnimFreezeInfo {
  unsigned long long actorId_ = 0;

  ImageRenderer* pImageRenderer_ = nullptr;

  bool isInfinite_ = false;

  unsigned long long timer_ = 0;

  unsigned long long duration_ = 0;

  void* searchHandle_ = nullptr;
};

class AnimFreezeManager final
    : public Actor {
 public:
  AnimFreezeManager();

  ~AnimFreezeManager();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize();

  bool RegistComponent(unsigned long long actorId, ImageRenderer* pImageRenderer);

  void UnregistComponent(unsigned long long actorId);

  void ApplyFreeze(unsigned long long actorId, bool isInfinite = true, unsigned long long duration = 0);

  void Defreeze(unsigned long long actorId);

 private:
  HashTable rendererFreezeTable_;

  std::vector<unsigned long long> frozenActors_;
};
