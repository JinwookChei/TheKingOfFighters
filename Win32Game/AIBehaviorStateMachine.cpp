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

bool AIBehaviorStateMachine::RegistBehabior(AI_BEHABIOR_STATE behabiorTag, unsigned long long behabiorDuration) {
  AIBehabiorInfo* pFind;
  if (0 != behabiorTable_.Select((void**)&pFind, 1, &behabiorTag, 8)) {
    return false;
  }

  AIBehabiorInfo* pInfo = new AIBehabiorInfo;
  pInfo->behabiorTag_ = behabiorTag;
  pInfo->behabiorDuration_ = behabiorDuration;
  pInfo->searchHandle_ = behabiorTable_.Insert(pInfo, &pInfo->behabiorTag_, 8);

  return nullptr != pInfo->searchHandle_;
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

  curBehabiorInfo_ = pBehabiorInfo;
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

    AIBehabiorInfo* pBehabiorInfo = nullptr;
    if (false == SearchBehabior(behabiorTag, &pBehabiorInfo)) {
      return;
    }

    curBehabiorInfo_ = pBehabiorInfo;
    behabiorTimer_ = 0;
  }
}

AI_BEHABIOR_STATE AIBehaviorStateMachine::GetCurBehabior() const {
  return curBehabiorInfo_->behabiorTag_;
}
