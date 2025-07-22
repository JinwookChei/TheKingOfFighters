#include "stdafx.h"
#include "CommandComponent.h"


CommandComponent::CommandComponent()
    : pRootNode_(new CommandNode()),
      pCurNode_(pRootNode_),
      inputTimeout_(0),
      inputTimeThreshold_(0),
      reservedTaskTimeout_(0),
      reservedTaskTimeThreshold_(0),
      reservedTask_(nullptr) {
  for (int i = 0; i < CommandKey::CK_MAX; ++i) {
    pRootNode_->pSubNodes[i] = new CommandNode();
  }
}

CommandComponent::~CommandComponent() {
  if (nullptr != pRootNode_) {
    delete pRootNode_;
  }
}

void CommandComponent::BeginPlay() {
}

void CommandComponent::Tick(unsigned long long curTick) {
  inputTimeout_ += curTick;
  if (inputTimeout_ > inputTimeThreshold_) {
    ResetNode();
  }

  if (nullptr == reservedTask_) {
    reservedTaskTimeout_ = 0;
  } else {
    reservedTaskTimeout_ += curTick;
    if (reservedTaskTimeout_ > reservedTaskTimeThreshold_) {
      reservedTask_ = nullptr;
    }
  }
}

bool CommandComponent::isWaitingTask() const {
  if (nullptr != reservedTask_) {
    return true;
  }
  return false;
}

void CommandComponent::ExcuteTask() {
  if (nullptr != reservedTask_) {
    reservedTask_();
    reservedTask_ = nullptr;
  }
}

void CommandComponent::JumpNode(CommandKey key) {
  inputTimeout_ = 0;

  if (nullptr == pCurNode_->pSubNodes[key]) {
    pCurNode_ = pRootNode_->pSubNodes[key];
    return;
  } else {
    pCurNode_ = pCurNode_->pSubNodes[key];
  }

  if (nullptr == pCurNode_) {
    return;
  }

  if (nullptr != pCurNode_->Task_) {
    Actor* owner = GetOwner();
    if (nullptr == owner) {
      return;
    }

    reservedTask_ = pCurNode_->Task_;

    ResetNode();
  }
}

void CommandComponent::SetTimeOutThreshold(unsigned long long threshold, unsigned long long reservedTaskTimeThreshold) {
  inputTimeThreshold_ = threshold;
  reservedTaskTimeThreshold_ = reservedTaskTimeThreshold;
}

void CommandComponent::ResetNode() {
  if (nullptr == pRootNode_) {
    return;
  }

  pCurNode_ = pRootNode_;
  inputTimeout_ = 0;
}
