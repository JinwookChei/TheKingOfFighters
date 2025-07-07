#include "stdafx.h"
#include "SoundTable.h"

SoundTable::SoundTable() {
}

SoundTable::~SoundTable() {
  for (HashTableIterator iter = soundTable_.begin(); iter != soundTable_.end();) {
    SoundInfo* pDel = (SoundInfo*)*iter;
    iter = soundTable_.erase(iter);

    delete pDel;
  }

  soundTable_.Cleanup();
}

void SoundTable::BeginPlay() {
}

void SoundTable::Tick(unsigned long long deltaTick) {
}

bool SoundTable::Initailize() {
  return soundTable_.Initialize(8, 8);
}

bool SoundTable::RegistSoundInfo(unsigned long long soundTableKey, SOUND_TYPE soundType) {
  SoundInfo* pFind;
  if (0 != soundTable_.Select((void**)&pFind, 1, &soundTableKey, 8)) {
    return false;
  }

  SoundInfo* pInfo = new SoundInfo;
  pInfo->soundTableKey_ = soundTableKey;
  pInfo->soundType_ = soundType;
  pInfo->searchHandle_ = soundTable_.Insert(pInfo, &pInfo->soundTableKey_, 8);

  return nullptr != pInfo->searchHandle_;
}

bool SoundTable::SearchSoundInfo(unsigned long long soundTableKey, SoundInfo** outSearchResult) {
  SoundInfo* pInfo;
  if (0 == soundTable_.Select((void**)&pInfo, 1, &soundTableKey, 8)) {
    return false;
  }

  if (nullptr == pInfo) {
    return false;
  }

  *outSearchResult = pInfo;
  return true;
}
