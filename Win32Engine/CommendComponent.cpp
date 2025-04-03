#include "stdafx.h"
#include "CommendComponent.h"

CommendComponent::CommendComponent()
    : pRootNode_(new CommendNode()),
      pCurNode_(pRootNode_),
      timeOut_(0),
      timeOutThreshold_(0) {
  for (int i = 0; i < CommendKey::CK_MAX; ++i) {
    pRootNode_->pSubNodes[i] = new CommendNode();
  }
}

CommendComponent::~CommendComponent() {
  if (nullptr != pRootNode_) {
    delete pRootNode_;
  }
}

void CommendComponent::BeginPlay() {
}

void CommendComponent::Tick(unsigned long long curTick) {
  timeOut_ += curTick;
  if (timeOut_ > timeOutThreshold_) {
    ResetNode();
  }
}

bool CommendComponent::RegistTask(std::initializer_list<CommendKey> commend, void (*task)()) {
  if (nullptr == pRootNode_) {
    return false;
  }

  CommendNode* pCur;
  pCur = pRootNode_;

  for (auto iter = commend.begin(); iter != commend.end(); ++iter) {
    if (nullptr == pCur->pSubNodes[*iter]) {
      pCur->pSubNodes[*iter] = new CommendNode();
    }
    pCur = pCur->pSubNodes[*iter];
  }

  pCur->Task = task;

  return true;
}

void CommendComponent::JumpNode(CommendKey key) {
  timeOut_ = 0;

  if (nullptr == pCurNode_->pSubNodes[key]) {
    pCurNode_ = pRootNode_->pSubNodes[key];
    return;
  } else {
    pCurNode_ = pCurNode_->pSubNodes[key];
  }

  if (nullptr == pCurNode_) {
    return;
  }

  if (nullptr != pCurNode_->Task) {
    pCurNode_->Task();
    ResetNode();
  }
}

void CommendComponent::SetTimeOutThreshold(unsigned long long threshold) {
  timeOutThreshold_ = threshold;
}

void CommendComponent::ResetNode() {
  if (nullptr == pRootNode_) {
    return;
  }
  pCurNode_ = pRootNode_;
  timeOut_ = 0;
}
