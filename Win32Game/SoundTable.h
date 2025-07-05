#pragma once

struct SoundInfo {
  unsigned long long soundTableKey_ = 0;
  SOUND_TYPE soundType_ = SOUNDTYPE_None;
  void* searchHandle_ = nullptr;
};

class SoundTable
    : public ActorComponent {
 public:
  SoundTable();
  ~SoundTable();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initailize();

  bool RegistSoundInfo(unsigned long long soundTableKey, SOUND_TYPE soundType);

  bool SearchSoundInfo(unsigned long long soundTableKey, SoundInfo** outSearchResult);

 private:
  HashTable soundTable_;
};