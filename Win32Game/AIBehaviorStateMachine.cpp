#include "stdafx.h"
#include "AIBehaviorStateMachine.h"
#include <random>

AIBehaviorStateMachine::AIBehaviorStateMachine() {
}

AIBehaviorStateMachine::~AIBehaviorStateMachine() {
  for (HashTableIterator iter = behabiorTable_.begin(); iter != behabiorTable_.end();) {
    AIBehabiorInfo* pDel = (AIBehabiorInfo*)*iter;
    iter = behabiorTable_.erase(iter);

    delete pDel;
  }

  behabiorTable_.Cleanup();
}

void AIBehaviorStateMachine::BeginPlay() {
}

void AIBehaviorStateMachine::Tick(unsigned long long deltaTick) {

}

bool AIBehaviorStateMachine::Initialize() {
  return behabiorTable_.Initialize(8, 8);
}

bool AIBehaviorStateMachine::SearchBehabior(AI_BEHABIOR_STATE behabiorTag, AIBehabiorInfo** outBehabiorInfo) {
  AIBehabiorInfo* pInfo;
  if (0 == behabiorTable_.Select((void**)&pInfo, 1, &behabiorTag, 8)) {
    return false;
  }

  if (nullptr == pInfo) {
    return false;
  }

  *outBehabiorInfo = pInfo;
  return true;
}

void AIBehaviorStateMachine::ChangeBehabiorState(AI_BEHABIOR_STATE behabiorTag) {
  AIBehabiorInfo* pBehabiorInfo = nullptr;
  if (false == SearchBehabior(behabiorTag, &pBehabiorInfo)) {
    return;
  }

  if (nullptr != curBehabiorInfo_) {
    curBehabiorInfo_->currentRunning_ = false;
  }

  if (false == pBehabiorInfo->isCoolTimeActive_) {
  curBehabiorInfo_ = pBehabiorInfo;
  pBehabiorInfo->isCoolTimeActive_ = true;
  pBehabiorInfo->coolTimer_ = 0;
  pBehabiorInfo->currentRunning_ = true;
  }else{
    pBehabiorInfo = nullptr;
    if (false == SearchBehabior(AI_BEHABIOR_Idle, &pBehabiorInfo)) {
      return;
    }
    curBehabiorInfo_ = pBehabiorInfo;
    pBehabiorInfo->isCoolTimeActive_ = true;
    pBehabiorInfo->coolTimer_ = 0;
    pBehabiorInfo->currentRunning_ = true;
  }
}

void AIBehaviorStateMachine::DecideBehabior(unsigned long long deltaTick) {
  if (nullptr == curBehabiorInfo_) {
    return;
  }

  behabiorTimer_ += deltaTick;

  if (behabiorTimer_ >= curBehabiorInfo_->behabiorDuration_) {

      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dist(0, AI_BEHABIOR_Max - 1);
      AI_BEHABIOR_STATE behabiorTag = (AI_BEHABIOR_STATE)dist(gen);

      ChangeBehabiorState(behabiorTag);
      behabiorTimer_ = 0;
  }
}

void AIBehaviorStateMachine::UpdateCoolTime(unsigned long long deltaTick) {
  for (HashTableIterator iter = behabiorTable_.begin(); iter != behabiorTable_.end();) {
    AIBehabiorInfo* pInfo = (AIBehabiorInfo*)*iter;
    ++iter;

    if (false == pInfo->isCoolTimeActive_) {
      continue;
    }

    if (true == pInfo->currentRunning_) {
      continue;
    }

    pInfo->coolTimer_ += deltaTick;

    if (pInfo->coolTimer_ >= pInfo->coolTime_) {
      pInfo->isCoolTimeActive_ = false;
      pInfo->coolTimer_ = 0;
    }
  }
}

void AIBehaviorStateMachine::UpdateBehabior() {
  if (nullptr != curBehabiorInfo_ && nullptr != curBehabiorInfo_->behabior_) {
    curBehabiorInfo_->behabior_();
  }
}

AI_BEHABIOR_STATE AIBehaviorStateMachine::GetCurBehabior() const {
  return curBehabiorInfo_->behabiorTag_;
}
